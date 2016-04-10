#include <iostream>
#include <GLUT/glut.h>
#include "Sphere.h"
#include "Scene.h"
#include "Plane.h"

/******************************************************************
	Notes:
	This is the same utility as in the earlier homework assignment.
	Image size is 400 by 400 by default.  You may adjust this if
		you want to.
	You can assume the window will NOT be resized.
	Call clearFramebuffer to clear the entire framebuffer.
	Call setFramebuffer to set a pixel.  This should be the only
		routine you use to set the color (other than clearing the
		entire framebuffer).  drawit() will cause the current
		framebuffer to be displayed.
	As is, your ray tracer should probably be called from
		within the display function.  There is a very short sample
		of code there now.  You can replace that with a call to a
		function that raytraces your scene (or whatever other
		interaction you provide.
	You may add code to any of the subroutines here,  You probably
		want to leave the drawit, clearFramebuffer, and
		setFramebuffer commands alone, though.
  *****************************************************************/

#define ImageW 600
#define ImageH 600

float framebuffer[ImageH][ImageW][3];


// Draws the scene
void drawit(void) {
    glDrawPixels(ImageW, ImageH, GL_RGB, GL_FLOAT, framebuffer);
    glFlush();
}

// Clears framebuffer to black
void clearFramebuffer() {
    int i, j;

    for (i = 0; i < ImageH; i++) {
        for (j = 0; j < ImageW; j++) {
            framebuffer[i][j][0] = 0.0;
            framebuffer[i][j][1] = 0.0;
            framebuffer[i][j][2] = 0.0;
        }
    }
}


// Sets pixel x,y to the color RGB
void setFramebuffer(int x, int y, float R, float G, float B) {
    //it looked like the x and y were reversed...
    if (R <= 1.0) if (R >= 0.0)
        framebuffer[y][x][0] = R;
    else
        framebuffer[y][x][0] = 0.0;
    else
        framebuffer[y][x][0] = 1.0;
    if (G <= 1.0) if (G >= 0.0)
        framebuffer[y][x][1] = G;
    else
        framebuffer[y][x][1] = 0.0;
    else
        framebuffer[y][x][1] = 1.0;
    if (B <= 1.0) if (B >= 0.0)
        framebuffer[y][x][2] = B;
    else
        framebuffer[y][x][2] = 0.0;
    else
        framebuffer[y][x][2] = 1.0;
}

void setFramebuffer(int x, int y, Color color) {
    setFramebuffer(x, y, color.r, color.g, color.b);
}


void display(void) {
    //The next two lines of code are for demonstration only.
    //They show how to draw a line from (0,0) to (100,100)
    for (int i = 0; i <= 100; i++) setFramebuffer(i, 3 * i, 1.0, 1.0, 1.0);
    drawit();

    //assume that X axis goes to the right, Y axis goes up, Z axis comes towards you.

    vector<Shape *> shapes;
//    shapes.push_back(new Sphere(Point(80, 0, 0), 50, Color(.1, .7, .2)));
//    shapes.push_back(new Sphere(Point(50, -90, -200), 50, Color(.2,.2,.2)));
//    shapes.push_back(new Sphere(Point(-50, -100, -180), 50, Color(.6, .0, .0)));
//    shapes.push_back(new Plane(Point(0,0,0), Vec3(-.5,0,1), Color(1,0,0)));
    shapes.push_back(new Plane(Point(0,-200,0), Vec3(0,1,.1), Color(0,0,1)));
    shapes.push_back(new Plane(Point(80,0,-600), Vec3(-1,0,.15), Color(1,1,0)));

    shapes.push_back(new Sphere(Point(-100, 0, 20), 50, Color(.4, .7, .8)));
    shapes.push_back(new Sphere(Point(100, 0, -200), 100, Color(1, 1, 0)));
    shapes.push_back(new Sphere(Point(100, -50, 30), 20, Color(.8, .2, .3)));
    shapes.push_back(new Sphere(Point(0, 200, 0), 70, Color(.8, .2, .9)));

    vector<LightSource> lights;

//    lights.push_back(LightSource(Point(00, 2000, 300), Color(1, 1, 1)));
//    lights.push_back(LightSource(Point(300,900,-1000), Color(1,0,0)));
//    lights.push_back(LightSource(Point(-400, 500, 200), Color(0,0,1)));
//
//    lights.push_back(LightSource(Point(0, 900, 00), Color(1, 1, 1)));
//    lights.push_back(LightSource(Point(-900, 100, 00), Color(0, 1, 1)));
//    lights.push_back(LightSource(Point(0, 0, 900), Color(1, 0,0)));
//
//    shapes.push_back(new Sphere(Point(-100, 0, 20), 50, Color(.4, .7, .8)));
//    shapes.push_back(new Sphere(Point(100, 0, 0), 100, Color(1, 1, 0)));
    shapes.push_back(new Sphere(Point(100, -50, 30), 20, Color(.8, .2, .3)));
    shapes.push_back(new Sphere(Point(0, 200, 0), 70, Color(.8, .2, .9)));

//    lights.push_back(LightSource(Point(0, 900, 00), Color(1, 1, 1)));
//    lights.push_back(LightSource(Point(-900, 100, 00), Color(0, 1, .5)));
    lights.push_back(LightSource(Point(0, 0, 900), Color(1, 0, 0)));

    Scene scene(lights, shapes);
    //if I make a Scene class, that can hold the ambient light coefficient.

    scene.setEye_pt(Point(0, 0, 150));

    for (int j = 0; j < ImageH; ++j) {
        for (int i = 0; i < ImageW; ++i) {

            //works for classic view
            double y = (j - ImageH /2 + scene.getEye_pt().y);
            double x = (i - ImageW /2 + scene.getEye_pt().x);
            double z = scene.getEye_pt().z;
            //make it to where camera position is adjustable via V changing
//            http://stackoverflow.com/questions/13078243/ray-tracing-camera

            Vec3 direction(.2 * x, .2 * y, -z); //these coefficients create a perspective projection.
            //to make it orthogonal, use Vec3 direction(0,0,-1);
            //this may cause perspective warp if coefficients are too large. This is expected.
            direction.normalize();

            Ray r(Point(x, y, z), direction);
            Pixel p = Pixel(Point(0, 0, 0), Color(0, 0, 0));
            if (scene.intersect(r, p))
                setFramebuffer(i, j, p.color);
        }
    }

    drawit();
}

void init(void) {
    clearFramebuffer();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ImageW, ImageH);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Wesley Moncrief - A5, Option 2");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


//works for classic view
//int y = (int) (j - 200 + scene.getEye_pt().y);
//int x = (int) (i - 200 + scene.getEye_pt().x);
//int z = (int) scene.getEye_pt().z;
////make it to where camera position is adjustable via V changing
//
//Vec3 direction(0, 0, -1);