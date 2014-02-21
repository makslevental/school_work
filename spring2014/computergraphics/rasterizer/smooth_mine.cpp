
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
#include <algorithm>    // std::min
#pragma comment( linker, "/entry:\"mainCRTStartup\"" )  // set the entry point to be main()

#define DATA_DIR "data/"
#define IMAGE_WIDTH 512
#define IMAGE_HEIGHT 512
#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512
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
static int translation = 2.;
static GLfloat light_src[3] = {-1.,0.,3.};
static GLfloat eye_location[3] = {0.,0, translation};

static int framess = 0;

#define PHONG_EXP 5.0
#define K_S .3
#define K_D .9
#define K_A .9
#define ILLUM .7

static inline void loadbar(unsigned int x, unsigned int n, unsigned int w = 50)
{
    if ( (x != n) && (x % (n/100) != 0) ) return;

    float ratio  =  x/(float)n;
    int   c      =  ratio * w;

    std::cout << std::setw(3) << (int)(ratio*100) << "% [";
    for (int x=0; x<c; x++) std::cout << "=";
    for (int x=c; x<w; x++) std::cout << " ";
    std::cout << "]\r" << std::flush;
}

float
elapsed(void)
{
    static long begin = 0;
    static long finish, difference;

#if defined(_WIN32)
    static struct timeb tb;
    ftime(&tb);
    finish = tb.time*1000+tb.millitm;
#else
    static struct tms tb;
    finish = times(&tb);
#endif

    difference = finish - begin;
    begin = finish;

    return (float)difference/(float)1000;
}

void
shadowtext(int x, int y, char* s)
{
    int lines;
    char* p;

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, glutGet(GLUT_WINDOW_WIDTH),
        0, glutGet(GLUT_WINDOW_HEIGHT), -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3ub(0, 0, 0);
    glRasterPos2i(x+1, y-1);
    for(p = s, lines = 0; *p; p++) {
        if (*p == '\n') {
            lines++;
            glRasterPos2i(x+1, y-1-(lines*18));
        }
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
    }
    glColor3ub(0, 128, 255);
    glRasterPos2i(x, y);
    for(p = s, lines = 0; *p; p++) {
        if (*p == '\n') {
            lines++;
            glRasterPos2i(x, y-(lines*18));
        }
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
    }
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
}

void
lists(void)
{
    GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat shininess = 65.0;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    if (model_list)
        glDeleteLists(model_list, 1);

    /* generate a list */
    if (material_mode == 0) {
        if (facet_normal)
            model_list = glmList(model, GLM_FLAT);
        else
            model_list = glmList(model, GLM_SMOOTH);
    } else if (material_mode == 1) {
        if (facet_normal)
            model_list = glmList(model, GLM_FLAT | GLM_COLOR);
        else
            model_list = glmList(model, GLM_SMOOTH | GLM_COLOR);
    } else if (material_mode == 2) {
        if (facet_normal)
            model_list = glmList(model, GLM_FLAT | GLM_MATERIAL);
        else
            model_list = glmList(model, GLM_SMOOTH | GLM_MATERIAL);
    }
}

static GLvoid
glmScalarMultiple(GLfloat u ,GLfloat* n)
{
    assert(n);

    n[1] = u*n[1];
    n[2] = u*n[2];
    n[0] = u*n[0];
}

static GLvoid
glmSum(GLfloat* u, GLfloat* v, GLfloat* n)
{
    assert(u); assert(v); assert(n);

    n[1] = u[1]+v[1];
    n[2] = u[2]+v[2];
    n[0] = u[0]+v[0];
}

static GLvoid
glmDifference(GLfloat* u, GLfloat* v, GLfloat* n)
{
    assert(u); assert(v); assert(n);

    n[1] = u[1]-v[1];
    n[2] = u[2]-v[2];
    n[0] = u[0]-v[0];
}

void addMaterialToAllTriangles(){
    static GLuint i;
    static GLMgroup* group;

    group = model->groups;
    while(group) {
        for (i = 0; i < group->numtriangles; i++) {
            T(group->triangles[i]).material = group->material;
        }
        group = group->next;
    }
}

void triangleCentroid(GLdouble vertices[3][3], GLfloat* centroid){

    centroid[0] = vertices[0][0] + .5*(vertices[1][0]+vertices[2][0]);
    centroid[1] = vertices[0][1] + .5*(vertices[1][1]+vertices[2][1]);
    centroid[2] = vertices[0][2] + .5*(vertices[1][2]+vertices[2][2]);
    //printf("");
}

