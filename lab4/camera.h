#include "GL/glut.h"

#include "math.h"

#include <iostream>



//  << Support Classes for Camera >>

//////////// Point3 class

class Point3{

public:

    float x,y,z;

    void set(float dx, float dy, float dz){x = dx; y = dy; z = dz;}

    void set(Point3& p){x = p.x; y = p.y; z = p.z;}

    Point3(float xx, float yy, float zz){x = xx; y = yy; z = zz;}

    Point3(){x = y = z = 0;}

    void build4tuple(float v[])

    {// load 4-tuple with this point: v[3] = 1 for homogeneous

            v[0] = x; v[1] = y; v[2] = z; v[3] = 1.0f;

    }

};



//////////// Vector3 class

class Vector3{

public:

    float x,y,z;

    void set(float dx, float dy, float dz){ x = dx; y = dy; z = dz;}

    void set(Vector3& v){ x = v.x; y = v.y; z = v.z;}

    void flip(){x = -x; y = -y; z = -z;} // reverse this vector

    void setDiff(Point3& a, Point3& b)//set to difference a - b

    { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;}

    void normalize()//adjust this vector to unit length

    {

        double sizeSq = x * x + y * y + z * z;

        if(sizeSq < 0.0000001)

        {

            std::cerr << "\nnormalize() sees vector (0,0,0)!";

            return; // does nothing to zero vectors;

        }

        float scaleFactor = 1.0/(float)sqrt(sizeSq);

        x *= scaleFactor; y *= scaleFactor; z *= scaleFactor;

    }

    Vector3(float xx, float yy, float zz){x = xx; y = yy; z = zz;}

    Vector3(Vector3& v){x = v.x; y = v.y; z = v.z;}

    Vector3(){x = y = z = 0;} //default constructor

    Vector3 cross(Vector3 b) //return this cross b

    {

       Vector3 c(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);

       return c;

    }

    float dot(Vector3 b) // return this dotted with b

   {return x * b.x + y * b.y + z * b.z;}

};



class Camera{

  private:

    Point3 eye;

    Vector3 u,v,n;

    double viewAngle, aspect, nearDist, farDist; // view volume shape

    void setModelViewMatrix(); // tell OpenGL where the Camera is



  public:

    Camera(){};

    //Camera(){u.set(1, 0, 0); v.set(0, 1, 0); n.set(0, 0, 1);};

    // default constructor

    void set(Point3 eye, Point3 look, Vector3 up); // like gluLookAt()

    void roll(float angle); // roll it

    void pitch(float angle); // increase pitch

    void yaw(float angle); // yaw it

    void slide(float delU, float delV, float delN); // slide it

    void setShape(float vAng, float asp, float nearD, float farD);

};



void Camera :: setModelViewMatrix(void)

{ // load modelview matrix with existing Camera values

    float m[16];

    Vector3 eVec(eye.x, eye.y, eye.z); // a vector version of eye

    m[0] =  u.x; m[4] =  u.y; m[8]  =  u.z;  m[12] = -eVec.dot(u);

    m[1] =  v.x; m[5] =  v.y; m[9]  =  v.z;  m[13] = -eVec.dot(v);

    m[2] =  n.x; m[6] =  n.y; m[10] =  n.z;  m[14] = -eVec.dot(n);

    m[3] =  0;   m[7] =  0;   m[11] =  0;    m[15] = 1.0;

    glMatrixMode(GL_MODELVIEW);

    glLoadMatrixf(m);  // load OpenGL's modelview matrix

}



void Camera :: set(Point3 Eye, Point3 look, Vector3 up)

{   // create a modelview matrix and send it to OpenGL

Vector3 t;

    eye.set(Eye); // store the given eye position

    n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z); // make n

    //t.set(up.y*n.z - up.z*n.y, up.z*n.x - up.x*n.z, up.x*n.y - up.y*n.x);

    u.set(up.y*n.z - up.z*n.y, up.z*n.x - up.x*n.z, up.x*n.y - up.y*n.x);

    //Vector3 t(up.cross(n));

    //u.set(t);                     // make u = up X n

    //u.set(up.cross(n));           // make u = up X n

    n.normalize(); u.normalize(); // make them unit length

    v.set(n.y*u.z - n.z*u.y, n.z*u.x - n.x*u.z, n.x*u.y - n.y*u.x);

    //t = up.cross(n);

    //v.set(t);                     // make v =  n X u

    //v.set(n.cross(u));            // make v =  n X u

    setModelViewMatrix();         // tell OpenGL

}



void Camera :: setShape(float vAng, float asp, float nearD, float farD)

{ // set shape of the view volume and set up the projection matrix

    viewAngle = vAng; aspect = asp; nearDist = nearD; farDist = farD;

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(viewAngle, aspect, nearDist, farDist);

}



void Camera :: slide(float delU, float delV, float delN)

{

    eye.x += delU * u.x + delV * v.x + delN * n.x;

    eye.y += delU * u.y + delV * v.y + delN * n.y;

    eye.z += delU * u.z + delV * v.z + delN * n.z;

    setModelViewMatrix();

}



void Camera :: roll(float angle)

{ // roll the camera through angle degrees

    float cs = cos( angle / 180 * 3.14159265 );

    float sn = sin( angle / 180 * 3.14159265 );

    Vector3 t = u;   // remember old u

    u.set(cs*t.x - sn*v.x, cs*t.y - sn*v.y, cs*t.z - sn*v.z );

    v.set(sn*t.x + cs*v.x, sn*t.y + cs*v.y, sn*t.z + cs*v.z );

    setModelViewMatrix();

}



void Camera :: pitch(float angle)

{ // pitch the camera through angle degrees

    float cs = cos( angle / 180 * 3.14159265 );

    float sn = sin( angle / 180 * 3.14159265 );

    Vector3 t = n;   // remember old n

    n.set(cs*t.x + sn*v.x, cs*t.y + sn*v.y, cs*t.z + sn*v.z );

    v.set(-sn*t.x + cs*v.x, -sn*t.y + cs*v.y, -sn*t.z + cs*v.z );

    setModelViewMatrix();

}



void Camera :: yaw(float angle)

{ // yaw the camera through angle degrees

    float cs = cos( angle / 180 * 3.14159265 );

    float sn = sin( angle / 180 * 3.14159265 );

    Vector3 t = u;   // remember old n

    u.set(cs*t.x + sn*n.x, cs*t.y + sn*n.y, cs*t.z + sn*n.z );

    n.set(-sn*t.x + cs*n.x, -sn*t.y + cs*n.y, -sn*t.z + cs*n.z );

    setModelViewMatrix();

}
