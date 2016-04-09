//
// Created by Wesley Moncrief on 4/9/16.
//

#ifndef RAYTRACING_SHAPE_H
#define RAYTRACING_SHAPE_H

#include <vector>
using namespace std;

class Shape {
public:
    Point eye_pt;
    Color shape_color;
    double ambient_coeff;
    double diffuse_coeff;
    double specular_refl_coeff ;
    double specular_n_value;


    virtual bool intersect(Ray ray, vector<LightSource> lights, vector<Shape*> shapes, Pixel& pixel) = 0;

    virtual bool is_occluding(Ray shadow_ray, LightSource light) = 0;

};


#endif //RAYTRACING_SHAPE_H