void lineMidpoint(GLdouble vertices[2][3], GLfloat* midpoint){
    midpoint[0] = vertices[0][0] + .5*(vertices[1][0]-vertices[0][0]);
    midpoint[1] = vertices[0][1] + .5*(vertices[1][1]-vertices[0][1]);
    midpoint[2] = vertices[0][2] + .5*(vertices[1][2]-vertices[0][2]);
}

double calculateBeta(double z0, double z1, double alpha){
    return alpha*z0/((alpha*z0)+(1-alpha)*z1);
}

void shader(GLfloat* color, GLfloat* normal, GLfloat* lookfrom, GLfloat* lightFrom, GLMmaterial* material){

    GLfloat bisector[3];
    glmSum(lightFrom, lookfrom, bisector);

    glmNormalize(bisector);

//    printf("normal %f %f %f\n", normal[0], normal[1], normal[2]);
//    printf("bisector %f %f %f\n", bisector[0], bisector[1], bisector[2]);
//    printf("lookfrom %f %f %f\n", lookfrom[0], lookfrom[1], lookfrom[2]);
//    printf("lightfrom %f %f %f\n", lightFrom[0], lightFrom[1], lightFrom[2]);

    GLfloat diffuse_color[3] = {material->diffuse[0]*255, material->diffuse[1]*255, material->diffuse[2]*255};
    GLfloat ambient_color[3] = {material->ambient[0]*255,material->ambient[1]*255,material->ambient[2]*255};
    GLfloat specular_color[3] = {material->specular[0]*255,material->specular[1]*255,material->specular[2]*255};

//    printf("diffuse color %f %f %f \n", diffuse_color[0], diffuse_color[1], diffuse_color[2]);
//    printf("ambient color %f %f %f \n", ambient_color[0], ambient_color[1], ambient_color[2]);
//    printf("specular color %f %f %f \n", specular_color[0], specular_color[1], specular_color[2]);

    double norm_dot_light = glmDot(lightFrom,normal);

//    std::cout << "norm_dot_light " << norm_dot_light << std::endl;
    double diffuse_lighting = K_D*std::max(0.,norm_dot_light);
    diffuse_lighting = std::min(255., diffuse_lighting);
    double norm_dot_bi = glmDot(bisector,normal);
//    std::cout << "norm_dot_bi " << norm_dot_bi << std::endl;
    double specular_lighting = K_S*pow(std::max(0.,norm_dot_bi),PHONG_EXP);
    specular_lighting = std::min(255., specular_lighting);

    double ambient_lighting = K_A;

    glmScalarMultiple(ILLUM*diffuse_lighting, (GLfloat*)diffuse_color);
    glmSum((GLfloat*)color, (GLfloat*)diffuse_color, (GLfloat*)color);

    glmScalarMultiple(ILLUM*ambient_lighting, (GLfloat*)ambient_color);
    glmSum((GLfloat*)color, (GLfloat*)ambient_color, (GLfloat*)color);

    glmScalarMultiple(ILLUM*specular_lighting, (GLfloat*)specular_color);
    glmSum((GLfloat*)color, (GLfloat*)specular_color, (GLfloat*)color);
    //printf("color %f %f %f \n\n", color[0], color[1], color[2]);
}

