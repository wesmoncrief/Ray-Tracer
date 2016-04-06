#include <iostream>
#include <GLUT/glut.h>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include "InfinitePlane.h"
#include "Sphere.h"
#include "Color.h"

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

#define ImageW 400
#define ImageH 400

float framebuffer[ImageH][ImageW][3];


// Draws the scene
void drawit(void)
{
   glDrawPixels(ImageW,ImageH,GL_RGB,GL_FLOAT,framebuffer);
   glFlush();
}

// Clears framebuffer to black
void clearFramebuffer()
{
	int i,j;

	for(i=0;i<ImageH;i++) {
		for (j=0;j<ImageW;j++) {
			framebuffer[i][j][0] = 0.0;
			framebuffer[i][j][1] = 0.0;
			framebuffer[i][j][2] = 0.0;
		}
	}
}


// Sets pixel x,y to the color RGB
void setFramebuffer(int x, int y, float R, float G, float B)
{
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

void setFramebuffer(int x, int y, Color color){
	setFramebuffer(x,y,color.r, color.g, color.b);
}


void display(void)
{
	//The next two lines of code are for demonstration only.
	//They show how to draw a line from (0,0) to (100,100)
	for(int i=0;i<=100;i++) setFramebuffer(i, 3*i, 1.0, 1.0, 1.0);
	drawit();


	//assume that X axis goes to the right, Y axis goes up, Z axis comes towards you.
	int eye_z = 40;
	int eye_y = 0;
	int eye_x = 0;

	Sphere s1(Point(0,0,0), 20, Color(.4, .7, .8));
	Sphere s2(Point(100,150, -200), 80, Color(.8, .2, .9));
	Sphere s3(Point(-110,-40, -1000), 120, Color(.8, .2, .9));
	//if I make a Scene class, that can hold the ambient light coefficient.
	for (int j = 0; j < ImageH; ++j){
		for (int i = 0; i < ImageW; ++i) {
			int y = j - 200 + eye_y;
			int x = i - 200 + eye_x;
			//todo: make it to where camera position is adjustable via V changing
			//if intersection, setframebuffer
			Ray r(Point(x,y,eye_z));
			Pixel p = Pixel();
			if (s1.intersect(r, p)){
				//before calling this we should make sure p is the closest!
				setFramebuffer(i, j, p.color.r, p.color.g, p.color.b);
			}
			if (s3.intersect(r,p)) setFramebuffer(i, j, p.color);
			if (s2.intersect(r, p)) setFramebuffer(i, j, p.color);

		}
	}

	drawit();
}

void init(void)
{
	clearFramebuffer();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(ImageW,ImageH);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Wesley Moncrief - A5, Option 2");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}