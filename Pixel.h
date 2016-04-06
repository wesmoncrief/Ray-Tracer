//
// Created by Wesley Moncrief on 4/5/16.
//

#ifndef RAYTRACING_PIXEL_H
#define RAYTRACING_PIXEL_H


#include "Point.h"

class Pixel {
public:
    Pixel(const Point &p, float r, float g, float b) : p(p), r(r), g(g), b(b) { }
    Point p;
    float r, g, b;
};


#endif //RAYTRACING_PIXEL_H
