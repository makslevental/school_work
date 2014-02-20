
/*
    smooth.c
    Nate Robins, 1998

    Model viewer program.  Exercises the glm library.
*/
#include <vector>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <string.h>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <GL/glut.h>
#include "gltb.h"
#include "glm.h"
#include "dirent32.h"
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/times.h>
#include <iostream>

#pragma comment( linker, "/entry:\"mainCRTStartup\"" )  // set the entry point to be main()

#define DATA_DIR "data/"
#define IMAGE_WIDTH 1024
#define IMAGE_HEIGHT 1024
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 1024
#define T(x) (model->triangles[(x)])

static GLubyte image[IMAGE_WIDTH][IMAGE_HEIGHT][3];
//1 entry as a simple written/not written market, 1 entry for z-value, 3 for normal, 3 for local ambient, 3 for local diffuse, 3 for specular
double framebuffer[IMAGE_WIDTH][IMAGE_HEIGHT][1+1+3+3+3+3+3];
double zbuffer[IMAGE_WIDTH][IMAGE_HEIGHT];
char*      model_file = NULL;		/* name of the obect file */
GLuint     model_list = 0;		    /* display list for object */
GLMmodel*  model;			        /* glm model data structure */
GLfloat    scale;			        /* original scale factor */
GLfloat    smoothing_angle = 90.0;	/* smoothing angle */
GLfloat    weld_distance = 0.00001;	/* epsilon for welding vertices */
GLboolean  facet_normal = GL_FALSE;	/* draw with facet normal? */
GLboolean  bounding_box = GL_FALSE;	/* bounding box on? */
GLboolean  performance = GL_FALSE;	/* performance counter on? */
GLboolean  stats = GL_FALSE;		/* statistics on? */
GLuint     material_mode = 0;		/* 0=none, 1=color, 2=material */
GLint      entries = 0;			    /* entries in model menu */
GLdouble   pan_x = 0.0;
GLdouble   pan_y = 0.0;
GLdouble   pan_z = 0.0;

typedef boost::numeric::ublas::vector<double, std::vector<double> > dbl_vec;
typedef boost::numeric::ublas::vector<int,std::vector<int> > GLubyte_vec;
//GLubyte black[3] = {255,255,0}; //actually yellow or something
//GLubyte white[3] = {255,255,255};
GLdouble modelview[16];
GLdouble projection[16];
GLint viewport[4];
static dbl_vec light_src(3, std::vector<double>{0,0,-1});
static dbl_vec unit_light_src(light_src/norm_2(light_src));
static dbl_vec ray_directiion(3, std::vector<double>{0,0,-1});

#define PHONG_EXP 15.0
#define K_S .2
#define K_D 1
#define K_A .2
#define ILLUM 1

//
//float
//elapsed(void)
//{
//    static long begin = 0;
//    static long finish, difference;
//
//#if defined(_WIN32)
//    static struct timeb tb;
//    ftime(&tb);
//    finish = tb.time*1000+tb.millitm;
//#else
//    static struct tms tb;
//    finish = times(&tb);
//#endif
//
//    difference = finish - begin;
//    begin = finish;
//
//    return (float)difference/(float)1000;
//}
//
//void
//shadowtext(int x, int y, char* s)
//{
//    int lines;
//    char* p;
//
//    glDisable(GL_DEPTH_TEST);
//    glMatrixMode(GL_PROJECTION);
//    glPushMatrix();
//    glLoadIdentity();
//    glOrtho(0, glutGet(GLUT_WINDOW_WIDTH),
//        0, glutGet(GLUT_WINDOW_HEIGHT), -1, 1);
//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//    glLoadIdentity();
//    glColor3ub(0, 0, 0);
//    glRasterPos2i(x+1, y-1);
//    for(p = s, lines = 0; *p; p++) {
//        if (*p == '\n') {
//            lines++;
//            glRasterPos2i(x+1, y-1-(lines*18));
//        }
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
//    }
//    glColor3ub(0, 128, 255);
//    glRasterPos2i(x, y);
//    for(p = s, lines = 0; *p; p++) {
//        if (*p == '\n') {
//            lines++;
//            glRasterPos2i(x, y-(lines*18));
//        }
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
//    }
//    glMatrixMode(GL_PROJECTION);
//    glPopMatrix();
//    glMatrixMode(GL_MODELVIEW);
//    glPopMatrix();
//    glEnable(GL_DEPTH_TEST);
//}

