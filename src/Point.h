//
// Created by Wesley Moncrief on 4/5/16.
//

#ifndef RAYTRACING_POINT_H
#define RAYTRACING_POINT_H


class Point {
public:
    double x;
    double y;
    double z;

    Point() { }

    Point(double x, double y, double z) : x(x), y(y), z(z) { }

};



#endif //RAYTRACING_POINT_H
