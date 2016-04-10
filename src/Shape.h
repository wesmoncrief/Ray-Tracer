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
    double specular_refl_coeff;
    double specular_n_value;

    int count_max = 3;

    virtual bool intersect(const Ray &ray, const vector<LightSource> &lights, vector<Shape *> shapes, int count,
                           Pixel &pixel) = 0;

    virtual bool is_occluding(const Ray &shadow_ray, const LightSource &light) const = 0;

    //for future idea, a lot of the code for calculating diffuse light and specular light
    //is independent of the shape. I could pull this out and implement it in Shape

};


#endif //RAYTRACING_SHAPE_H
