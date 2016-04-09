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
    Point eye_pt = Point(-200,0,00);

    vector<Shape*> shapes;
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

    Scene(vector<LightSource> _lights, vector<Shape*> _shapes) : lights(_lights), shapes(_shapes) {
        cout << "here " << endl;
        for (int i = 0; i < shapes.size(); ++i) {
            shapes.at(i)->eye_pt.x = eye_pt.x;
            shapes.at(i)->eye_pt.y = eye_pt.y;
            shapes.at(i)->eye_pt.z = eye_pt.z;
            cout << "i = " << i << endl;

        }
    }

    Scene() { }

    bool intersect(Ray ray, Pixel &pixel);
};


#endif //RAYTRACING_SCENE_H
