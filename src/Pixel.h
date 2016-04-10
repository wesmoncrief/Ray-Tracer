//
// Created by Wesley Moncrief on 4/5/16.
//

#ifndef RAYTRACING_PIXEL_H
#define RAYTRACING_PIXEL_H


#include "Point.h"
#include "Color.h"

class Pixel {
public:

    Pixel() { color = Color(); }

    Pixel(const Point &point, const Color &color) : point(point), color(color) { }

    Point point;
    Color color;
};


#endif //RAYTRACING_PIXEL_H
