#include <GL/glew.h>
#include <GL/glut.h>
#include <algorithm> // min, max
#include <iostream> //std::cout, std::endl
#include <vector>
#include <map>
#include "surfaces.h"

std::vector<surface*> surfaces;

void makeCheckImage(){

  int i, j; 
  int c = 1;

  for (i = 0; i < CHECK_IMAGE_HEIGHT; i++){
    
    for (j = 0; j < CHECK_IMAGE_WIDTH; j++) {

      loadbar(c++,CHECK_IMAGE_WIDTH*CHECK_IMAGE_HEIGHT);

      //the origin of the viewing ray, 1 for each pixel in the checkImage array
      long_dbl_vec perspective(3, std::vector<long double>{500,(long double)j,(long double)i});

      //multiplied by rotation matrix if any rotation
      perspective = prod(rotation,perspective);
      
      //necessary to sort surfaces by depth
      std::map<double,surface*> objects_intersected;
      
      //for each object in the scene
      for( std::vector<surface*>::iterator it = surfaces.begin(); it != surfaces.end(); it++ ){
	//intersection test takes ray origin and ray direction as args and return distance from viewport or -1
	double intersQ = (*it)->intersection_test(perspective, ray_directiion);
	if ( intersQ > 0 )
	  //objects intersected stored in map keyed on distance from viewport
	  objects_intersected[intersQ] = *it;
      }

      if( !objects_intersected.empty() ){
	surface* foreground_ob = objects_intersected.begin()->second;
	double foreground_ob_dist = objects_intersected.begin()->first;
	dbl_vec point_on_surface = perspective + foreground_ob_dist*ray_directiion;
   
	GLubyte_vec* shading = foreground_ob->shader(point_on_surface);

        checkImage[i][j][0] = (GLubyte)std::min(255,shading[0][0] + shading[1][0] + shading[2][0]);
        checkImage[i][j][1] = (GLubyte)std::min(255,shading[0][1] + shading[1][1] + shading[2][1]);
	checkImage[i][j][2] = (GLubyte)std::min(255,shading[0][2] + shading[1][2] + shading[2][2]);
      }
      else{
	checkImage[i][j][0] = 0;
	checkImage[i][j][1] = 0;
	checkImage[i][j][2] = 0;
      }
    }
  }
  for (i = 1; i < CHECK_IMAGE_HEIGHT-1; i++){
    checkImage[i][0][0] = checkImage[i][CHECK_IMAGE_WIDTH-1][0] = 255; 
    checkImage[i][0][1] = checkImage[i][CHECK_IMAGE_WIDTH-1][1] = 0;
    checkImage[i][0][2] = checkImage[i][CHECK_IMAGE_WIDTH-1][2] = 0;
  }
  for (j = 0; j < CHECK_IMAGE_WIDTH; j++){
    checkImage[0][j][0] = checkImage[CHECK_IMAGE_HEIGHT-1][j][0] = 255; 
    checkImage[0][j][1] = checkImage[CHECK_IMAGE_HEIGHT-1][j][1] = 0;
    checkImage[0][j][2] = checkImage[CHECK_IMAGE_HEIGHT-1][j][2] = 0;
  }
  
  
  
}

void init() {
  makeCheckImage();
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void keyPressed (unsigned char key, int x, int y) {  

  if( key == 'a' ){ // If the 'a' key has been pressed  
    rotate_viewing_angle(0,0,10);
    makeCheckImage();
    glutPostRedisplay();
  }
  if( key == 'd' ){
    rotate_viewing_angle(0,0,-10);
    makeCheckImage();
    glutPostRedisplay();
  }
  if( key == 'w' ){
    rotate_viewing_angle(0,10,0);
    makeCheckImage();
    glutPostRedisplay();
  }
  if( key == 's' ){
    rotate_viewing_angle(0,-10,0);
    makeCheckImage();
    glutPostRedisplay();
  }
  if( key == 'p'){
    
  }


}  

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glRasterPos2i(-1,-1);
  glDrawPixels(CHECK_IMAGE_WIDTH, CHECK_IMAGE_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, checkImage);
  glFlush();
}

