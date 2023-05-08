#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
using namespace std;

typedef float Matrix44 [4][4];
typedef float Matrix41 [4][1];
typedef float Matrix14 [1][4];
Matrix44 Matrix;
Matrix41 Matrixkq;
float point [4] ={0,0,0,0};

void inputpoint(float x,float y,float z){
	point[0]=x;
	point[1]=y;
	point[2]=z;
	point[3]=1;
}
//khoi tao ma tran don vi
void matrixSetIdentity(Matrix44 m){
	int i,j;
	for (i=0;i<4;i++){
		for(j=0;j<4;j++){
			m[i][j]=(i==j);
		}
	}
}
//Phep nhan 2 ma tran 4*4 a,b
void matrixMul(Matrix44 a, Matrix44 b)
{
    int i, j;
    Matrix44 tmp;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            tmp[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j] + a[i][3] * b[3][j];
        }
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            Matrix[i][j] = tmp[i][j];
        }
    }
}
//Phep nhan 2 ma tran xac dinh diem (44*41)
void matrixMul(Matrix44 a)
{
    int i, j;
    Matrix41 tmp;
    for (i = 0; i < 4; i++)
    {

            tmp[i][0] = a[i][0] * point[0] + a[i][1] * point[1]+ a[i][2] * point[2] + a[i][3] * point[3];

    }
    for (i = 0; i < 4; i++)
    {

            Matrixkq[i][0] = tmp[i][0];

    }
}
//In ma tran bieu dien
void printMatrix(Matrix44 b){
	for(int i=0;i<4;i++){
		cout<<endl<<setw(5)<<"|"<<setw(10);
		for(int j=0;j<4;j++){
			cout<<setw(10);
			cout<<setprecision(4)<<b[i][j];
			if(j==3) cout<<setw(3)<<"|";
		}
	}
	cout<<endl<<endl;
}
//In toa do cua diem
void printpoint(Matrix41 a){
	cout<<"Toa do diem duoc dich chuyen toi : ";
	cout<<"(";
	for(int i=0;i<3;i++){
		cout<<setprecision(4)<<a[i][0];
		if(i<2) cout<<";";
	}
	cout<<")";
	cout<<endl<<endl;
}
//Bien doi tinh tien
void Translate(float x,float y, float z)
{
	Matrix44 m;
	matrixSetIdentity(m);

	m[0][3]=x;
	m[1][3]=y;
	m[2][3]=z;
	matrixMul(m,Matrix);
	cout<<"Ma tran tinh tien: "<<endl;
	printMatrix(Matrix);
}

float mulvecnon(float *a,float *b){
	return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}
void camerachange(float* eye,float *look, float *up,float *right){
	Matrix44 m={{right[0],up[0],look[0],0},{right[1],up[1],look[1],0},
	{right[2],up[2],look[2],0},{-mulvecnon(eye,right),-mulvecnon(eye,up),-mulvecnon(eye,look),1}};
	matrixMul(m,Matrix);
	cout<<"Ma tran bien doi: "<<endl;
	printMatrix(Matrix);
}

void matrixMul1(Matrix44 a){
	int i,j;
	Matrix14 tmp;
	for(int i=0;i<4;i++){
		tmp[i]=0;
		for(int j=0;j<4;j++){
			tmp[i]+=point[j]*a[j][i];
		}
	}
	for(int i=0;i<4;i++)
	{
		MatrixKQ[i]=tmp[i];
	}
}

void display2(){
	matrixSetIdentity(Matrix);
	float eye[3],look[3],up[3],right[3];
	cout<<"Nhap diem dat camera: ";
	cin>>eye[0]>>eye[1]>>eye[2];
	cout<<"Nhap diem nhin vao: ";
	cin>>look[0]>>look[1]>>look[2];
	cout<<"Nhap diem huong vao: ";
	cin>>up[0]>>up[1]>>up[2];

	//nhan co huong
	right[0]=up[1]*look[2]-up[2]*look[1];
	right[1]=up[2]*look[0]-up[0]*look[2];
	right[2]=up[0]*look[1]-up[1]*look[0];


	camerachange(eye,look,up,right);
	matrixMul1(Matrix);
	cout<<"Diem sau khi doi goc nhin la: ";
	printpoint(MatrixKQ);
}

