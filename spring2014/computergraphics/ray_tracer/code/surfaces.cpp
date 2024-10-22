#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <GL/glut.h> // GLubyte

#include "surfaces.h"


GLubyte_vec* surface::shader(dbl_vec point){
    static GLubyte_vec shades[3];
    // static because perspective RAY direction (not perspective pixel itself) is the same globally
    static dbl_vec bisector = (light_src + -1*ray_directiion)/norm_2(light_src + -1*ray_directiion);
    GLubyte_vec this_color(3, std::vector<GLubyte>{this->color[0],this->color[1],this->color[2]});

    double norm_dot_light = inner_prod(this->unit_normal(point),unit_light_src);
    double diffuse_lighting = K_D*std::max(0.,norm_dot_light);
    double norm_dot_bi = inner_prod(this->unit_normal(point),bisector);
    double specular_lighting = K_S*pow(std::max(0.,norm_dot_bi),PHONG_EXP);
    double ambient_lighting = K_A;
    double illum = ILLUM;
    shades[0] = illum*diffuse_lighting*this_color;
    shades[1] = illum*specular_lighting*GLubyte_white;    
    shades[2] = illum*ambient_lighting*GLubyte_pink;

    return shades;
}
  




triangle::triangle(GLubyte surface_color[3], dbl_vec vertA, dbl_vec vertB, dbl_vec vertC){
    this->vertexA = vertA;
    this->vertexB = vertB;
    this->vertexC = vertC;
    this->edgeAB = vertexB - vertexA;
    this->edgeBC = vertexC - vertexB;
    this->edgeCA = vertexA - vertexC;
    this->plucker_edgeAB[0] = edgeAB;
    this->plucker_edgeAB[1] = cross_product(edgeAB, vertexA);
    this->plucker_edgeBC[0] = edgeBC;
    this->plucker_edgeBC[1] = cross_product(edgeBC, vertexB);
    this->plucker_edgeCA[0] = edgeCA;
    this->plucker_edgeCA[1] = cross_product(edgeCA, vertexC);
    this->normal = cross_product(edgeAB, edgeBC)/norm_2(cross_product(edgeAB, edgeBC));
    color[0] = surface_color[0];
    color[1] = surface_color[1];
    color[2] = surface_color[2];
  } 

dbl_vec triangle::unit_normal(dbl_vec){
    return this->normal; 
  }

double triangle::intersection_test(dbl_vec ray_start_vec, dbl_vec ray_dir_vec){
    // U_r = ray_dir V_r = ray_dir \cross ray_start
    // p_r = {U_r : V_r}
    // p_r circdot p_s = U_r.V_s + U_s.V_r

    dbl_vec U_r = ray_dir_vec;
    dbl_vec V_r = cross_product(ray_dir_vec, ray_start_vec);
    long double sidetestAB = inner_prod(U_r,plucker_edgeAB[1]) + inner_prod(plucker_edgeAB[0],V_r);
    long double sidetestBC = inner_prod(U_r,plucker_edgeBC[1]) + inner_prod(plucker_edgeBC[0],V_r);
    long double sidetestCA = inner_prod(U_r,plucker_edgeCA[1]) + inner_prod(plucker_edgeCA[0],V_r);


    long double norm_plucker = sidetestAB + sidetestBC + sidetestCA;
    // if the abs of the sum == sum of abs then they're all the same sign, saturates cauchy schwarz inequality
    double diff = abs( abs(norm_plucker) - ( abs(sidetestAB)+abs(sidetestBC)+abs(sidetestCA) ) );

    if ( norm_plucker != 0 && ( diff < 10. ) ){
      long_dbl_vec u_k(3, std::vector<long double>{sidetestAB/norm_plucker, sidetestBC/norm_plucker, sidetestCA/norm_plucker});
      dbl_vec intersection_point = u_k[0]*vertexA + u_k[1]*vertexB + u_k[2]*vertexC;
      return (intersection_point[0]-ray_start_vec[0])/ray_dir_vec[0];
    }
    else{
      return -1.;
    }
}

void triangle::test(){
    std::cout << "vertex A " << vertexA << std::endl;
    std::cout << "vertex B " << vertexB << std::endl;
    std::cout << "vertex C " << vertexC << std::endl;
    std::cout << "edgeAB " << edgeAB << std::endl;
    std::cout << "edgeBC " << edgeBC << std::endl;
    std::cout << "edgeCA " << edgeCA << std::endl;
    std::cout << "edgeAB X edgeBC " << cross_product(edgeAB, edgeBC) << std::endl;
    std::cout << "triangle normal " << unit_normal(light_src) << std::endl;
    std::cout << "plucker coordinates edgeAB " << plucker_edgeAB[0] << ":" << plucker_edgeAB[1] << std::endl;
    std::cout << "plucker coordinates edgeBC " << plucker_edgeBC[0] << ":" << plucker_edgeBC[1] << std::endl;
    std::cout << "plucker coordinates edgeCA " << plucker_edgeCA[0] << ":" << plucker_edgeCA[1] << std::endl;
    std::cout << "view plane vec " << prod(rotation,dbl_vec(3,std::vector<double>{1000,1,1})) << std::endl;
    std::cout << this->intersection_test(prod(rotation,dbl_vec(3,std::vector<double>{1000,1,1})), ray_directiion) << std::endl;
    std::cout << this->intersection_test(dbl_vec(3,std::vector<double>{1000,10,10}), ray_directiion) << std::endl;
}
  



  
sphere::sphere(GLubyte surface_color[3], int_vec center, double radius){
    color[0] = surface_color[0];
    color[1] = surface_color[1];
    color[2] = surface_color[2];
    this->center = center;
    this->radius = radius;
}

dbl_vec sphere::unit_normal(dbl_vec point){
    dbl_vec normal = point - this->center;
    return normal/norm_2(normal);
}


double sphere::intersection_test(dbl_vec ray_start_vec, dbl_vec ray_dir_vec){

    dbl_vec pov_to_center = ray_start_vec - center;
    double v_dot_d = inner_prod(pov_to_center, ray_dir_vec);
    double vSquared = inner_prod(pov_to_center, pov_to_center);
    double rSquared = radius*radius;
    double discr = v_dot_d*v_dot_d - (vSquared - rSquared);

    if( discr > 0 ){
      double sqrtdiscr = sqrt(discr);
      double t1 = -(v_dot_d) + sqrtdiscr;
      double t2 = -(v_dot_d) - sqrtdiscr;
      return std::min(t1,t2);
    }
    else{
      return -1;
    }
    return 0;
    
}
  
void sphere::test(){
}

