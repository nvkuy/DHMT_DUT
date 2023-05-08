#include "GL/glut.h"
#include <bits/stdc++.h>

using namespace std;

const double WIDTH = 600, HEIGHT = 600;

void demo102210240() {

    glClear(GL_COLOR_BUFFER_BIT);

    //toa do diem dung' (de` cho), mau xanh la cay
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(1, 4, 6);
    glRotatef(60, 0, 0, 1);
    glColor3f(0, 1, 0);
    glBegin(GL_POINTS);
    glVertex3f(21, 2, 40);
    glEnd();

    //toa do Uy tinh ra, mau xanh duong
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0, 0, 1);
    glBegin(GL_POINTS);
    glVertex3f(9.768, 23.187, 46);
    glEnd();

    //toa do Tri' tinh ra, mau do
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    glVertex3f(5.804, 22.052, 46);
    glEnd();

    glFlush ();

}

void display(void)

{
    demo102210240();
}

void init (void)

{

    glClearColor (0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(-50, 50, -50, 50, -50, 50);

}

int main(int argc, char** argv)

{

    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize (WIDTH, HEIGHT);

    glutInitWindowPosition (100, 100);

    glutCreateWindow ("demo");

    init ();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;

}