void bresenham(int x0, int y0, double z0, int x1, int y1, double z1, GLfloat* normalVertex1, GLfloat* normalVertex2, GLMmaterial* material){
    int dx = abs(x1-x0);
    int dy = abs(y1-y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx-dy;
    int x = floor(x0);
    int y = floor(y0);
    int e2;
    double distanceFromStart = 0;
    double totalDistance = dx+dy;
    double alpha = 0;
    double beta = 0;
    //shading
    GLfloat color1[3] = {0,0,0};
    GLfloat color2[3] = {0,0,0};
    GLdouble realVertices[2][3];
    GLfloat midpoint[3];
    //recover real vertices of line
    int res=gluUnProject(x0,y0,z0,modelview,projection,viewport,&realVertices[0][0],&realVertices[0][1],&realVertices[0][2]);
    res=gluUnProject(x1,y1,z1,modelview,projection,viewport,&realVertices[1][0],&realVertices[1][1],&realVertices[1][2]);
    //realVertices now contains the vertices in 3 space of the line.

    lineMidpoint(realVertices, midpoint);

    //lookfrom vector, vector view screen to eye, which is the same vector as from the center of triangle to eye
//    GLfloat lookFrom[3] = {eye_location[0] - midpoint[0], eye_location[1] - midpoint[1], eye_location[2] - midpoint[2]};
//    GLfloat lightFrom[3] = {light_src[0] - midpoint[0], light_src[1] - midpoint[1], light_src[2] - midpoint[2]};
    GLfloat lookFrom1[3] = {eye_location[0] - realVertices[0][0], eye_location[1] - realVertices[0][1], eye_location[2] - realVertices[0][2]};
    GLfloat lightFrom1[3] = {light_src[0] - realVertices[0][0], light_src[1] - realVertices[0][1], light_src[2] - realVertices[0][2]};
    glmNormalize(lookFrom1);
    glmNormalize(lightFrom1);
    shader(color1, normalVertex1, lookFrom1, lightFrom1, material);

    GLfloat lookFrom2[3] = {eye_location[0] - realVertices[1][0], eye_location[1] - realVertices[1][1], eye_location[2] - realVertices[1][2]};
    GLfloat lightFrom2[3] = {light_src[0] - realVertices[1][0], light_src[1] - realVertices[1][1], light_src[2] - realVertices[1][2]};
    glmNormalize(lookFrom2);
    glmNormalize(lightFrom2);
    shader(color2, normalVertex2, lookFrom2, lightFrom2, material);
//    printf("vertnormal1 %f %f %f vertnormal2 %f %f %f\n", normalVertex1[0], normalVertex1[1], normalVertex1[2], normalVertex2[0], normalVertex2[1], normalVertex2[2]);
//    printf("color1 %f %f %f color2 %f %f %f\n", color1[0], color1[1], color1[2], color2[0], color2[1], color2[2]);

    while(true){

        alpha = distanceFromStart/totalDistance;
        beta = calculateBeta(z0,z1,alpha);
        framebuffer[y][x][0] = 1;
        //printf("scaled method %f \n", z0+calculateBeta(z0,z1,alpha)*(z1-z0));
        framebuffer[y][x][1] = z0+beta*(z1-z0);
        //printf("scaled framebuffer %f \n", framebuffer[y][x][1]);
        framebuffer[y][x][2] =double(color1[0]) + (double(color2[0]-color1[0])*beta);
        framebuffer[y][x][3] =double(color1[1]) + (double(color2[1]-color1[1])*beta);
        framebuffer[y][x][4] =double(color1[2]) + (double(color2[2]-color1[2])*beta);
        //printf("%f %f %f beta %f \n", framebuffer[y][x][2], framebuffer[y][x][3], framebuffer[y][x][4], beta);

        e2 = 2*err;
        if(x==x1 && y==y1){
                break;
        }
        if(e2 > -dy){
            err -= dy;
            distanceFromStart++;
            x += sx;
        }
        if(x==x1 && y==y1){
            alpha = distanceFromStart/totalDistance;
            beta = calculateBeta(z0,z1,alpha);
            framebuffer[y][x][0] = 1;
            //printf("scaled method %f \n", z0+calculateBeta(z0,z1,alpha)*(z1-z0));
            framebuffer[y][x][1] = z0+beta*(z1-z0);
            //printf("scaled framebuffer %f \n", framebuffer[y][x][1]);
            double scaled = framebuffer[y][x][1];
            //scaled = 1;
            framebuffer[y][x][2] =double(color1[0]) + (double(color2[0]-color1[0])*beta);
            framebuffer[y][x][3] =double(color1[1]) + (double(color2[1]-color1[1])*beta);
            framebuffer[y][x][4] =double(color1[2]) + (double(color2[2]-color1[2])*beta);
            //printf("alpha %f z0 %f z1 %f x %d  y %f %f %f scaled %f \n", alpha, z0, z1, x, y, framebuffer[y][x][2], framebuffer[y][x][3], framebuffer[y][x][4], scaled);
            break;
        }
        if(e2 < dx){
            err += dx;
            distanceFromStart++;
            y += sy;
        }
    }
}


void scanlineTriangleToFrameBuffer(double vertices[3][3], GLfloat* normal, GLMmaterial* material){
    int minx = floor(std::min({vertices[0][0], vertices[1][0], vertices[2][0]}));
    int miny = floor(std::min({vertices[0][1], vertices[1][1], vertices[2][1]}));
    int maxx = ceil(std::max({vertices[0][0], vertices[1][0], vertices[2][0]}));
    int maxy = ceil(std::max({vertices[0][1], vertices[1][1], vertices[2][1]}));

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
                double* colorLeft = &framebuffer[y][crossings[1][0]][2];
                double* colorRight = &framebuffer[y][crossings[2][1]][2];
//                printf("colorleft %f %f %f \n", colorLeft[0], colorLeft[1], colorLeft[2]);
//                printf("colorRight %f %f %f \n", colorRight[0], colorRight[1], colorRight[2]);
                double totalAlpha = abs(crossings[1][1] - crossings[2][1]) - 1;
                double beta = 0;
                double scaled = 0;
                for(int k = crossings[1][1]; k < crossings[2][1]; k++){
                    beta = totalAlpha == 0 ? 0 : calculateBeta(zleft,zright,double(k-crossings[1][1])/totalAlpha);
                    scaled = zleft+beta*(zright-zleft);
                    framebuffer[y][k][1] = scaled;
                    framebuffer[y][k][2] =colorLeft[0] + (double(colorRight[0]-colorLeft[0])*beta);
                    framebuffer[y][k][3] =colorLeft[1] + (double(colorRight[1]-colorLeft[1])*beta);
                    framebuffer[y][k][4] =colorLeft[2] + (double(colorRight[2]-colorLeft[2])*beta);

                    //printf("scanline %d %d %d %d %d %f \n", y, k, framebuffer[y][k][2], framebuffer[y][k][3], framebuffer[y][k][4], scaled);
                }
                //printf("end scanline \n");
        }
    }
}


