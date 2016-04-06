//
// Created by Wesley Moncrief on 4/6/16.
//

#include <cmath>
#include "Sphere.h"

//when two solutions, this returns the minimum
//when two solutions, this returns the minimum
bool quadratic(double a, double b, double c, double &t) {
    //should this enforce that t is positive?

    double descrim = b * b - 4 * a * c;
    if (descrim < 0)//no intersection
        return false;
    if (descrim == 0){//one intersection
        t = -(1*b) / (2*a);
        return true;
    }
    double desc_root = sqrt(descrim);
    double r1 = (-b + desc_root) * 0.5 / a;
    double r2 = (-b - desc_root) * 0.5 / a;

    //should this never give a zero for a root?
    if (r1 < 0 && r2 < 0) {
//        cout << "Sphere intersect -> quadratic has two negative roots." << endl;
    }
    if (r1 < r2 && r1 > 0) t = r1;
    if (r2 < r1 && r2 > 0) t = r2;

    return true;
}


bool Sphere::intersect(Ray ray, Pixel &pixel) { //todo should this return a boolean? How to handle cases with no intersection?
    //the math and the naming for this function come from lecture 15 slide 43, Dr. Chai

    //p_naught_minus_o is the vector created by (Po (the starting point of the ray) - O (center of sphere)).
    Vec3 p_naught_minus_o(ray.start.x - center.x, ray.start.y - center.y, ray.start.z - center.z);
    double b = 2 * (ray.V.dotProduct(p_naught_minus_o));
    //http://www.vis.uky.edu/~ryang/teaching/cs535-2012spr/Lectures/13-RayTracing-II.pdf
    //somehow my implementation of the wikipedia way was wrong but this, from above link, worked like a charm.
    double c = ray.start.x*ray.start.x - 2*ray.start.x*center.x + center.x*center.x + ray.start.y*ray.start.y -
               2*ray.start.y*center.y + center.y*center.y + ray.start.z*ray.start.z - 2*ray.start.z*center.z + center.z*center.z - radius*radius;
    //check to make sure unit vector
    double t;
    if (!quadratic(1.0, b, c, t))
        return false;
    //P = P_o + tV
    Point intersect_pt(ray.start.x + t * ray.V.x, ray.start.y + t * ray.V.y, ray.start.z + t * ray.V.z);


    //color is Direct (ambient + diffuse + specular) + reflected + refracted...
    Color ambient = calc_ambient();
    Color diffuse = calc_diffuse();
    Color direct_color = ambient.sum(diffuse);
    pixel = Pixel(intersect_pt, direct_color);
    return true;
    //todo multiply point by ambient_coeff when creating pixel
}

Color Sphere::calc_diffuse() {
    return Color();
}

Color Sphere::calc_ambient() {
    return Color(sphere_color.r * ambient_coefficient, sphere_color.g * ambient_coefficient, sphere_color.b * ambient_coefficient);
}