void
lists(void)
{
//    GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
//    GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
//    GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat shininess = 65.0;
//
//    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
//    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
//
//    if (model_list)
//        glDeleteLists(model_list, 1);
//
//    /* generate a list */
//    if (material_mode == 0) {
//        if (facet_normal)
//            model_list = glmList(model, GLM_FLAT);
//        else
//            model_list = glmList(model, GLM_SMOOTH);
//    } else if (material_mode == 1) {
//        if (facet_normal)
//            model_list = glmList(model, GLM_FLAT | GLM_COLOR);
//        else
//            model_list = glmList(model, GLM_SMOOTH | GLM_COLOR);
//    } else if (material_mode == 2) {
//        if (facet_normal)
//            model_list = glmList(model, GLM_FLAT | GLM_MATERIAL);
//        else
//            model_list = glmList(model, GLM_SMOOTH | GLM_MATERIAL);
//    }
}

//inline dbl_vec cross_product(dbl_vec a, dbl_vec b){
//  dbl_vec V_r(3,std::vector<double>{a[1]*b[2]-a[2]*b[1],
//	                            a[2]*b[0]-a[0]*b[2],
//	                            a[0]*b[1]-a[1]*b[0]});
//  return V_r;
//}

void addMaterialToAllTriangles(){
    static GLuint i;
    static GLMgroup* group;
    static GLMtriangle* triangle;
    static GLMmaterial* material;

    group = model->groups;
    while(group) {
        for (i = 0; i < group->numtriangles; i++) {
            T(group->triangles[i]).material = group->material;
        }
        group = group->next;
    }
}

double calculateBeta(double z0, double z1, double alpha){
    return alpha*z0/((alpha*z0)+(1-alpha)*z1);
}

GLubyte_vec shader(dbl_vec normal, GLMmaterial* material){

    GLubyte_vec shades;
    // static because perspective RAY direction (not perspective pixel itself) is the same globally
    dbl_vec bisector = (light_src + -1*ray_directiion)/norm_2(light_src + -1*ray_directiion);
    //GLubyte_vec this_color(3, std::vector<GLubyte>{this->color[0],this->color[1],this->color[2]});
    GLubyte color[3];
    color[0] = material->diffuse[0]*255;
    color[1] = material->diffuse[1]*255;
    color[2] = material->diffuse[1]*255;

    GLubyte_vec diffuse_color(3, std::vector<int>{material->diffuse[0]*255, material->diffuse[0]*255, material->diffuse[0]*255});
    GLubyte_vec ambient_color(3, std::vector<int>{material->ambient[0]*255,material->ambient[1]*255,material->ambient[2]*255});
    GLubyte_vec specular_color(3, std::vector<int>{material->specular[0]*255,material->specular[1]*255,material->specular[2]*255});
    std::cout << diffuse_color << std::endl;
    std::cout << ambient_color << std::endl;
    std::cout << specular_color << std::endl;

    double norm_dot_light = inner_prod(normal,unit_light_src);
    double diffuse_lighting = K_D*std::max(0.,norm_dot_light);
    double norm_dot_bi = inner_prod(normal,bisector);
    double specular_lighting = K_S*pow(std::max(0.,norm_dot_bi),PHONG_EXP);
    double ambient_lighting = K_A;
    double illum = ILLUM;
    shades = illum*diffuse_lighting*diffuse_color;
    shades += illum*specular_lighting*ambient_color;
    shades += illum*ambient_lighting*diffuse_color;
    std::cout << "shades " << shades << std::endl;
    return shades;
}