//Quay quanh truc Ox
void RotateX (float angle)
{
	Matrix44 m;
	matrixSetIdentity(m);
	angle=angle*3.141592653589793238/180;
	m[1][1]=cos(angle);
	m[1][2]=-sin(angle);
	m[2][1]=sin(angle);
	m[2][2]=cos(angle);
	matrixMul(m,Matrix);
	cout<<"Ma tran quay quanh truc ox: "<<endl;
	printMatrix(Matrix);
}
//Quay quanh truc Oy
void RotateY (float angle)
{
	Matrix44 m;
    matrixSetIdentity(m);
    angle=angle*3.141592653589793238/180;
    m[0][0] = cos(angle);
    m[0][2] = sin(angle);
    m[2][0] = -sin(angle);
    m[2][2] = cos(angle);
    matrixMul(m, Matrix);
    cout<<"Ma tran quay quanh truc oy: "<<endl;
    printMatrix(m);

}
//Quay quanh truc Oz
void RotateZ(float angle)
{
    Matrix44 m;
    matrixSetIdentity(m);
    angle=angle*3.141592653589793238/180;
    m[0][0] = cos(angle);
    m[0][1] = -sin(angle);
    m[1][0] = sin(angle);
    m[1][1] = cos(angle);
    matrixMul(m, Matrix);
    cout<<"Ma tran quay quanh truc oz: "<<endl;
    printMatrix(m);
}
void RotatePQ(float* P, float* Q, float angle){
	Matrix44 m1,m2,m3,m4,m5,m6,m7;
	float cx=Q[0]-P[0];
	float cy=Q[1]-P[1];
	float cz=Q[2]-P[2];
	float d=sqrt(cy*cy+cz*cz);
	float l=sqrt(cx*cx+cy*cy+cz*cz);

	//Tinh tien
	matrixSetIdentity(m1);

	m1[0][3]=-P[0];
	m1[1][3]=-P[1];
	m1[2][3]=-P[2];
	cout<<"Ma tran<1> tinh tien Mt: "<<endl;
	printMatrix(m1);

	//Quay truc ox goc alpha
	matrixSetIdentity(m2);

	m2[1][1]=cz/d;
	m2[1][2]=-cy/d;
	m2[2][1]=cy/d;
	m2[2][2]=cz/d;
	cout<<"Ma tran<2> quay truc ox goc alpha: "<<endl;
	printMatrix(m2);

	//Quay truc Oy goc -phi
	matrixSetIdentity(m3);

    m3[0][0] = d/l;
    m3[0][2] = -cx/l;
    m3[2][0] = cx/l;
    m3[2][2] = d/l;

    cout<<"Ma tran<3> quay quanh truc oy goc -phi: "<<endl;
    printMatrix(m3);

    //Quay truc Oz goc de ra:
    matrixSetIdentity(m4);
    angle=angle*3.141592653589793238/180;
    m4[0][0] = cos(angle);
    m4[0][1] = -sin(angle);
    m4[1][0] = sin(angle);
    m4[1][1] = cos(angle);

    cout<<"Ma tran<4> quay quanh truc oz: "<<endl;
    printMatrix(m4);

	//Quay truc Oy goc phi
	matrixSetIdentity(m5);

    m5[0][0] = d/l;
    m5[0][2] = cx/l;
    m5[2][0] = -cx/l;
    m5[2][2] = d/l;

    cout<<"Ma tran<5> quay quanh truc oy goc phi: "<<endl;
    printMatrix(m5);

    //Quay truc ox goc -alpha
	matrixSetIdentity(m6);

	m6[1][1]=cz/d;
	m6[1][2]=cy/d;
	m6[2][1]=-cy/d;
	m6[2][2]=cz/d;
	cout<<"Ma tran<2> quay truc ox goc -alpha: "<<endl;
	printMatrix(m6);

    //Tinh tien
	matrixSetIdentity(m7);

	m7[0][3]=P[0];
	m7[1][3]=P[1];
	m7[2][3]=P[2];
	cout<<"Ma tran<7> tinh tien nguoc Mt: "<<endl;
	printMatrix(m7);

    matrixMul(m1,Matrix);
    matrixMul(m2,Matrix);
    matrixMul(m3,Matrix);
    matrixMul(m4,Matrix);
    matrixMul(m5,Matrix);
    matrixMul(m6,Matrix);
    matrixMul(m7,Matrix);
    cout<<"Ma tran<> bien doi "<<endl;
    printMatrix(Matrix);
}
void display1(){
	matrixSetIdentity(Matrix);
	cout<<"Moi ban chon phep bien doi: "<<endl;
	cout<<"1. Tinh tien"<<endl;
	cout<<"2. Quay quanh truc Ox,Oy,Oz"<<endl;
	cout<<"3. Quay quanh truc PQ bat ky"<<endl;
	cout<<"=>";
	int choice;
	cin>>choice;
	if(choice==1){
		cout<<"Moi ban nhap toa do tinh tien: "<<endl<<"=>";
		float x,y,z;
		cin>>x>>y>>z;
		Translate(x,y,z);
		matrixMul(Matrix);
		printpoint(Matrixkq);
	}
	else if(choice==2){
		cout<<"Moi nhap goc: ";
		float angle;
		cin>>angle;
		cout<<"Moi chon truc quay: "<<endl;
		cout<<"1. Truc Ox"<<endl;
		cout<<"2. Truc Oy"<<endl;
		cout<<"3. Truc Oz"<<endl;
		cout<<"=>";
		cin>>choice;
		switch (choice){
			case 1: RotateX(angle);
					matrixMul(Matrix);
					printpoint(Matrixkq);
					break;
			case 2: RotateY(angle);
					matrixMul(Matrix);
					printpoint(Matrixkq);
					break;
			case 3: RotateZ(angle);
					matrixMul(Matrix);
					printpoint(Matrixkq);
					break;
		}
	}
	else {
		float P[3],Q[3];
		cout<<"Moi nhap diem P: ";
		cin>>P[0]>>P[1]>>P[2];
		cout<<"Moi nhap diem Q: ";
		cin>>Q[0]>>Q[1]>>Q[2];
		cout<<"Moi nhap goc :";
		float angle;
		cin>>angle;
		RotatePQ(P,Q,angle);
		matrixMul(Matrix);
		printpoint(Matrixkq);
	}
}

