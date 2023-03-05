#include "GL/glut.h"
#include <bits/stdc++.h>

using namespace std;

const double WIDTH = 600, HEIGHT = 600;

pair<double, double> p1, p2, p3;
double dist(pair<double, double> p1, pair<double, double> p2) {
    return sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}

bool validTri(pair<double, double> p1, pair<double, double> p2, pair<double, double> p3) {
    vector<double> edges;
    edges.push_back(dist(p1, p2));
    edges.push_back(dist(p1, p3));
    edges.push_back(dist(p2, p3));
    sort(edges.begin(), edges.end());
    if (edges[0] + edges[1] <= edges[2] + 1e-5)
        return false;
    return true;
}

double determinantOfMatrix(double mat[3][4])
{
    double ans;
    ans = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2])
        - mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0])
        + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
    return ans;
}

pair<double, double> findSolution(double coeff[3][4])
{
    double d[3][4] = {
        { coeff[0][0], coeff[0][1], coeff[0][2] },
        { coeff[1][0], coeff[1][1], coeff[1][2] },
        { coeff[2][0], coeff[2][1], coeff[2][2] },
    };

    double d1[3][4] = {
        { coeff[0][3], coeff[0][1], coeff[0][2] },
        { coeff[1][3], coeff[1][1], coeff[1][2] },
        { coeff[2][3], coeff[2][1], coeff[2][2] },
    };

    double d2[3][4] = {
        { coeff[0][0], coeff[0][3], coeff[0][2] },
        { coeff[1][0], coeff[1][3], coeff[1][2] },
        { coeff[2][0], coeff[2][3], coeff[2][2] },
    };

    double d3[3][4] = {
        { coeff[0][0], coeff[0][1], coeff[0][3] },
        { coeff[1][0], coeff[1][1], coeff[1][3] },
        { coeff[2][0], coeff[2][1], coeff[2][3] },
    };

    double D = determinantOfMatrix(d);
    double D1 = determinantOfMatrix(d1);
    double D2 = determinantOfMatrix(d2);
    double D3 = determinantOfMatrix(d3);

    return {D1 / D, D2 / D};
}

double compressX(double x) {
    double res = x / WIDTH;
    res *= 2.0;
    return res - 1.0;
}

double compressY(double y) {
    double res = y / HEIGHT;
    res *= 2.0;
    return res - 1.0;
}

void bai1()
{

    glClear(GL_COLOR_BUFFER_BIT);

    // ve nha
    glColor3f (0.933, 0.721, 0.545);

    glBegin(GL_POLYGON);

    glVertex3f (-0.5, -0.5, 0.0);

    glVertex3f (0.5, -0.5, 0.0);

    glVertex3f (0.5, 0.5, 0.0);

    glVertex3f (-0.5, 0.5, 0.0);

    glEnd();

    // ve mai
    glColor3f (0.729, 0.933, 0.545);

    glBegin(GL_POLYGON);

    glVertex3f (0.5, 0.5, 0.0);

    glVertex3f (0, 0.75, 0.0);

    glVertex3f (-0.5, 0.5, 0.0);

    glEnd();

    // ve cua
    glColor3f (0.619, 0.545, 0.933);

    glBegin(GL_POLYGON);

    glVertex3f (-0.25, -0.5, 0.0);

    glVertex3f (0.25, -0.5, 0.0);

    glVertex3f (0.25, 0.25, 0.0);

    glVertex3f (-0.25, 0.25, 0.0);

    glEnd();

    glFlush ();

}

void bai4()
{

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f (1, 1, 1);
    glBegin(GL_LINE_STRIP);

    int point = 1e4;
    double t_begin = -13, t_end = 13, denta = (t_end - t_begin) / point, t = t_begin;
    double f = 0;
    for (int i = 0; i < point; i++) {
        f = max(abs(cos(t) - cos(80 * t) * sin(t)), f);
        f = max(abs(2.0 * sin(t) - sin(80 * t)), f);
        t += denta;
    }
    t = t_begin;
    for (int i = 0; i < point; i++) {
        double x = (cos(t) - cos(80 * t) * sin(t)) / f;
        double y = (2.0 * sin(t) - sin(80 * t)) / f;
        t += denta;
        glVertex3f(x, y, 0);
    }

    glEnd();

    glFlush ();
}

void drawStar(double cx, double cy, double r, double c1, double c2, double c3) {

    glColor3f (c1, c2, c3);
    glBegin(GL_LINE_LOOP);

    vector<double> x(5), y(5);
    double grad = (double) ((72.0 * 3.1415) / 180.0);
    x[0] = cx;
    y[0] = cy + r;

    for (int i = 1; i < 5; i++) {
        x[i] = (double) (x[0] * cos(i * grad) - y[0] * sin(i * grad) + cy * sin(i * grad) + cx * (1 - cos(i * grad)));
        y[i] = (double) (x[0] * sin(i * grad) + y[0] * cos(i * grad) + cy * (1 - cos(i * grad)) - cx * sin(i * grad));
    }
    for (int i = 0; i < 5; i++) x[i] = compressX(x[i]), y[i] = compressY(y[i]);
    glVertex3f(x[0], y[0], 0);
    glVertex3f(x[2], y[2], 0);
    glVertex3f(x[4], y[4], 0);
    glVertex3f(x[1], y[1], 0);
    glVertex3f(x[3], y[3], 0);

    glEnd();

}

