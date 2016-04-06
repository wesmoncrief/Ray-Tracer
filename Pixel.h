//
// Created by Wesley Moncrief on 4/5/16.
//

#ifndef RAYTRACING_PIXEL_H
#define RAYTRACING_PIXEL_H


#include "Point.h"

class Pixel {
public:
    Pixel();

    Pixel(Point point, float r, float g, float b) : point(point), r(r), g(g), b(b) { }
    Point point;
    float r, g, b;
};

Pixel::Pixel() {

}


#endif //RAYTRACING_PIXEL_H
