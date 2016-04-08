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
    Vec3() { }

    Vec3(double x, double y, double z) : x(x), y(y), z(z) { }

    double dotProduct(Vec3 v) {
        return (x * v.x + y * v.y + z * v.z);
    }

    void normalize() {
        double magnitude = sqrt(x * x + y * y + z * z);
        x = x / magnitude;
        y = y / magnitude;
        z = z / magnitude;
    }
};


#endif //RAYTRACING_VEC3_H
