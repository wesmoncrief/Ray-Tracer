//
// Created by Wesley Moncrief on 4/9/16.
//

#include "Plane.h"

bool Plane::get_intersect_pt(Ray ray, Point &pt) {
    //t = -(Po dot N + d) / (V dot N), V is ray vector, N is plane vector, Po is ray point
    //P = Po + tV

    //t = -(ray.point dot normal + d) / (ray.vec dot N)
    double PoDotN = Vec3(ray.start).dotProduct(normal);
    double numerator = -1 *(PoDotN + d);
    double denom = ray.V.dotProduct(normal);
    double t = numerator / denom;
    if (t <0 ) return false;
    Vec3 dist = ray.V.scaled(t);
    pt = Point(ray.start.x + dist.x, ray.start.y + dist.y, ray.start.z + dist.z);

    return true;
}

bool Plane::intersect(Ray ray, vector<LightSource> lights, vector<Shape *> shapes, Pixel &pixel) {
    Point intersect_pt;
    if (!get_intersect_pt(ray, intersect_pt)) return false; //else the intersect_pt is updated

    //color is Direct (ambient + diffuse + specular) + reflected + //refracted...
    //if i add attenuation to plane, should I add it here?
    Color ambient = calc_ambient();
//    Color diffuse = calc_diffuse(intersect_pt, lights, shapes);
//    Color direct_color = ambient.sum(diffuse);
//    Color specular = calc_specular(intersect_pt, lights, shapes);
//    direct_color = direct_color.sum(specular);
//    pixel = Pixel(intersect_pt, direct_color);
    pixel = Pixel(intersect_pt, ambient);
    return true;
}

Color Plane::calc_ambient() {
    return Color(plane_color.scaled(ambient_coeff));
}

bool Plane::is_occluded(Ray shadow_ray, vector<Shape *> shapes, LightSource light) {
    return false;
}

bool Plane::is_occluding(Ray shadow_ray, LightSource light) {
    return false;
}

Color Plane::calc_diffuse(Point intersect_pt, vector<LightSource> lights, vector<Shape *> shapes) {
    return Color();
}

Color Plane::calc_specular(Point intersect_pt, vector<LightSource> lights, vector<Shape *> shapes) {
    return Color();
}














