//
// Created by Wesley Moncrief on 4/6/16.
//

#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H


class Color {

public:
    Color() { }

    Color(float r, float g, float b) : r(r), g(g), b(b) { }

    float r, g, b;

    // Add this instance's value to other, and return a new instance
    // with the result.
    Color sum(Color _color) {
        float new_r, new_g, new_b;
        new_r = _color.r + r;
        new_g = _color.g + g;
        new_b = _color.b + b;
        if (new_r > 1) new_r = 1;
        if (new_g > 1) new_g = 1;
        if (new_b > 1) new_b = 1;
        Color c(new_r, new_g, new_b);
        return c;
    }
};


#endif //RAYTRACING_COLOR_H
