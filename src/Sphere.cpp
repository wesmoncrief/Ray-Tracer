//
// Created by Wesley Moncrief on 4/6/16.
//

#include <cmath>
#include "Sphere.h"
#include "LightSource.h"

//when two solutions, this returns the minimum
bool quadratic(double a, double b, double c, double &t) {
    //should this enforce that t is positive?

    double descrim = b * b - 4 * a * c;
    if (descrim < 0)//no intersection
        return false;
    if (descrim == 0) {//one intersection
        t = -(1 * b) / (2 * a);
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


bool Sphere::intersect(Ray ray,
                       Pixel &pixel) { //todo should this return a boolean? How to handle cases with no intersection?
    //the math and the naming for this function come from lecture 15 slide 43, Dr. Chai

    //p_naught_minus_o is the vector created by (Po (the starting point of the ray) - O (center of sphere)).
    Vec3 p_naught_minus_o(ray.start.x - center.x, ray.start.y - center.y, ray.start.z - center.z);
    double b = 2 * (ray.V.dotProduct(p_naught_minus_o));
    //http://www.vis.uky.edu/~ryang/teaching/cs535-2012spr/Lectures/13-RayTracing-II.pdf
    //somehow my implementation of the wikipedia way was wrong but this, from above link, worked like a charm.
    double c =
            ray.start.x * ray.start.x - 2 * ray.start.x * center.x + center.x * center.x + ray.start.y * ray.start.y -
            2 * ray.start.y * center.y + center.y * center.y + ray.start.z * ray.start.z - 2 * ray.start.z * center.z +
            center.z * center.z - radius * radius;
    //check to make sure unit vector
    double t;
    if (!quadratic(1.0, b, c, t))
        return false;
    //P = P_o + tV
    Point intersect_pt(ray.start.x + t * ray.V.x, ray.start.y + t * ray.V.y, ray.start.z + t * ray.V.z);


    Color co(0, 0, 0); //todo remove this
    //color is Direct (ambient + diffuse + specular) + reflected + refracted...
    Color ambient = calc_ambient();
    Color diffuse = calc_diffuse(intersect_pt);
    Color direct_color = ambient.sum(diffuse);
    Color specular = calc_specular(intersect_pt);
    direct_color = direct_color.sum(specular);
    pixel = Pixel(intersect_pt, direct_color);
    return true;
}

Color Sphere::calc_diffuse(Point intersect_pt) {

    LightSource ls(Point(00, 40, 900), Color(.5, .5, .5)); //todo remove this temporary light source, put it into scene

    //I = intensity of point light * diffuse reflection coefficient * (light vector dotted with normal vector)
    //todo to see if there is occlusion, run intersection on light vector and scene!

    //should L, N be unit vectors? N should probably be...
    //N is
    Vec3 N = Vec3(intersect_pt.x - center.x, intersect_pt.y - center.y, intersect_pt.z - center.z);
    N.normalize();

    //L is lightsource vector
    Vec3 L = Vec3(ls.light_center.x - intersect_pt.x, ls.light_center.y - intersect_pt.y,
                  ls.light_center.z - intersect_pt.z);
    L.normalize();
    double LdotN = L.dotProduct(N);
    double coeff = diffuse_coeff * LdotN;


    return Color(coeff * ls.light_color.r, coeff * ls.light_color.b, coeff * ls.light_color.g);
}

Color Sphere::calc_specular(Point intersect_pt) {
    //i'm assuming all the vectors described are normalized
    //I = C * spec_refl_coeff * (R dot E) ^spec_n_value
    //todo remove the eye point from being hardcoded in, put it in the scene

    Point eye_pt(0, 0, 40);
    Vec3 E(eye_pt.x - intersect_pt.x, eye_pt.y - intersect_pt.y, eye_pt.z - intersect_pt.z);
    E.normalize();

    LightSource ls(Point(00, 40, 900), Color(1, 1, 1)); //todo remove this temporary light source, put it into scene
    Vec3 L = Vec3(ls.light_center.x - intersect_pt.x, ls.light_center.y - intersect_pt.y,
                  ls.light_center.z - intersect_pt.z);
    L.normalize();

    Vec3 N = Vec3(intersect_pt.x - center.x, intersect_pt.y - center.y, intersect_pt.z - center.z);
    N.normalize();

    double n_coef = 2 * L.dotProduct(N);
    Vec3 R(n_coef * N.x - L.x, n_coef * N.y - L.y, n_coef * N.z - L.z);

    double RdotE = R.dotProduct(E);
    double powerRdotE = pow(RdotE, specular_n_value);
    double full_coeff = specular_refl_coeff * powerRdotE;
    if (full_coeff < 0) full_coeff = 0;
    Color c(full_coeff * ls.light_color.r, full_coeff * ls.light_color.b, full_coeff * ls.light_color.g);
    return c;
}


Color Sphere::calc_ambient() {
    return Color(sphere_color.r * ambient_coeff, sphere_color.g * ambient_coeff, sphere_color.b * ambient_coeff);
}








