//
// Created by Wesley Moncrief on 4/5/16.
//

#ifndef RAYTRACING_INFINITEPLANE_H
#define RAYTRACING_INFINITEPLANE_H

#include "Ray.h"
#include "Point.h"


class InfinitePlane {
private:
    double a;
    double b;
    double c;
    double d;

    //will need additional values for coefficients

public:
    //creates plane in general form.
    InfinitePlane(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) { }

    //returns the first point intersected with
//    Point intersect(int x, int y) {
//
//        return nullptr;
//    }


};


#endif //RAYTRACING_INFINITEPLANE_H