//model is global
void plotTriangleToFrameBuffer(GLMtriangle* triangle){
    //get the opengl matrices
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    GLfloat normal[3] = {(GLfloat)model->facetnorms[3*triangle->findex],(GLfloat)model->facetnorms[3*triangle->findex+1],(GLfloat)model->facetnorms[3*triangle->findex+2]};

    double vertices[3][3];
    GLfloat vertnormals[3][3];
    for(int j = 0; j < 3; j++){
        GLuint vindex = triangle->vindices[j];
        GLuint normalindex = triangle->nindices[j];
        GLdouble winX, winY, winZ;//2D point

        GLfloat posX = model->vertices[3*vindex+0];
        GLfloat posY = model->vertices[3*vindex+1];
        GLfloat posZ = model->vertices[3*vindex+2];

        vertnormals[j][0] = model->normals[3*normalindex+0];
        vertnormals[j][1] = model->normals[3*normalindex+1];
        vertnormals[j][2] = model->normals[3*normalindex+2];

        int res=gluProject(posX,posY,posZ,modelview,projection,viewport,&winX,&winY,&winZ);
        vertices[j][0] = winX;
        vertices[j][1] = winY;
        vertices[j][2] = winZ;
//        printf("posx %f posy %f posx %f \n", posX, posY, posZ);
//        printf("winx %f winy %f winz %f \n", winX, winY, winZ);
    }


//    printf("normal %f %f %f \n", normal[0], normal[1], normal[2]);

    GLMmaterial* triangleMaterial = &model->materials[triangle->material];

    bresenham(vertices[0][0],vertices[0][1], vertices[0][2], vertices[1][0], vertices[1][1], vertices[1][2], vertnormals[0], vertnormals[1], triangleMaterial);
    bresenham(vertices[1][0],vertices[1][1], vertices[1][2], vertices[2][0], vertices[2][1], vertices[2][2], vertnormals[1], vertnormals[2], triangleMaterial);
    bresenham(vertices[2][0],vertices[2][1], vertices[2][2], vertices[0][0], vertices[0][1], vertices[0][2], vertnormals[2], vertnormals[0], triangleMaterial);
    scanlineTriangleToFrameBuffer(vertices, normal, triangleMaterial);
}


void swapImageAndFrameBuffer(){
    for(int y = 0; y < IMAGE_HEIGHT; y++)
        for(int x = 0; x < IMAGE_WIDTH; x++){
            //printf("zbuffer %f framebuffer %f \n", zbuffer[y][x], framebuffer[y][x][1]);
            if( zbuffer[y][x] - framebuffer[y][x][1] > .01 ){
                zbuffer[y][x] = framebuffer[y][x][1];
                image[y][x][0] = (GLubyte)framebuffer[y][x][2];
                image[y][x][1] = (GLubyte)framebuffer[y][x][3];
                image[y][x][2] = (GLubyte)framebuffer[y][x][4];
            }
        }
}