int main(int argc, char **argv) {
  GLubyte red[3] = {255,0,0};
  GLubyte green[3] = {0,255,0};
  GLubyte blue[3] = {0,0,255};
  GLubyte grey[3] = {128,128,128};
  int_vec push(3, std::vector<int>{100,0,0});

  surface* sphere1 = new sphere(green, dbl_vec(3, std::vector<double>{100, 350,350}), 50);
  surface* sphere2 = new sphere(red, dbl_vec(3, std::vector<double>{50,300,300}), 20);
  // surface* triangle1 = new triangle((GLubyte[]){128,128,128}, 
  // 				    dbl_vec(3, std::vector<double>{0,500,0}),
  // 				    dbl_vec(3, std::vector<double>{0,0,0}),
  // 				    dbl_vec(3, std::vector<double>{0,0,500}));  
  // surface* triangle2 = new triangle((GLubyte[]){128,128,128}, 
  // 				    dbl_vec(3, std::vector<double>{0,500,0}),
  // 				    dbl_vec(3, std::vector<double>{0,0,500}),
  // 				    dbl_vec(3, std::vector<double>{0,500,500}));
  // surface* triangle3 = new triangle((GLubyte[]){128,128,128}, 
  // 				    dbl_vec(3, std::vector<double>{0,0,0}),
  // 				    dbl_vec(3, std::vector<double>{0,0,500}),
  // 				    dbl_vec(3, std::vector<double>{500,0,0}));  
  // surface* triangle4 = new triangle((GLubyte[]){128,128,128}, 
  // 				    dbl_vec(3, std::vector<double>{0,0,500}),
  // 				    dbl_vec(3, std::vector<double>{500,0,500}),
  // 				    dbl_vec(3, std::vector<double>{500,0,0}));
  // surface* triangle5 = new triangle((GLubyte[]){128,128,128}, 
  // 				    dbl_vec(3, std::vector<double>{0,0,0}),
  // 				    dbl_vec(3, std::vector<double>{500,0,0}),
  // 				    dbl_vec(3, std::vector<double>{0,500,0}));  
  // surface* triangle6 = new triangle((GLubyte[]){128,128,128}, 
  // 				    dbl_vec(3, std::vector<double>{500,0,0}),
  // 				    dbl_vec(3, std::vector<double>{500,500,0}),
  // 				    dbl_vec(3, std::vector<double>{0,500,0}));  
  surface* triangle7 = new triangle((GLubyte[]){128,128,128}, 
  				    dbl_vec(3, std::vector<double>{200,350,100}),
  				    dbl_vec(3, std::vector<double>{200,400,100}),
  				    dbl_vec(3, std::vector<double>{200,375,150}));
  surface* triangle8 = new triangle(grey, 
  				    dbl_vec(3, std::vector<double>{200,350,100}),
  				    dbl_vec(3, std::vector<double>{200,400,100}),
  				    dbl_vec(3, std::vector<double>{250,375,100}));
  surface* triangle9 = new triangle(grey, 
  				    dbl_vec(3, std::vector<double>{200,350,100}),
  				    dbl_vec(3, std::vector<double>{250,375,100}),
  				    dbl_vec(3, std::vector<double>{200,375,150}));
  surface* triangle10 = new triangle(grey, 
  				    dbl_vec(3, std::vector<double>{200,400,100}),
  				    dbl_vec(3, std::vector<double>{200,375,150}),
  				    dbl_vec(3, std::vector<double>{250,375,100}));

  surfaces = {triangle7,triangle8,triangle9,triangle10, sphere1, sphere2};
  //initialize rotation matrix because perspective is always multiplied by it, even if no rotation desired
  rotate_viewing_angle(0,0,0);
  init();
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(600,600);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses  
  // glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events  
  glutMainLoop();
  return 0;
  
}
