//
// Created by Wesley Moncrief on 4/6/16.
//

#include <cmath>
#include <vector>
#include "Sphere.h"
#include "LightSource.h"

bool is_occluded(Ray r, vector<Sphere> spheres, LightSource light);

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

    //we want the smallest positive value of r.
    if (r1 < 0 && r2 < 0) return false;
    if (r1 > 0 && r2 < 0) {
        t = r1;
    }
    if (r2 > 0 && r1 < 0) {
        t = r2;
    }
    if (r1 > 0 && r2 > 0) {
        if (r1 > r2) {
            t = r2;
        }
        else {
            t = r1;
        }

    }

    return true;
}

bool Sphere::get_intersect_pt(Ray ray, Point &pt) {
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
    if (!quadratic(1.0, b, c, t)) //there is no intersection
        return false;
    //P = P_o + tV
    Point intersect_pt(ray.start.x + t * ray.V.x, ray.start.y + t * ray.V.y, ray.start.z + t * ray.V.z);
    pt.x = intersect_pt.x;
    pt.y = intersect_pt.y;
    pt.z = intersect_pt.z;
    return true;
}

bool Sphere::intersect(Ray ray, vector<LightSource> lights, vector<Sphere> spheres, Pixel &pixel) {

    Point intersect_pt;
    if (!get_intersect_pt(ray, intersect_pt)) return false; //else the intersect_pt is updated

    //color is Direct (ambient + diffuse + specular) + reflected + //refracted...
    //if i add attenuation to plane, should I add it here?
    Color ambient = calc_ambient();
    Color diffuse = calc_diffuse(intersect_pt, lights, spheres);
    Color direct_color = ambient.sum(diffuse);
    Color specular = calc_specular(intersect_pt, lights, spheres);
    direct_color = direct_color.sum(specular);
    pixel = Pixel(intersect_pt, direct_color);
    return true;
}

Color Sphere::calc_diffuse(Point intersect_pt, vector<LightSource> lights, vector<Sphere> spheres) {

    Color total_diffuse = Color(0, 0, 0);

    //run this for each light source. Light sources are additive in their effects.
    for (int i = 0; i < lights.size(); ++i) {
        LightSource ls = lights.at(i);
        //vec3 , from intersect pt to lightsource.pt
        Vec3 occlu_vec(ls.light_center.x - intersect_pt.x, ls.light_center.y - intersect_pt.y,
                       ls.light_center.z - intersect_pt.z);

        if (!is_occluded(Ray(intersect_pt, occlu_vec), spheres, ls)) {
            //I = intensity of point light * diffuse reflection coefficient * (light vector dotted with normal vector)

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
            total_diffuse = total_diffuse.sum(ls.light_color.scaled(coeff));
        }

    }


    return total_diffuse;
}

Color Sphere::calc_specular(Point intersect_pt, vector<LightSource> lights, vector<Sphere> spheres) {
    //i'm assuming all the vectors described are normalized
    //I = C * spec_refl_coeff * (R dot E) ^spec_n_value

    Vec3 E(eye_pt.x - intersect_pt.x, eye_pt.y - intersect_pt.y, eye_pt.z - intersect_pt.z);
    E.normalize();

    Color total_specular = Color(0, 0, 0);

    for (int i = 0; i < lights.size(); ++i) { //lights from different sources are additive
        LightSource ls = lights.at(i);

        Vec3 occlu_vec(ls.light_center.x - intersect_pt.x, ls.light_center.y - intersect_pt.y,
                       ls.light_center.z - intersect_pt.z);

        if (!is_occluded(Ray(intersect_pt, occlu_vec), spheres, ls)) {
            Vec3 L = Vec3(ls.light_center.x - intersect_pt.x, ls.light_center.y - intersect_pt.y,
                          ls.light_center.z - intersect_pt.z);
            L.normalize();

            Vec3 N = Vec3(intersect_pt.x - center.x, intersect_pt.y - center.y, intersect_pt.z - center.z);
            N.normalize();

            double n_coef = 2 * L.dotProduct(N);
            Vec3 R(n_coef * N.x - L.x, n_coef * N.y - L.y, n_coef * N.z - L.z);
            R.normalize();

            double RdotE = R.dotProduct(E);
            double powerRdotE = pow(RdotE, specular_n_value);
            double full_coeff = specular_refl_coeff * powerRdotE;
            if (full_coeff < 0) full_coeff = 0;

            total_specular = total_specular.sum(ls.light_color.scaled(full_coeff));
        }

    }

    return total_specular;
}

Color Sphere::calc_ambient() {
    return Color(sphere_color.scaled(ambient_coeff));
}

bool Sphere::is_occluded(Ray ray, vector<Sphere> spheres, LightSource light) {

    ray.normalize();
    double distance = light.light_center.distance(ray.start);  //distance between lightsource and ray

    for (int i = 0; i < spheres.size(); ++i) {
        Sphere occluding_sphere = spheres.at(i);
        if (!this->equals(occluding_sphere)){ //fixes problem where sphere 'occludes' itself
            //following code from intersect
            Vec3 p_naught_minus_o(ray.start.x - occluding_sphere.center.x, ray.start.y - occluding_sphere.center.y,
                                  ray.start.z - occluding_sphere.center.z);
            double b = 2 * (ray.V.dotProduct(p_naught_minus_o));
            //http://www.vis.uky.edu/~ryang/teaching/cs535-2012spr/Lectures/13-RayTracing-II.pdf
            //somehow my implementation of the wikipedia way was wrong but this, from above link, worked like a charm.
            double c =
                    ray.start.x * ray.start.x - 2 * ray.start.x * occluding_sphere.center.x +
                    occluding_sphere.center.x * occluding_sphere.center.x + ray.start.y * ray.start.y -
                    2 * ray.start.y * occluding_sphere.center.y + occluding_sphere.center.y * occluding_sphere.center.y +
                    ray.start.z * ray.start.z - 2 * ray.start.z * occluding_sphere.center.z +
                    occluding_sphere.center.z * occluding_sphere.center.z -
                    occluding_sphere.radius * occluding_sphere.radius;
            //check to make sure unit vector
            double t = 0;
            if (quadratic(1.0, b, c, t)) { //there is an intersection
                if (t < distance)
                    return true;

            }
        }
        else {
            int j = 4;
            j ++;
            j++;
        }

    }
    return false;


}

bool Sphere::equals(Sphere sph) {
    return sph.radius == radius && sph.center.x == center.x && sph.center.y == center.y && sph.center.z == center.z;
}

