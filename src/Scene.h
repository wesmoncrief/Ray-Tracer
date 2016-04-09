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
    Point eye_pt = Point(-200,0,00);
public:


    void setEye_pt(const Point &eye_pt) {
        Scene::eye_pt = eye_pt;
    }

    const vector<LightSource> &getLights() const {
        return lights;
    }

    const Point &getEye_pt() const {
        return eye_pt;
    }

    Scene(const vector<LightSource> _lights, const vector<Sphere> _spheres) : lights(_lights), spheres(_spheres) {
        for (int i = 0; i < spheres.size(); ++i) {
            spheres.at(i).eye_pt.x = eye_pt.x;
            spheres.at(i).eye_pt.y = eye_pt.y;
            spheres.at(i).eye_pt.z = eye_pt.z;

        }
        //todo add eye_pt data for rectangle
    }

    Scene() { }

    bool intersect(Ray ray, Pixel &pixel);
    bool is_occluded(Pixel pix, LightSource ls);
};


#endif //RAYTRACING_SCENE_H
