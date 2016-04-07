//
// Created by Wesley Moncrief on 4/6/16.
//

#ifndef RAYTRACING_SCENE_H
#define RAYTRACING_SCENE_H


#include <vector>
#include "LightSource.h"
#include "Sphere.h"

class Scene {
    vector<LightSource> lights; // should this be vector of pointers??
    vector<Sphere> spheres;

public:
    Scene(const vector<LightSource> lights, const vector<Sphere> spheres) : lights(lights), spheres(spheres) { }

    Scene() { }

    bool intersect(Ray ray, Pixel &pixel);
};


#endif //RAYTRACING_SCENE_H
