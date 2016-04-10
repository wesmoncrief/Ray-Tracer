//
// Created by Wesley Moncrief on 4/5/16.
//

#ifndef RAYTRACING_VEC3_H
#define RAYTRACING_VEC3_H

#include <math.h>

class Vec3 {
public:
    double x;
    double y;
    double z;


public:
    Vec3() { x=0, y=0, z=0; }

    Vec3(double x, double y, double z) : x(x), y(y), z(z) { }

    Vec3(Point pt) {
        x = pt.x;
        y = pt.y;
        z = pt.z;
    }

    double dotProduct(Vec3 v) const {
        return (x * v.x + y * v.y + z * v.z);
    }

    void normalize() {
        double magnitude = sqrt(x * x + y * y + z * z);
        x = x / magnitude;
        y = y / magnitude;
        z = z / magnitude;
    }

    Vec3 scaled(double scale) {
        return Vec3(x * scale, y * scale, z * scale);
    }
};


#endif //RAYTRACING_VEC3_H
