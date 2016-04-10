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

#define ImageW 800
#define ImageH 800

float framebuffer[ImageH][ImageW][3];
int image_num; //used to cycle between images!
int num_of_images;


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

    //assume that X axis goes to the right, Y axis goes up, Z axis comes towards you.
    vector<Shape *> shapes;
    vector<LightSource> lights;

    Scene scene;
    if (image_num == 0){
        shapes.push_back(new Plane(Point(0, -200, 0), Vec3(0, 1, .05), Color(0, 1, 0), 0));
        shapes.push_back(new Plane(Point(300, 0, -600), Vec3(-1, 0, .01), Color(1, .1, 0), 0, .45, .5, .3, 30));

        shapes.push_back(new Sphere(Point(-150, -115, -200), 80, Color(.5, .5, 1), 0, .4, .7, .2, 5));
        shapes.push_back(new Sphere(Point(0, -135, -350), 50, Color(.4, .7, .8), 0));
        shapes.push_back(new Sphere(Point(0, 50, -750), 200, Color(.82, .68, .21), .4, .6, .3, .5, 3));
        shapes.push_back(new Sphere(Point(-300, 200, -450), 60, Color(0, .4, 0), 0, .6, .8, .4, 40));

        lights.push_back(LightSource(Point(-900, 400, 100), Color(1, 1, 1)));
        lights.push_back(LightSource(Point(-100, 400, -2000), Color(1, 1, .1)));
        lights.push_back(LightSource(Point(100, -200, 1000), Color(0, 0, .5)));

        scene = Scene(lights, shapes);
        scene.setEye_pt(Point(0, 0, 1300));
    }
    if (image_num == 1){
        shapes.push_back(new Sphere(Point(-100, 0, 20), 50, Color(.4, .7, .8)));
        shapes.push_back(new Sphere(Point(100, 0, 0), 100, Color(1, 1, 0)));
        shapes.push_back(new Sphere(Point(100, -50, 30), 20, Color(.8, .2, .3)));
        shapes.push_back(new Sphere(Point(0, 200, 0), 70, Color(.8, .2, .9)));

        lights.push_back(LightSource(Point(0, 900, 00), Color(0, 1, 0)));
        lights.push_back(LightSource(Point(-900, 100, 200), Color(0, 0, 1)));

        scene = Scene(lights, shapes);
        scene.setEye_pt(Point(0, 0, 1300));
    }
    if (image_num == 2){
        shapes.push_back(new Sphere(Point(0, 0, 0), 250, Color(.3, .8, .3)));

        lights.push_back(LightSource(Point(0, 900, 400), Color(0, 1, 0)));
        lights.push_back(LightSource(Point(-900, 0, 400), Color(0, 0, 1)));
        lights.push_back(LightSource(Point(900, 0, 400), Color(1, 0,0)));
        lights.push_back(LightSource(Point(0, -900, 400), Color(1, 0,1)));
        lights.push_back(LightSource(Point(0, 200, 800), Color(1, 0,1)));

        scene = Scene(lights, shapes);
        scene.setEye_pt(Point(0, 0, 1600));
    }
    if (image_num == 3){
        shapes.push_back(new Plane(Point(0, -50, 0), Vec3(.7, 1, 0), Color(.2, .8, .7), 0));
        shapes.push_back(new Plane(Point(0, -50, 0), Vec3(-.7,1,0), Color(.5, .5, .5), .7));

        shapes.push_back(new Sphere(Point(0, 35, 0), 80, Color(1, .1, 0), 0, .4, .7, .2, 45));
        shapes.push_back(new Sphere(Point(0, 5, 180), 50, Color(.2, .1, .8), 0, .4, .7, .8, 5));
        shapes.push_back(new Sphere(Point(50, 115, 350), 40, Color(0,1,.1), .4, .4, .7, .2, 5));
//        shapes.push_back(new Sphere(Point(0, -135, -350), 50, Color(.4, .7, .8), 0));
//        shapes.push_back(new Sphere(Point(0, 50, -750), 200, Color(.82, .68, .21), .4, .6, .3, .5, 3));
//        shapes.push_back(new Sphere(Point(-300, 200, -450), 60, Color(0, .4, 0), 0, .6, .8, .4, 40));
//
//        lights.push_back(LightSource(Point(-900, 400, 100), Color(1, 1, 1)));
        lights.push_back(LightSource(Point(200, 400, 1500), Color(1, 1, 1)));

//        lights.push_back(LightSource(Point(100, -200, 1000), Color(0, 0, .5)));

        scene = Scene(lights, shapes);
        scene.setEye_pt(Point(0, 0, 1300));
    }


    //if I make a Scene class, that can hold the ambient light coefficient.



    for (int j = 0; j < ImageH; ++j) {
        for (int i = 0; i < ImageW; ++i) {

            //works for classic view
            double y = (j - ImageH / 2 + scene.getEye_pt().y);
            double x = (i - ImageW / 2 + scene.getEye_pt().x);
            double z = scene.getEye_pt().z;
            //make it to where camera position is adjustable via V changing
//            http://stackoverflow.com/questions/13078243/ray-tracing-camera

            Vec3 direction(scene.getPerspective_x() * x, scene.getPerspective_y() * y, -z); //these coefficients create a perspective projection.
            //to make it orthogonal, use Vec3 direction(0,0,-1);
            //this may cause perspective warp if coefficients are too large. This is expected.
            direction.normalize();

//            Ray r(Point(x, y, z), direction);
            Ray r(scene.getEye_pt(), direction);
            Pixel p = Pixel(Point(0, 0, 0), Color(0, 0, 0));
            if (scene.intersect(r, p))
                setFramebuffer(i, j, p.color);
            else setFramebuffer(i, j, 0, 0, 0);
        }
    }

    drawit();
}

void keyboard(unsigned char key, int x, int y) {
    image_num = (image_num+1) % num_of_images;
    glutPostRedisplay();
}

void init(void) {
    clearFramebuffer();
    image_num = 0;
    num_of_images = 4;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ImageW, ImageH);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Wesley Moncrief - A5, Option 2");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
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