void raster(){
    addMaterialToAllTriangles();
    GLMtriangle* triangle;
    for(int i = 0; i < model->numtriangles; i++){
//    int j = 8;
//    for(int i = j; i < j+1/*model->numtriangles*/; i++){
        memset(framebuffer, 0, sizeof(framebuffer));
        for(int m = 0; m < IMAGE_HEIGHT; m++)
            for(int n = 0; n < IMAGE_WIDTH; n++){
                framebuffer[m][n][1] = 10000;
            }
        //std::cout << "triangle " << i+1 << std::endl;
        //printf("triangle vertex indices %d %d %d \n", 3*model->triangles[i].vindices[0], 3*model->triangles[i].vindices[1], 3*model->triangles[i].vindices[2]);

        triangle = &model->triangles[i];
        plotTriangleToFrameBuffer(triangle);
        swapImageAndFrameBuffer();
        loadbar(10*(i+1), 10*(model->numtriangles));
    }
}


void
init(void)
{
    gltbInit(GLUT_LEFT_BUTTON);

    /* read in the model */
    model = glmReadOBJ(model_file);
    scale = glmUnitize(model);
    glmFacetNormals(model);
    glmVertexNormals(model, smoothing_angle);

    if (model->nummaterials > 0)
        material_mode = 2;

    /* create new display lists */
    lists();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

}

void
reshape(int width, int height)
{
    gltbReshape(width, height);

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -1*(translation+1)); //pushes the viewport back to z=2
}

#define NUM_FRAMES 5
void
display(void)
{
    static char s[256], t[32];
    static char* p;
    static int frames = 0;

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glTranslatef(pan_x, pan_y, 0.0);

    gltbMatrix();

#if 0   /* glmDraw() performance test */
    if (material_mode == 0) {
        if (facet_normal)
            glmDraw(model, GLM_FLAT);
        else
            glmDraw(model, GLM_SMOOTH);
    } else if (material_mode == 1) {
        if (facet_normal)
            glmDraw(model, GLM_FLAT | GLM_COLOR);
        else
            glmDraw(model, GLM_SMOOTH | GLM_COLOR);
    } else if (material_mode == 2) {
        if (facet_normal)
            glmDraw(model, GLM_FLAT | GLM_MATERIAL);
        else
            glmDraw(model, GLM_SMOOTH | GLM_MATERIAL);
    }
#else
    glCallList(model_list);
#endif

    glDisable(GL_LIGHTING);
    if (bounding_box) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glEnable(GL_CULL_FACE);
        glColor4f(1.0, 0.0, 0.0, 0.25);
        glutSolidCube(2.0);
        glDisable(GL_BLEND);
    }

    glPopMatrix();

    if (stats) {
        /* XXX - this could be done a _whole lot_ faster... */
        int height = glutGet(GLUT_WINDOW_HEIGHT);
        glColor3ub(0, 0, 0);
        sprintf(s, "%s\n%d vertices\n%d triangles\n%d normals\n"
            "%d texcoords\n%d groups\n%d materials",
            model->pathname, model->numvertices, model->numtriangles,
            model->numnormals, model->numtexcoords, model->numgroups,
            model->nummaterials);
        shadowtext(5, height-(5+18*1), s);
    }

    /* spit out frame rate. */
    frames++;
    if (frames > NUM_FRAMES) {
        sprintf(t, "%g fps", frames/elapsed());
        frames = 0;
    }
    if (performance) {
        shadowtext(5, 5, t);
    }

    glutSwapBuffers();
    glEnable(GL_LIGHTING);
    GLfloat position1[4];
    glGetLightfv(GL_LIGHT0, GL_POSITION, position1);
    //printf("light %f %f %f %f \n", position1[0], position1[1], position1[2], position1[3]);
}

void
display1(void)
{

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(pan_x, pan_y, 0.0);
    gltbMatrix();
    if(framess++ % NUM_FRAMES == 0 ){
        for(int i = 0; i < IMAGE_WIDTH; i++)
            for(int j = 0; j < IMAGE_WIDTH; j++){
                image[i][j][0] = 255;
                image[i][j][1] = 255;
                image[i][j][2] = 255;
                zbuffer[i][j] = 10000;
            }
        raster();
        if(framess > 10000)
            framess = 1;
    }
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

    case 'r':
        glmReverseWinding(model);
        lists();
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

    case 'R':
        {
            GLuint i;
            GLfloat swap;
            for (i = 1; i <= model->numvertices; i++) {
                swap = model->vertices[3 * i + 1];
                model->vertices[3 * i + 1] = model->vertices[3 * i + 2];
                model->vertices[3 * i + 2] = -swap;
            }
            glmFacetNormals(model);
            lists();
            break;
        }

    case 27:
        exit(0);
        break;

    case 'y':
        glutDisplayFunc(display1);
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
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

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
