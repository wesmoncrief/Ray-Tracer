//
// Created by Wesley Moncrief on 4/6/16.
//

#include "Scene.h"

bool cmp_pts(Pixel p1, Pixel p2){
    return p1.point.z > p2.point.z;
}

bool Scene::intersect(Ray ray, Pixel &pixel) { //don't modify 'pixel' until the end, it's basically a return value

    vector<Pixel> closest_pixs;
    for (int sph = 0; sph < spheres.size(); ++sph) {
        Pixel temp_pix = pixel;
        if (spheres.at(sph).intersect(ray, lights, spheres, temp_pix)){
            closest_pixs.push_back(temp_pix);
        }
        //else this sphere doesn't intersect with the ray
    }

    //todo add intersections for planes here

    if (closest_pixs.size() == 0 ) return false; //no intersections with shapes

    Pixel closest_pix = *std::min_element(closest_pixs.begin(), closest_pixs.end(), cmp_pts);
    pixel = closest_pix;
    return true;


}

bool Scene::is_occluded(Pixel pix, LightSource ls) {


    return false;
}