void bresenham(int x0, int y0, double z0, int x1, int y1, double z1, dbl_vec normal, GLMmaterial* material){
    int dx = abs(x1-x0);
    int dy = abs(y1-y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx-dy;
    int x = floor(x0);
    int y = floor(y0);
    int e2;
    //interpolation
    double distanceFromStart = 0;
    double totalDistance = dx+dy;
    double alpha = 0;
    //shading
    GLubyte_vec color;
    color = shader(normal, material);



    while(true){

        //STORE THE NORMAL WITHOUT INTERPOLATION
        alpha = distanceFromStart/totalDistance;
        framebuffer[y][x][0] = 1;
        //printf("scaled method %f \n", z0+calculateBeta(z0,z1,alpha)*(z1-z0));
        framebuffer[y][x][1] = z0+calculateBeta(z0,z1,alpha)*(z1-z0);
        //printf("scaled framebuffer %f \n", framebuffer[y][x][1]);
        double scaled = framebuffer[y][x][1];
        //scaled = 1;

        framebuffer[y][x][2] = (double(color[0]));
        framebuffer[y][x][3] = (double(color[1]));
        framebuffer[y][x][4] = (double(color[2]));

        //printf("alpha %f z0 %f z1 %f x %d  y %f %f %f scaled %f \n", alpha, z0, z1, x, y, framebuffer[y][x][2], framebuffer[y][x][3], framebuffer[y][x][4], scaled);



        e2 = 2*err;
        if(x==x1 && y==y1) break;
        if(e2 > -dy){
            err -= dy;
            distanceFromStart++;
            x += sx;
        }
        if(x==x1 && y==y1){
            alpha = distanceFromStart/totalDistance;
            framebuffer[y][x][0] = 1;
            //printf("scaled method %f \n", z0+calculateBeta(z0,z1,alpha)*(z1-z0));
            framebuffer[y][x][1] = z0+calculateBeta(z0,z1,alpha)*(z1-z0);
            double scaled = framebuffer[y][x][1];
            //scaled = 1;

            framebuffer[y][x][2] = (double(color[0]));
            framebuffer[y][x][3] = (double(color[1]));
            framebuffer[y][x][4] = (double(color[2]));

            //printf("alpha %f z0 %f z1 %f x %d  y %f %f %f scaled %f \n", alpha, z0, z1, x, y, framebuffer[y][x][2], framebuffer[y][x][3], framebuffer[y][x][4], scaled);

            break;
        }
        if(e2 < dx){
            err += dx;
            distanceFromStart++;
            y += sy;
        }
    }
    //std::cout << "love max" << std::endl;
}

void scanlineTriangleToFrameBuffer(double vertices[3][3], dbl_vec normal, GLMmaterial* material){
    int minx = floor(std::min({vertices[0][0], vertices[1][0], vertices[2][0]}));
    int miny = floor(std::min({vertices[0][1], vertices[1][1], vertices[2][1]}));
    int maxx = ceil(std::max({vertices[0][0], vertices[1][0], vertices[2][0]}));
    int maxy = ceil(std::max({vertices[0][1], vertices[1][1], vertices[2][1]}));
    //STORE THE NORMAL WITHOUT INTERPOLATION

    //shading
    GLubyte_vec color = shader(normal, material);


    for(int y = miny-1; y < maxy+1; y++){
        int crossing = 0;
        int crossings[4][2];
        // crossings contains the x coordinates of the edges of the barrier. crossing[i][0] is the x right before the jump (up or down) and crossing[i][1] is the x
        // right after the jump
        for(int x = minx-1; x < maxx+1; x++){
            //printf("frame x+1 %f frame x %f \n",framebuffer[y][x+1][0], framebuffer[y][x][0]);
            if(abs(abs(framebuffer[y][x+1][0] - framebuffer[y][x][0]) - 1) < .0001 ){
                crossings[crossing][0] = x;
                crossings[crossing][1] = x+1;
                crossing++;
            }
            if(crossing == 4)
                break;
        }
        if(crossing == 4){
                double zleft = framebuffer[y][crossings[1][0]][1];
                double zright = framebuffer[y][crossings[2][1]][1];
                double totalAlpha = abs(crossings[1][1] - crossings[2][1]) - 1;
                double beta = 0;
                double scaled = 0;
                for(int k = crossings[1][1]; k < crossings[2][1]; k++){
                    beta = totalAlpha == 0 ? 0 : calculateBeta(zleft,zright,double(k-crossings[1][1])/totalAlpha);
                    scaled = zleft+beta*(zright-zleft);
                    framebuffer[y][k][1] = scaled;
                    //scaled = 1;


                    framebuffer[y][k][2] = (double(color[0]));
                    framebuffer[y][k][3] = (double(color[1]));
                    framebuffer[y][k][4] = (double(color[2]));



                    //printf("scanline %d %d %d %d %d %f \n", y, k, framebuffer[y][k][2], framebuffer[y][k][3], framebuffer[y][k][4], scaled);
                }
                //printf("end scanline \n");
        }
    }
}


//model is global
void plotTriangleToFrameBuffer(GLMtriangle* triangle){
    //want to compute shading once per triangle so hence here. and then pass it to each bresanham and scanline
    //get the matrices
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    double vertices[3][3];
    for(int j = 0; j < 3; j++){
        GLuint vindex = triangle->vindices[j];
        GLdouble winX, winY, winZ;//2D point
        GLfloat posX = model->vertices[3*vindex+0];
        GLfloat posY = model->vertices[3*vindex+1];
        GLfloat posZ = model->vertices[3*vindex+2];

        //        std::cout << "vertex " << j+1 << std::endl;
        //        printf("tx %f ty %f tz %f \n", posX, posY, posZ);

        int res=gluProject(posX,posY,posZ,modelview,projection,viewport,&winX,&winY,&winZ);
        //        printf("x %f y %f z %f \n", winX, winY, winZ);
        //        double myverts[3] = {winX, winY, winZ};
        //        std::vector<double> vertx(myverts, myverts + sizeof(myverts) / sizeof(double) );
        // TODO PASS TRIANGLE INSTEAD OF VERTICES TO plotTriangleToFrameBuffer
        vertices[j][0] = winX;
        vertices[j][1] = winY;
        vertices[j][2] = winZ;
        //printf("posx %f posy %f posx %f \n", posX, posY, posZ);
        //printf("winx %f winy %f winz %f \n", winX, winY, winZ);
    }

    dbl_vec normal(3, std::vector<double>{model->facetnorms[triangle->findex],model->facetnorms[triangle->findex+1],model->facetnorms[triangle->findex+2]});
    normal = normal/norm_2(normal);
    std::cout << normal << std::endl;
    GLMmaterial* triangleMaterial = &model->materials[triangle->material];
    bresenham(vertices[0][0],vertices[0][1], vertices[0][2], vertices[1][0], vertices[1][1], vertices[1][2], normal, triangleMaterial);
    bresenham(vertices[1][0],vertices[1][1], vertices[1][2], vertices[2][0], vertices[2][1], vertices[2][2], normal, triangleMaterial);
    bresenham(vertices[2][0],vertices[2][1], vertices[2][2], vertices[0][0], vertices[0][1], vertices[0][2], normal, triangleMaterial);
    scanlineTriangleToFrameBuffer(vertices, normal, triangleMaterial);
    //printf("\n");
}


void swapImageAndFrameBuffer(){
    //NOT THE LAST STEP. LAST STEP SHOULD SHADE. SO NEED ANOTHER BUFFER WHERE I COMPUTE SHADING AS A FUNCTION
    //OF NORMAL. THEN THE SWAP DOESN'T SWAP BUT JUST WRITES TO GLubyte array.
    for(int y = 0; y < IMAGE_HEIGHT; y++)
        for(int x = 0; x < IMAGE_WIDTH; x++){
            //printf("zbuffer %f framebuffer %f \n", zbuffer[y][x], framebuffer[y][x][1]);
            if( zbuffer[y][x] - framebuffer[y][x][1] > .1 ){
                zbuffer[y][x] = framebuffer[y][x][1];
                image[y][x][0] = (GLubyte)framebuffer[y][x][2];
                image[y][x][0] = (GLubyte)framebuffer[y][x][3];
                image[y][x][0] = (GLubyte)framebuffer[y][x][4];
            }
        }
}

void raster(){


    static int i = 0;
    //get the matrices

    GLMtriangle* triangle;
//    for(int i = 0; i < model->numtriangles; i++){
    int j = 5;
    for(int i = j; i < j+1/*model->numtriangles*/; i++){
        memset(framebuffer, 0, sizeof(framebuffer));
        for(int m = 0; m < IMAGE_HEIGHT; m++)
            for(int n = 0; n < IMAGE_WIDTH; n++){
                //framebuffer[m][n][0] = 0;
                framebuffer[m][n][1] = 10000;
                //framebuffer[m][n][2] = 0;
                //framebuffer[m][n][3] = 0;
                //framebuffer[m][n][4] = 0;
            }



        std::cout << "triangle " << i+1 << std::endl;
        //printf("triangle vertex indices %d %d %d \n", 3*model->triangles[i].vindices[0], 3*model->triangles[i].vindices[1], 3*model->triangles[i].vindices[2]);

        triangle = &model->triangles[i];

        plotTriangleToFrameBuffer(triangle);
        swapImageAndFrameBuffer();
        glutPostRedisplay();
    }
}


void
init(void)
{

    for(int i = 0; i < IMAGE_WIDTH; i++)
        for(int j = 0; j < IMAGE_WIDTH; j++){
            image[i][j][0] = 255;
            image[i][j][1] = 125;
            image[i][j][2] = 255;
            zbuffer[i][j] = 10000;
        }

    /* read in the model */
    model = glmReadOBJ(model_file);
    scale = glmUnitize(model);
    glmFacetNormals(model);
    glmVertexNormals(model, smoothing_angle);

    if (model->nummaterials > 0)
        material_mode = 2;

    /* create new display lists */
    //lists();
    addMaterialToAllTriangles();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

}

void
reshape(int width, int height)
{
//    gltbReshape(width, height);

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.0); //pushes the viewport back to z=2
}








