//
// Created by Wesley Moncrief on 4/5/16.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H


#include "Point.h"
#include "Pixel.h"

class Sphere {
    Point center;
    double radius;
    float r, g, b; //color of object
    double ambient_coefficient = .5;


public:
    Sphere(Point center, double radius, float r, float g, float b)
            : center(center), radius(radius), r(r), g(g), b(b) { }

private:
//this returns a pixel so that it has color and location information.
    //this location information can be used if a ray intersects multiple
    //objects. it will help determine which one to draw.
    Pixel intersect(int x, int y){

    }



};


#endif //RAYTRACING_SPHERE_H