void xien()
{
	float l,alpha;
	cout<<"Nhap he so rut ngan: ";
	cin>>l;
	cout<<"Nhap goc giua hinh chieu va truc nam ngang: ";
	cin>>alpha;
	alpha=alpha*PI/180;

	Matrix44 m;
	matrixSetIdentity(m);
	m[2][0]=l*cos(alpha);
	m[2][1]=l*sin(alpha);
	m[2][2]=0;

	matrixMul(m,Matrix);
	cout<<"Ma tran chieu xien: "<<endl;
	printMatrix(Matrix);
}
void trucgiao()
{
	Matrix44 m;
	matrixSetIdentity(m);
	cout<<"Lua chon mat chieu truc giao: "<<endl;
	cout<<"1. Mat OXY"<<endl;
	cout<<"2. Mat OXZ"<<endl;
	cout<<"3. Mat OYZ"<<endl;
	int choice;
	cin>>choice;
	switch (choice)
	{
		case 1: m[2][2]=0; break;
		case 2: m[1][1]=0; break;
		case 3: m[0][0]=0; break;
	}
	matrixMul(m,Matrix);
	cout<<"Ma tran chieu truc giao : "<<endl;
	printMatrix(Matrix);
}
void phoicanh()
{
	float b,t,l,r,n,f;
	cout<<"Nhap cac thong so b,t,l,r: ";
	cin>>b>>t>>l>>r;
	cout<<"Nhap cac thong so near, far: ";
	cin>>n>>f;
	Matrix44 m;
	matrixSetIdentity(m);
	m[0][0]=2*n/(r-l);
	m[0][2]=(r+l)/(r-l);
	m[1][1]=2*n/(t-b);
	m[1][2]=(t+b)/(t-b);
	m[2][2]=-(f+n)/(f-n);
	m[2][3]=-2*f*n/(f-n);
	m[3][2]=-1;
	m[3][3]=0;
	cout<<"Ma tran Mpro : "<<endl;
	printMatrix(m);
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			m[i][j]*=(1/-point[2]);
		}
	}
	matrixMul(m,Matrix);
	cout<<"Ma tran chieu phoi canh : "<<endl;
	printMatrix(Matrix);
}

void display3(){
	matrixSetIdentity(Matrix);
	cout<<"Chon loai phep chieu: "<<endl;
	cout<<"1. Phep chieu xien"<<endl;
	cout<<"2. Phep chieu truc giao"<<endl;
	cout<<"3. Phep chieu phoi canh"<<endl;
	cout<<"=>";
	int choice;
	cin>>choice;
	switch (choice)
	{
		case 1: xien();break;
		case 2: trucgiao(); break;
		case 3: phoicanh(); break;
	}
	matrixMul(Matrix);
	cout<<"Toa do cua diem sau khi dieu chinh phep chieu: ";
	printpoint(Matrixkq);
}

void bai1() {
    float x,y,z;
	cout<<"Nhap toa do diem: "<<endl<<"=>";
	cin>>x>>y>>z;
	inputpoint(x,y,z);
	display1();
}

void bai2() {
    float x,y,z;
	cout<<"Nhap toa do diem: "<<endl<<"=>";
	cin>>x>>y>>z;
	inputpoint(x,y,z);
	display2();
}

void bai3() {
    float x,y,z;
	cout<<"Nhap toa do diem: "<<endl<<"=>";
	cin>>x>>y>>z;
	inputpoint(x,y,z);
	display3();
}

int main(){

	bai1();
	//bai2();
	//bai3();
	return 0;
}