#define NUM_FRAMES 5
void
display(void)
{

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glRasterPos2i(-1,-1);

    glPixelZoom(WINDOW_WIDTH/IMAGE_WIDTH, WINDOW_HEIGHT/IMAGE_HEIGHT);
    glDrawPixels(IMAGE_WIDTH, IMAGE_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, image);
    glutSwapBuffers();

}

void
keyboard(unsigned char key, int x, int y)
{
    GLint params[2];

    switch (key) {
    case 'h':
        printf("help\n\n");
        printf("w         -  Toggle wireframe/filled\n");
        printf("c         -  Toggle culling\n");
        printf("n         -  Toggle facet/smooth normal\n");
        printf("b         -  Toggle bounding box\n");
        printf("r         -  Reverse polygon winding\n");
        printf("m         -  Toggle color/material/none mode\n");
        printf("p         -  Toggle performance indicator\n");
        printf("s/S       -  Scale model smaller/larger\n");
        printf("t         -  Show model stats\n");
        printf("o         -  Weld vertices in model\n");
        printf("+/-       -  Increase/decrease smoothing angle\n");
        printf("W         -  Write model to file (out.obj)\n");
        printf("q/escape  -  Quit\n\n");
        break;

    case 't':
        stats = !stats;
        break;

    case 'p':
        performance = !performance;
        break;

    case 'm':
        material_mode++;
        if (material_mode > 2)
            material_mode = 0;
        printf("material_mode = %d\n", material_mode);
        lists();
        break;

    case 'd':
        glmDelete(model);
        init();
        lists();
        break;

    case 'w':
        glGetIntegerv(GL_POLYGON_MODE, params);
        if (params[0] == GL_FILL)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;

    case 'c':
        if (glIsEnabled(GL_CULL_FACE))
            glDisable(GL_CULL_FACE);
        else
            glEnable(GL_CULL_FACE);
        break;

    case 'b':
        bounding_box = !bounding_box;
        break;

    case 'n':
        facet_normal = !facet_normal;
        lists();
        break;

    case 'z':
        //glutPostRedisplay();
        break;

    case 'r':
        raster();
//        glmReverseWinding(model);
//        lists();
        break;

    case 's':
        glmScale(model, 0.8);
        lists();
        break;

    case 'S':
        glmScale(model, 1.25);
        lists();
        break;

    case 'o':
        //printf("Welded %d\n", glmWeld(model, weld_distance));
        glmVertexNormals(model, smoothing_angle);
        lists();
        break;

    case 'O':
        weld_distance += 0.01;
        printf("Weld distance: %.2f\n", weld_distance);
        glmWeld(model, weld_distance);
        glmFacetNormals(model);
        glmVertexNormals(model, smoothing_angle);
        lists();
        break;

    case '-':
        smoothing_angle -= 1.0;
        printf("Smoothing angle: %.1f\n", smoothing_angle);
        glmVertexNormals(model, smoothing_angle);
        lists();
        break;

    case '+':
        smoothing_angle += 1.0;
        printf("Smoothing angle: %.1f\n", smoothing_angle);
        glmVertexNormals(model, smoothing_angle);
        lists();
        break;

    case 'W':
        glmScale(model, 1.0/scale);
        glmWriteOBJ(model, "out.obj", GLM_SMOOTH | GLM_MATERIAL);
        break;
//
//    case 'R':
//        {
//            GLuint i;
//            GLfloat swap;
//            for (i = 1; i <= model->numvertices; i++) {
//                swap = model->vertices[3 * i + 1];
//                model->vertices[3 * i + 1] = model->vertices[3 * i + 2];
//                model->vertices[3 * i + 2] = -swap;
//            }
//            glmFacetNormals(model);
//            lists();
//            break;
//        }

    case 27:
        exit(0);
        break;
    }

    glutPostRedisplay();
}

