/*  flyCamera.cpp

 *  This program demonstrates the application of "flying"  a camera around a teapot.

 */



#include <fstream>

#include <cmath>

#include <gl/glut.h>

#include <stdlib.h>

#include <stdio.h>

#include "Camera.h"



Camera cam; // global camera object



void myKeyboard(unsigned char key, int x, int y)

{   //use 'F', 'ctrl-F', 'P' and 'ctrl-P' to control the camera

  switch(key)

  {

    // controls for camera

    case 'F': cam.slide(0, 0, 0.2);

              break; // slide camera forward

    case 'F'-64: cam.slide(0,0,-0.2);

                 break; //slide camera back

    // add up/down control

    case 'P': cam.pitch(-1.0);

              break;

    case 'P' - 64: cam.pitch( 1.0);

                   break;

    // add roll control

    case 'A': cam.roll(-1.0);

              break;

    case 'A' - 64: cam.roll( 1.0);

                   break;

    // add left/right control

    case 'M': cam.yaw(-1.0);

              break;

    case 'M' - 64: cam.yaw( 1.0);

                   break;

  }

  glutPostRedisplay(); // draw it again

}

//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>>>>>>>>>>

void myDisplay(void)

{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutWireTeapot(1.0); // draw the teapot

    glFlush();

    glutSwapBuffers(); // display the screen just made

}



void myMouse(int button, int state, int x, int y)

{

  switch (button) {

     case GLUT_RIGHT_BUTTON:

        if (state == GLUT_DOWN)

           exit (-1);

        break;

     default:

        break;

  }

}





//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int main(int argc, char **argv)

{

    Point3 eye, look;

    Vector3 up;

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // double buffering

    glutInitWindowSize(640,480);

    glutInitWindowPosition(50, 50);

    glutCreateWindow("Fly a camera around a teapot");

    //

    glClearColor(1.0f,1.0f,1.0f,1.0f);           // background is white

    glColor3f(0.0f,0.0f,0.0f);                   // set color of stuff

    glViewport(0, 0, 640, 480);

    eye.set(4, 4, 4);

    //eye.set(4, 0, 4);

    look.set(0, 0, 0);

    up.set(0, 1, 0);

    cam.set(eye, look, up);                      // make the initial camera

    cam.setShape(30.0f, 64.0f/48.0f, 0.5f, 50.0f);

    //

    glutKeyboardFunc(myKeyboard);

    glutMouseFunc(myMouse);                      // register myMouse function

    glutDisplayFunc(myDisplay);

    glutMainLoop();

}//main
