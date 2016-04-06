//
// Created by Wesley Moncrief on 4/6/16.
//

#ifndef RAYTRACING_LIGHTSOURCE_H
#define RAYTRACING_LIGHTSOURCE_H


#include "Point.h"
#include "Color.h"

class LightSource {
public:
    Point light_center;
    Color light_color;


    LightSource() { }

    LightSource(const Point &light_center, const Color &light_color) : light_center(light_center),
                                                                       light_color(light_color) { }
};


#endif //RAYTRACING_LIGHTSOURCE_H
