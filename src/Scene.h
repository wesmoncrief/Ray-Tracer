//
// Created by Wesley Moncrief on 4/6/16.
//

#ifndef RAYTRACING_SCENE_H
#define RAYTRACING_SCENE_H


#include <vector>
#include "LightSource.h"
#include "Sphere.h"

using namespace std;

class Scene {
    vector<LightSource> lights; // should this be vector of pointers??
    vector<Sphere> spheres;
    Point eye_pt = Point(-200, 0, 00);
    double perspective_x;
    double perspective_y;
    vector<Shape *> shapes;
public:


    double getPerspective_x() const {
        return perspective_x;
    }

    void setPerspective_x(double perspective_x) {
        Scene::perspective_x = perspective_x;
    }

    double getPerspective_y() const {
        return perspective_y;
    }

    void setPerspective_y(double perspective_y) {
        Scene::perspective_y = perspective_y;
    }

    void setEye_pt(const Point &eye_pt) {
        Scene::eye_pt = eye_pt;
    }

    const vector<LightSource> &getLights() const {
        return lights;
    }

    const Point &getEye_pt() const {
        return eye_pt;
    }

    Scene(vector<LightSource> _lights, vector<Shape *> _shapes) : lights(_lights), shapes(_shapes) {
        for (int i = 0; i < shapes.size(); ++i) {
            shapes.at(i)->eye_pt.x = eye_pt.x;
            shapes.at(i)->eye_pt.y = eye_pt.y;
            shapes.at(i)->eye_pt.z = eye_pt.z;
        }
        perspective_x = 1;
        perspective_y = 1;
    }

    Scene() { }

    bool intersect(const Ray &ray, Pixel &pixel);
};


#endif //RAYTRACING_SCENE_H