void bai5(double cx, double cy, double r) {

    glClear(GL_COLOR_BUFFER_BIT);

    drawStar(cx, cy, r, 1, 1, 1);

    glFlush ();

}

void drawCircle(double cx, double cy, double r, double c1, double c2, double c3) {

    glColor3f (c1, c2, c3);
    glBegin(GL_POLYGON);

    int point = 1000;
    for (int i = 0; i < point; i++) {
        double theta = 2.0 * 3.1415 * double(i) / double(point);
        double x = r * cos(theta);
        double y = r * sin(theta);
        glVertex3f(compressX(x + cx), compressY(y + cy), 0);
    }

    glEnd();
}

void bai6(double cx, double cy, double r) {

    glClear(GL_COLOR_BUFFER_BIT);

    vector<double> x(5), y(5);
    double grad = (double) ((72.0 * 3.1415) / 180.0);
    x[0] = cx;
    y[0] = cy + r * 3 / 5;

    for (int i = 1; i < 5; i++) {
        x[i] = (double) (x[0] * cos(i * grad) - y[0] * sin(i * grad) + cy * sin(i * grad) + cx * (1 - cos(i * grad)));
        y[i] = (double) (x[0] * sin(i * grad) + y[0] * cos(i * grad) + cy * (1 - cos(i * grad)) - cx * sin(i * grad));
    }
    for (int i = 0; i < 5; i++)
        drawCircle(x[i], y[i], r * 2 / 5, 0.4, 0.6, 0.8);
    drawCircle(cx, cy, r * 2 / 5, 0.3, 0.5, 0.7);

    glFlush ();

}

void bai7() {

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);

    glVertex3f (compressX(100), compressY(100), 0);
    glVertex3f (compressX(500), compressY(100), 0);
    glVertex3f (compressX(500), compressY(350), 0);
    glVertex3f (compressX(100), compressY(350), 0);

    glEnd();

    int num = 100;
    double r = 60, cur_r = r;
    for (int i = 0; i < num; i++) {
        drawStar(300, 225, cur_r, 1, 1, 0);
        cur_r -= (r / num);
    }

    glFlush ();

}

void input_tri(pair<double, double> &p1, pair<double, double> &p2, pair<double, double> &p3) {
    while (true) {
        cout << "Nhap toa do 3 diem tam giac, 0 <= x < " << WIDTH << " va 0 <= y < " << HEIGHT << endl;
        cout << "x1 = "; cin >> p1.first;
        cout << "y1 = "; cin >> p1.second;
        cout << "x2 = "; cin >> p2.first;
        cout << "y2 = "; cin >> p2.second;
        cout << "x3 = "; cin >> p3.first;
        cout << "y3 = "; cin >> p3.second;
        if (validTri(p1, p2, p3)) break;
        cout << "Toa do 3 diem khong hop le" << endl;
    }
}

void bai2(pair<double, double> &p1, pair<double, double> &p2, pair<double, double> &p3) {

    glClear(GL_COLOR_BUFFER_BIT);
    double le[3][4] = {
        {-2.0 * p1.first, -2.0 * p1.second, 1, -p1.first * p1.first - p1.second * p1.second},
        {-2.0 * p2.first, -2.0 * p2.second, 1, -p2.first * p2.first - p2.second * p2.second},
        {-2.0 * p3.first, -2.0 * p3.second, 1, -p3.first * p3.first - p3.second * p3.second}
    };
    pair<double, double> I = findSolution(le);
    double R = dist(I, p1);
    drawCircle(I.first, I.second, R, 1, 1, 1);

    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);

    glVertex3f (compressX(p1.first), compressY(p1.second), 0);
    glVertex3f (compressX(p2.first), compressY(p2.second), 0);
    glVertex3f (compressX(p3.first), compressY(p3.second), 0);

    glEnd();

    glFlush ();

}

void bai3(pair<double, double> &p1, pair<double, double> &p2, pair<double, double> &p3) {

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);

    glVertex3f (compressX(p1.first), compressY(p1.second), 0);
    glVertex3f (compressX(p2.first), compressY(p2.second), 0);
    glVertex3f (compressX(p3.first), compressY(p3.second), 0);

    glEnd();

    double e12 = dist(p1, p2), e13 = dist(p1, p3), e23 = dist(p2, p3);
    pair<double, double> I;
    I.first = (e12 * p3.first + e23 * p1.first + e13 * p2.first) / (e12 + e13 + e23);
    I.second = (e12 * p3.second + e23 * p1.second + e13 * p2.second) / (e12 + e13 + e23);
    double p = (e12 + e23 + e13) / 2;
    double R = sqrt((p - e12) * (p - e13) * (p - e23) / p);
    drawCircle(I.first, I.second, R, 1, 1, 1);

    glFlush ();

}

void display(void)

{
    //bai1();

    ////bai 2 3 can input rieng o ham main
    //bai2(p1, p2, p3);
    //bai3(p1, p2, p3);

    //bai4();
    //bai5(200, 200, 100);
    //bai6(200, 200, 100);
    //bai7();
}

void init (void)

{

    glClearColor (0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(-1, 1, -1, 1, -1, 1);

}

int main(int argc, char** argv)

{
    //input cho bai 2 va 3
    input_tri(p1, p2, p3);

    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize (WIDTH, HEIGHT);

    glutInitWindowPosition (100, 100);

    glutCreateWindow ("lab1");

    init ();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;

}
