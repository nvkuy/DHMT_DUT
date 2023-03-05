#include <GL/glut.h>
#include <GL/gl.h>
#include <bits/stdc++.h>

using namespace std;

const double maxX = 50, maxY = 50, maxZ = 50;
vector<char> history;

struct point
{
    double x, y, z;
    point(double ix = 0, double iy = 0, double iz = 0)
    {
        x = ix, y = iy, z = iz;
    }
};

struct line
{
    point p1, p2;
};

line pq, mn;

void initValue()
{
    pq.p1 = point(1, 2);
    pq.p2 = point(7, 14);
    double x, y;
    cout << "Nhap toa do diem M, 0 <= max(|x|, |y|) <= 50:" << endl;
    cout << "x = ";
    cin >> x;
    cout << "y = ";
    cin >> y;
    mn.p1 = point(x, y);
    cout << "Nhap toa do diem N, 0 <= max(|x|, |y|) <= 50:" << endl;
    cout << "x = ";
    cin >> x;
    cout << "y = ";
    cin >> y;
    mn.p2 = point(x, y);
}

void init(void)

{

    glClearColor (0.0, 0.0, 0.0, 0.0);

    glShadeModel (GL_FLAT);

}

void updateMat() {
    reverse(history.begin(), history.end());
    for (char key : history) {
        switch (key) {
            case 't':
                glTranslatef(5, 0, 0);
                break;
            case 'T':
                glTranslatef(-5, 0, 0);
                break;
            case 'r':
                glRotatef(30, 0, 1, 0);
                break;
            case 'R':
                glRotatef(-30, 0, 1, 0);
                break;
            case 'p':
                glRotatef(180, 1, 0, 0);
                break;
            case 'P':
                glRotatef(-180, 1, 0, 0);
                break;
            case 'f':
                glTranslated(mn.p2.x, mn.p2.y, mn.p2.z);
                glRotatef(180, mn.p1.x - mn.p2.x, mn.p1.y - mn.p2.y, mn.p1.z - mn.p2.z);
                glTranslated(-mn.p2.x, -mn.p2.y, -mn.p2.z);
                break;
            case 'F':
                glTranslated(mn.p2.x, mn.p2.y, mn.p2.z);
                glRotatef(-180, mn.p1.x - mn.p2.x, mn.p1.y - mn.p2.y, mn.p1.z - mn.p2.z);
                glTranslated(-mn.p2.x, -mn.p2.y, -mn.p2.z);
                break;
            case 'h':
                glTranslated(mn.p2.x, mn.p2.y, mn.p2.z);
                glRotatef(30, mn.p1.x - mn.p2.x, mn.p1.y - mn.p2.y, mn.p1.z - mn.p2.z);
                glTranslated(-mn.p2.x, -mn.p2.y, -mn.p2.z);
                break;
            case 'H':
                glTranslated(mn.p2.x, mn.p2.y, mn.p2.z);
                glRotatef(-30, mn.p1.x - mn.p2.x, mn.p1.y - mn.p2.y, mn.p1.z - mn.p2.z);
                glTranslated(-mn.p2.x, -mn.p2.y, -mn.p2.z);
                break;
            default:
                break;
        }
    }
    reverse(history.begin(), history.end());
}

void display(void)

{

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    glColor3f(0, 1, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(mn.p1.x, mn.p1.y, mn.p1.z);
    glVertex3f(mn.p2.x, mn.p2.y, mn.p2.z);
    glEnd();

    updateMat();

    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(pq.p1.x, pq.p1.y, pq.p1.z);
    glVertex3f(pq.p2.x, pq.p2.y, pq.p2.z);
    glEnd();

    glPopMatrix();

    glutSwapBuffers();

}


void reshape(int w, int h)

{

    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(-maxX, maxX, -maxY, maxY, -maxZ, maxZ);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

}


void keyboard(unsigned char key, int x, int y)

{

    char tmp = toupper(key);
    if (tmp == 'T' || tmp == 'R' || tmp == 'P' || tmp == 'F' || tmp == 'H') {
        history.push_back(key);
        glutPostRedisplay();
    }

}

int main(int argc, char** argv)

{

    initValue();

    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize (500, 500);

    glutInitWindowPosition (100, 100);

    glutCreateWindow ("lab 2");

    init ();

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;

}
