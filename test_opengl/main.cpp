#include <stdlib.h>

//#include <GL/gl.h>

#include <GL/glut.h>

#include <iostream>

#include <assert.h>

#include <stdio.h>



const int WIN_SIZE = 500;



class Point;

class Vector;



/***********************

 * Basic Point and Vector Classes with some standard functions

 ************************/

class Point {

public:

  float x, y;

  Point(): x(0), y(0) { }

  Point(float _x, float _y) : x(_x), y(_y) { }

  static Point lerp(Point& p, Point& q, float t);

  static Point lerp(Point& p, Vector& q, float t);

};



class Vector {

public:

  float dx, dy;

  Vector() : dx(0), dy(0) { }

  Vector(Point& p, Point& q) {

    dx = q.x - p.x;

    dy = q.y - p.y;

  }



  // Returns the perp of the given Vector

  Vector perp() {

    Vector answer;

    answer.dx = -dy;

    answer.dy = dx;

    return answer;

  }

};



// Compute the Point that is a linear interpolation of p and q

Point Point::lerp(Point& p, Point& q, float t) {

  Point answer;

  answer.x = p.x + t*(q.x - p.x);

  answer.y = p.y + t*(q.y - p.y);

  return answer;

}



// Compute the Point that is a linear interpolation of p and v

Point Point::lerp(Point& p, Vector& v, float t) {

  Point answer;

  answer.x = p.x + t*v.dx;

  answer.y = p.y + t*v.dy;

  return answer;

}



//=====================================================



void centerWorld(double cx, double cy, double sx, double sy);

void drawRay(Point start, Point end, int ticks = 0);

void drawCoordinateFrame();

void drawHouse();

void drawScene();

void display();



// Set the world to be centered at given location With given size

void centerWorld(double cx, double cy, double sx, double sy) {

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();

  gluOrtho2D(cx - sx/2, cx + sx/2, cy - sy/2, cy + sy/2);

}



// Draw a ray from start to end Include arrow and tick marks

void drawRay(Point start, Point end, int ticks) {

  // First draw the line segment itself

  glBegin(GL_LINES);

  {

    glVertex2f(start.x, start.y);

    glVertex2f(end.x, end.y);

  }

  glEnd();

}



// Draw the x- and y- axes (use drawRay)

void drawCoordinateFrame() {

  Point origin(0, 0);

  Point xPoint(10, 0);

  Point yPoint(0, 10);

  drawRay(origin, xPoint, 10);

  drawRay(origin, yPoint, 10);

}



// Draw a simple house

void drawHouse() {

  glBegin(GL_POLYGON); {

    glVertex2f(0, 0);

    glVertex2f(1, 0);

    glVertex2f(1, 1);

    glVertex2f(0, 1);

  }

  glEnd();

  glBegin(GL_TRIANGLES); {

    glVertex2f(0, 1);

    glVertex2f(1, 1);

    glVertex2f(0.5, 1.5);

  }

  glEnd();

}



// Compute the Shear Matrix

//   OpenGL does not provide a Shear matrix (that I could find yet)

//   Plus it illustrates how to pass ANYWAY Matrix to OpenGL

//     Note: m goes down COLUMNS first...

//        m1, m2, m3, m4 represent m11, m21, m31, m41

//        m5, m6, m7, m8 represent m12, m22, m32, m42

//        etc...

void shearMatrix(int shearX, int shearY) {

  float m[] = {

    1, shearY, 0, 0,

      shearX, 1, 0, 0,

      0, 0, 1, 0,

      0, 0, 0, 1 };

  glMultMatrixf(m);

}



void printMatrix() {

  float m[16];

  glGetFloatv(GL_MODELVIEW_MATRIX, m);



  int row, col, index;

  for (row = 0; row < 4; row++) {

    for (col = 0, index = row; col < 4; col++, index+=4) {

      printf("%3.3f ", m[index]);

    }

    printf("\n");

  }

}



// Draw our complex scene!

void drawScene() {

  float intensity = 1.0;



  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();

  printf("After Identity\n");

  printMatrix();  printf("\n");



  glColor3f(intensity, intensity, intensity);

  glScaled(20, 20, 1.0);  // Sx=20, Sy=20, Sz=1

  printf("After Scaling\n");

  printMatrix();  printf("\n");

  drawCoordinateFrame(); drawHouse();



  glPushMatrix();



  intensity -= 0.1;

  glColor3f(intensity, intensity, intensity);

  glColor3f(.0, 1.0, 1.0);

  glTranslated(2, 0, 0);   // dx = 2, dy = 0, dz = 0 (over 2 units)

  printf("After Now Translating\n");

  printMatrix();  printf("\n");

  drawCoordinateFrame(); drawHouse();



  intensity -= 0.1;

  glColor3f(intensity, intensity, intensity);

  glTranslated(0, 2, 0.0);

  printf("After Now Translating Again...\n");

  printMatrix();  printf("\n");

  drawCoordinateFrame(); drawHouse();



  intensity -= 0.1;

  glColor3f(intensity, intensity, intensity);

  glRotated(30, 0, 0, 1);  // 30 degrees about origin (z-axis)

  glTranslated(0, 5, 0);

  glScaled(1.2, 0.5, 1);

  printf("After Rotate, Translate, Scale\n");

  printMatrix();  printf("\n");

  drawCoordinateFrame(); drawHouse();



  glPopMatrix();

  glPushMatrix();

  intensity -= 0.1;

  glColor3f(intensity, intensity, intensity);

  glRotated(-30, 0, 0, 1);  // 30 degrees about origin (z-axis)

  glTranslated(0, 5, 0);

  glScaled(1.2, 0.5, 1);

  drawCoordinateFrame(); drawHouse();



  glPopMatrix();



  intensity -= 0.1;

  glColor3f(intensity, intensity, intensity);

  shearMatrix(1, 0);

  drawCoordinateFrame(); drawHouse();

  printf("At the End\n");

  printMatrix();  printf("\n");



}



void display() {

  // Set the viewport to the full screen!

  glViewport(0, 0, WIN_SIZE, WIN_SIZE);



  // Clear the screen

  glClearColor(0.0, 0.0, 0.0, 0.0);

  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0,1.0,1.0);



  // Place origin in the center of our Frame

  centerWorld(0, 0, WIN_SIZE, WIN_SIZE);



  // And now draw the scene

  drawScene();



  glFlush();

  glutSwapBuffers();   // needed for double buffering!

}



void keyboard(unsigned char key, int x, int y)

{

  switch (key) {

  case 27:

  case 'Q':

  case 'q':

    exit(0);

    break;

  }



  // Redraw the screen on all keyboard events

  glutPostRedisplay();

}



int main(int argc, char** argv) {

  // Initialize the GLUT environment

  glutInit(&argc, argv);



  // Single-buffered, using RGB

  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

  glutInitWindowSize(WIN_SIZE,WIN_SIZE);

  glutInitWindowPosition(100,100);



  // Create window, returns a unique window identifier

  glutCreateWindow("Transformers: Graphics in Disguise!");



  // Set up the callback routines we will need/use

  glutDisplayFunc(display);

  glutKeyboardFunc (keyboard);



  // Start GLUT going in its infinite event listen cycle

  glutMainLoop();

  return 0;

}//main