void
menu(int item)
{
    int i = 0;
    DIR* dirp;
    char* name;
    struct dirent* direntp;

    if (item > 0) {
        keyboard((unsigned char)item, 0, 0);
    } else {
        dirp = opendir(DATA_DIR);
        while ((direntp = readdir(dirp)) != NULL) {
            if (strstr(direntp->d_name, ".obj")) {
                i++;
                if (i == -item)
                    break;
            }
        }
        if (!direntp)
            return;
        name = (char*)malloc(strlen(direntp->d_name) + strlen(DATA_DIR) + 1);
        strcpy(name, DATA_DIR);
        strcat(name, direntp->d_name);
        model = glmReadOBJ(name);
        scale = glmUnitize(model);
        glmFacetNormals(model);
        glmVertexNormals(model, smoothing_angle);

        if (model->nummaterials > 0)
            material_mode = 2;
        else
            material_mode = 0;

        lists();
        free(name);

        glutPostRedisplay();
    }
}

static GLint      mouse_state;
static GLint      mouse_button;

void
mouse(int button, int state, int x, int y)
{
    GLdouble model[4*4];
    GLdouble proj[4*4];
    GLint view[4];

    /* fix for two-button mice -- left mouse + shift = middle mouse */
    if (button == GLUT_LEFT_BUTTON && glutGetModifiers() & GLUT_ACTIVE_SHIFT)
        button = GLUT_MIDDLE_BUTTON;

    gltbMouse(button, state, x, y);

    mouse_state = state;
    mouse_button = button;

    if (state == GLUT_DOWN && button == GLUT_MIDDLE_BUTTON) {
        glGetDoublev(GL_MODELVIEW_MATRIX, model);
        glGetDoublev(GL_PROJECTION_MATRIX, proj);
        glGetIntegerv(GL_VIEWPORT, view);
        gluProject((GLdouble)x, (GLdouble)y, 0.0,
            model, proj, view,
            &pan_x, &pan_y, &pan_z);
        gluUnProject((GLdouble)x, (GLdouble)y, pan_z,
            model, proj, view,
            &pan_x, &pan_y, &pan_z);
        pan_y = -pan_y;
    }

    glutPostRedisplay();
}

