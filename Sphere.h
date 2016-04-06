//
// Created by Wesley Moncrief on 4/5/16.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include <iostream>
#include "Point.h"
#include "Pixel.h"
#include "Ray.h"

using namespace std;

class Sphere {
    Point center;
    double radius;
    float r, g, b; //color of object
    double ambient_coefficient = .5;


public:
    Sphere(Point center, double radius, float r, float g, float b)
            : center(center), radius(radius), r(r), g(g), b(b) { }


    //when two solutions, this returns the minimum

    //this returns a boolean and modifies the pixel so that it has color and location information.
    //Pixel information can be used if a ray intersects multiple
    //objects. it will help determine which one to draw.
    //boolean is useful for when there is no intersection.
    bool intersect(Ray r, Pixel &pixel);


};

//when two solutions, this returns the minimum
bool quadratic(double a, double b, double c, double &t);

bool Sphere::intersect(Ray r,
                       Pixel &pixel) { //todo should this return a boolean? How to handle cases with no intersection?
//the math and the naming for this function come from lecture 15 slide 43, Dr. Chai

//p_naught_minus_o is the vector created by (Po (the starting point of the ray) - O (center of sphere)).
    Vec3 p_naught_minus_o(r.start.x - center.x, r.start.y - center.y, r.start.z - center.z);
    double b = 2 * (r.V.dotProduct(p_naught_minus_o));
    double t;
    if (!quadratic(1.0, b, 0.0, t)) {
        cout << "Sphere intersection is imaginary. Therefore no intersection" << endl;
        return false;
    }

    //P = P_o + tV
    Point intersect_pt(r.start.x + t * r.V.x, r.start.y + t * r.V.y, r.start.z + t * r.V.z);
    pixel = Pixel(intersect_pt, this->r, g, b);
    return true;
    //todo multiply point by ambient_coeff when creating pixel
}

//when two solutions, this returns the minimum
bool quadratic(double a, double b, double c, double &t) {
    //should this enforce that t is positive?

    double descrim = b * b - 4 * a * c;
    if (descrim < 0)
        return false;
    double desc_root = sqrt(descrim);
    double r1 = (-b + desc_root) * 0.5 / a;
    double r2 = (-b - desc_root) * 0.5 / a;
    if (r1 < 0 && r2 < 0) {
        cout << "Sphere intersect -> quadratic has two negative roots." << endl;
    }
    if (r1 < r2) t = r1;
    else t = r2;

    return true;
}


#endif //RAYTRACING_SPHERE_H
