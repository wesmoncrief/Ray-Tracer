//
// Created by Wesley Moncrief on 4/6/16.
//

#include "Scene.h"

bool cmp_pts(Pixel p1, Pixel p2){
    return p1.point.z > p2.point.z;
}

bool Scene::intersect(Ray ray, Pixel &pixel) { //don't modify 'pixel' until the end, it's basically a return value

    vector<Pixel> closest_pixs;
    for (int i = 0; i < shapes.size(); ++i) {
        Pixel temp_pix = pixel;
        if (shapes.at(i)->intersect(ray, lights, shapes, temp_pix)){ //add all the intersections from
            //the different shapes to the closest_pix vector
            closest_pixs.push_back(temp_pix);
        }
        //else this sphere doesn't intersect with the ray
    }


    if (closest_pixs.size() == 0 ) return false; //no intersections with shapes

    Pixel closest_pix = *std::min_element(closest_pixs.begin(), closest_pixs.end(), cmp_pts);
    pixel = closest_pix;
    return true;

}




