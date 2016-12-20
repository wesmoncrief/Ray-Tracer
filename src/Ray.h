//
// Created by Wesley Moncrief on 4/5/16.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H


#include "Point.h"
#include "Vec3.h"

class Ray : public Vec3 {
    //assume all rays travel parallel the axis going into the screen

    //this is the point on the screen
    //it should take the view_distance as the z parameter

    //this is the direction that the ray is moving in in the
    //x, y, and z axis.


public:


    Ray(Point _start, Vec3 direction) {
        start = _start;
        V = direction;
        V.normalize();
    }

    Vec3 V;
    Point start;
};


#endif //RAYTRACING_RAY_H