void
motion(int x, int y)
{
    GLdouble model[4*4];
    GLdouble proj[4*4];
    GLint view[4];

    gltbMotion(x, y);

    if (mouse_state == GLUT_DOWN && mouse_button == GLUT_MIDDLE_BUTTON) {
        glGetDoublev(GL_MODELVIEW_MATRIX, model);
        glGetDoublev(GL_PROJECTION_MATRIX, proj);
        glGetIntegerv(GL_VIEWPORT, view);
        gluProject((GLdouble)x, (GLdouble)y, 0.0,
            model, proj, view,
            &pan_x, &pan_y, &pan_z);
        gluUnProject((GLdouble)x, (GLdouble)y, pan_z,
            model, proj, view,
            &pan_x, &pan_y, &pan_z);
        pan_y = -pan_y;
    }

    glutPostRedisplay();
}

int
main(int argc, char** argv)
{
    int buffering = GLUT_DOUBLE;
    struct dirent* direntp;
    DIR* dirp;
    int models;

    glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);
    glutInit(&argc, argv);

    while (--argc) {
        if (strcmp(argv[argc], "-sb") == 0)
            buffering = GLUT_SINGLE;
        else
            model_file = argv[argc];
    }

    if (!model_file) {
        model_file = "data/cube.obj";
    }

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | buffering);
    glutCreateWindow("Smooth");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    //glutMouseFunc(mouse);
    //glutMotionFunc(motion);

    models = glutCreateMenu(menu);
    dirp = opendir(DATA_DIR);
    if (!dirp) {
        fprintf(stderr, "%s: can't open data directory.\n", argv[0]);
    } else {
        while ((direntp = readdir(dirp)) != NULL) {
            if (strstr(direntp->d_name, ".obj")) {
                entries++;
                glutAddMenuEntry(direntp->d_name, -entries);
            }
        }
        closedir(dirp);
    }

    glutCreateMenu(menu);
    glutAddMenuEntry("Smooth", 0);
    glutAddMenuEntry("", 0);
    glutAddSubMenu("Models", models);
    glutAddMenuEntry("", 0);
    glutAddMenuEntry("[w]   Toggle wireframe/filled", 'w');
    glutAddMenuEntry("[c]   Toggle culling on/off", 'c');
    glutAddMenuEntry("[n]   Toggle face/smooth normals", 'n');
    glutAddMenuEntry("[b]   Toggle bounding box on/off", 'b');
    glutAddMenuEntry("[p]   Toggle frame rate on/off", 'p');
    glutAddMenuEntry("[t]   Toggle model statistics", 't');
    glutAddMenuEntry("[m]   Toggle color/material/none mode", 'm');
    glutAddMenuEntry("[r]   Reverse polygon winding", 'r');
    glutAddMenuEntry("[s]   Scale model smaller", 's');
    glutAddMenuEntry("[S]   Scale model larger", 'S');
    glutAddMenuEntry("[o]   Weld redundant vertices", 'o');
    glutAddMenuEntry("[+]   Increase smoothing angle", '+');
    glutAddMenuEntry("[-]   Decrease smoothing angle", '-');
    glutAddMenuEntry("[W]   Write model to file (out.obj)", 'W');
    glutAddMenuEntry("", 0);
    glutAddMenuEntry("[Esc] Quit", 27);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    init();

    glutMainLoop();
    return 0;
}
