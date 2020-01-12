#include<bits/stdc++.h>
#include <windows.h>
#include <glut.h>
#define pi (2*acos(0.0))
using namespace std;
double cameraHeight;
double cameraAngle;
int drawaxes=0;
double posx=750;
double posy=100;
double posz=00;
double lx=-1/sqrt(2);
double ly=-1/sqrt(2);
double lz=0;
double rx=-1/sqrt(2);
double ry=1/sqrt(2);
double rz=0;
double ux=0;
double uy=0;
double uz=1;
double bridge_angle=0;
double angle=0;
double tx1=0;
double tx2=0;
double tx3=0;
double tx4=0;
double tx5=0;
double tx6=0;
double dx=0;
struct point
{
    double x,y,z;
};
void drawAxes()
{
    if(drawaxes==1)
    {
        glColor3f(1, 1, 1);
        glBegin(GL_LINES);
        {
            glVertex3f( 500,0,0);
            glVertex3f(-500,0,0);
            glVertex3f(0,-500,0);
            glVertex3f(0, 500,0);
            glVertex3f(0,0, 500);
            glVertex3f(0,0,-500);
        }
        glEnd();
    }
}
void drawCylinder(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    for(i=0; i<=segments; i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    glColor3f(1,0,1);
    for(i=0; i<segments; i++)
    {
        glBegin(GL_QUADS);
        {
            glVertex3f(points[i].x,points[i].y,height/2);
            glVertex3f(points[i+1].x,points[i+1].y,height/2);
            glVertex3f(points[i].x,points[i].y,-height/2);
            glVertex3f(points[i+1].x,points[i+1].y,-height/2);
        }
        glEnd();
    }
}
void drawCube(double a)
{
    glBegin(GL_QUADS);
    {
        glVertex3f( a, a, a);
        glVertex3f( a,-a,a);
        glVertex3f(-a,-a,a);
        glVertex3f(-a, a,a);
        glVertex3f( a, a, -a);
        glVertex3f( a,-a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a, a,-a);
        glVertex3f( a, a, a);
        glVertex3f(a, a,-a);
        glVertex3f(a,-a,-a);
        glVertex3f(a,-a, a);
        glVertex3f( -a, a, a);
        glVertex3f(-a, a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a,-a, a);
        glVertex3f( a,a, a);
        glVertex3f( a,a,-a);
        glVertex3f(-a,a,-a);
        glVertex3f(-a,a, a);
        glVertex3f( a,-a, a);
        glVertex3f( a,-a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a,-a, a);
    }
    glEnd();
}
void drawSquare(double a)
{
    glBegin(GL_QUADS);
    {
        glVertex3f( a, a,2);
        glVertex3f( a,-a,2);
        glVertex3f(-a,-a,2);
        glVertex3f(-a, a,2);
    }
    glEnd();
}
void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    for(i=0; i<=segments; i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    for(i=0; i<segments; i++)
    {
        glBegin(GL_LINES);
        {
            glVertex3f(points[i].x,points[i].y,0);
            glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}
void drawCone(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    for(i=0; i<=segments; i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    for(i=0; i<segments; i++)
    {
        if(i<segments/2)
            shade=2*(double)i/(double)segments;
        else
            shade=2*(1.0-(double)i/(double)segments);
        glColor3f(shade,shade,shade);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
            glVertex3f(points[i].x,points[i].y,0);
            glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}
void drawSphere(double radius,int slices,int stacks)
{
    struct point points[100][100];
    int i,j;
    double h,r;
    for(i=0; i<=stacks; i++)
    {
        h=radius*sin(((double)i/(double)stacks)*(pi/2));
        r=radius*cos(((double)i/(double)stacks)*(pi/2));
        for(j=0; j<=slices; j++)
        {
            points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
            points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
            points[i][j].z=h;
        }
    }
    for(i=0; i<stacks; i++)
    {
        glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
        for(j=0; j<slices; j++)
        {
            glBegin(GL_QUADS);
            {
                glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
                glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
                glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
                glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
            }
            glEnd();
        }
    }
}
void drawBoat()
{
    glPushMatrix();
    {
        glScalef(3,.5,.5);
        glRotatef(90,1,0,0);
        drawCone(50,50,50);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(-60,15,-10);
        glScalef(.1,1,.2);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(-60,15,10);
        glScalef(.1,1,.2);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(60,15,-10);
        glScalef(.1,1,.2);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(60,15,10);
        glScalef(.1,1,.2);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,35,0);
        glScalef(4,.1,1);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
}
void drawDriver(double a)
{
    glPushMatrix();
    {
        glTranslatef(0,33,0);
        glPushMatrix();
        {
            //head 1
            glTranslatef(10,0,7);
            drawSphere(5,24,20);
        }
        glPopMatrix();
        glPushMatrix();
        {
            //body 1
            glTranslatef(10,0,7);
            glScalef(.2,.5,.2);
            glTranslatef(0,-15,0);
            glColor3f(1.0,0.0,1.0);
            drawCube(a);
        }
        glPopMatrix();
        glPushMatrix();
        {
            //head 2
            glTranslatef(10,0,-7);
            drawSphere(5,24,20);
        }
        glPopMatrix();
        glPushMatrix();
        {
            //body 2
            glTranslatef(10,0,-7);
            glScalef(.2,.5,.2);
            glTranslatef(0,-15,0);
            drawCube(a);
        }
        glPopMatrix();
        glPushMatrix();
        {
            //head 3
            glTranslatef(-4,0,7);
            drawSphere(5,24,20);
        }
        glPopMatrix();
        glPushMatrix();
        {
            //body 3
            glTranslatef(-4,0,7);
            glScalef(.2,.5,.2);
            glTranslatef(0,-15,0);
            drawCube(a);
        }
        glPopMatrix();
        glPushMatrix();
        {
            //head 4
            glTranslatef(-4,0,-7);
            drawSphere(5,24,20);
        }
        glPopMatrix();
        glPushMatrix();
        {
            //body 4
            glTranslatef(-4,0,-7);
            glScalef(.2,.5,.2);
            glTranslatef(0,-15,0);
            drawCube(a);
        }
        glPopMatrix();
        glPushMatrix();
        {
            //side 1
            glRotatef(330,0,0,1);
            glTranslatef(-22,-10,0);
            glScalef(.2,2,1);
            glColor3f(0.0f, 0.5f, 0.5f);
            drawCube(a);
        }
        glPopMatrix();
        glPushMatrix();
        {
            //side 2
            glRotatef(30,0,0,1);
            glTranslatef(22,-10,0);
            glScalef(.2,2,1);
            glColor3f(0.0f, 0.5f, 0.5f);
            drawCube(a);
        }
        glPopMatrix();
        glPushMatrix();
        {
            //roof
            glTranslatef(0,20,0);
            glScalef(1.7,.2,1);
            glColor3f(0.0f, 0.5f, 1.0f);
            drawCube(a);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
void drawCar()
{
    double a=10;
    drawDriver(a);
    glPushMatrix();
    {
        //1st tire segment
        glTranslatef(-30,0,13);
        glRotatef(angle,0,0,1);
        drawCylinder(15,5,20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        //2nd tire segment
        glTranslatef(30,0,13);
        glRotatef(angle,0,0,1);
        drawCylinder(15,5,20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        //3rd tire segment
        glTranslatef(-30,0,-13);
        glRotatef(angle,0,0,1);
        drawCylinder(15,5,20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        //4th tire segment
        glTranslatef(30,0,-13);
        glRotatef(angle,0,0,1);
        drawCylinder(15,5,20);
    }
    glPopMatrix();
    glTranslatef(0,10,0);
    glPushMatrix();
    {
        // car main box segment
        glScalef(6,1,1);
        glColor3f(0.1f, 0.1f, 0.0f);
        drawCube(a);
    }
    glPopMatrix();
}
void drawHouse5()
{
    glPushMatrix();
    {
        glScalef(1.5,5,1.5);
        glColor3f(0.5f, 0.5f, 0.5f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,100,0);
        glScalef(1.6,.2,1.6);
        glColor3f(0.0f, 0.5f, 1.0f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,60,0);
        glScalef(1.6,.2,1.6);
        glColor3f(0.0f, 0.5f, 1.0f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,20,0);
        glScalef(1.6,.2,1.6);
        glColor3f(0.0f, 0.5f, 1.0f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,-20,0);
        glScalef(1.6,.2,1.6);
        glColor3f(0.0f, 0.5f, 1.0f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,-60,0);
        glScalef(1.6,.2,1.6);
        glColor3f(0.0f, 0.5f, 1.0f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,-100,0);
        glScalef(1.6,.2,1.6);
        glColor3f(0.0f, 0.5f, 1.0f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,-45,0);
        glScalef(1.6,.6,.4);
        glColor3f(0.1f, 0.1f, 0.1f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,0,15);
        glScalef(1.6,.4,.4);
        glColor3f(0.1f, 0.1f, 0.1f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,0,-15);
        glScalef(1.6,.4,.4);
        glColor3f(0.1f, 0.1f, 0.1f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,40,15);
        glScalef(1.6,.4,.4);
        glColor3f(0.1f, 0.1f, 0.1f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,40,-15);
        glScalef(1.6,.4,.4);
        glColor3f(0.1f, 0.1f, 0.1f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,80,15);
        glScalef(1.6,.4,.4);
        glColor3f(0.1f, 0.1f, 0.1f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,80,-15);
        glScalef(1.6,.4,.4);
        glColor3f(0.1f, 0.1f, 0.1f);
        drawCube(20);
    }
    glPopMatrix();
}
void drawHouse2()
{
    glPushMatrix();
    {
        glScalef(1.5,3,1.5);
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glScalef(1.6,.2,1.6);
        glColor3f(0.0f, 0.5f, 1.0f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,60,0);
        glScalef(1.6,.2,1.6);
        glColor3f(0.0f, 0.5f, 1.0f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,-60,0);
        glScalef(1.6,.2,1.6);
        glColor3f(0.0f, 0.5f, 1.0f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,-40,0);
        glScalef(1.6,.8,.4);
        glColor3f(0.1f, 0.1f, 0.1f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,35,15);
        glScalef(1.6,.6,.6);
        glColor3f(0.1f, 0.1f, 0.1f);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,35,-15);
        glScalef(1.6,.6,.6);
        glColor3f(0.1f, 0.1f, 0.1f);
        drawCube(20);
    }
    glPopMatrix();

}
void drawSurfaceRiver()
{
    glPushMatrix();
    {
        /// whole surface and river
        glTranslatef(0,-200,0);
        glPushMatrix();
        {
            /// lower surface
            glScalef(40,.3,30);
            glColor4f(1.0f, 0.0f, 1.0f, 0.0f);
            drawCube(10);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// river
            glTranslatef(0,20,0);
            glScalef(20,2,30);
            glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
            drawCube(10);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// left upper surface
            glTranslatef(-300,50,0);
            glScalef(10,5,30);
            glColor4f(1.0f, 0.0f, 1.0f, 0.0f);
            drawCube(10);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// right upper surface
            glTranslatef(300,50,0);
            glScalef(10,5,30);
            glColor4f(1.0f, 0.0f, 1.0f, 0.0f);
            drawCube(10);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// left road
            glTranslatef(-252,100,0);
            glScalef(1,.1,5.8);
            glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
            drawCube(50);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// right road
            glTranslatef(252,100,0);
            glScalef(1,.1,5.8);
            glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
            drawCube(50);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
void  drawBridge()
{
    glPushMatrix();
    {
        /// bridge right side control
        glTranslatef(100,0,0);
        glPushMatrix();
        {
            /// 4 pillar control
            glTranslatef(0,-140,0);
            glPushMatrix();
            {
                /// 1st pillar
                glTranslatef(-45,0,40);
                glRotatef(90,1,0,0);
                drawCylinder(10,60,5);
            }
            glPopMatrix();
            glPushMatrix();
            {
                /// 2nd pillar
                glTranslatef(-45,0,-40);
                glRotatef(90,1,0,0);
                drawCylinder(10,60,5);
            }
            glPopMatrix();
            glPushMatrix();
            {
                /// 3rd pillar
                glTranslatef(45,0,40);
                glRotatef(90,1,0,0);
                drawCylinder(10,60,5);
            }
            glPopMatrix();
            glPushMatrix();
            {
                /// 4th pillar
                glTranslatef(45,0,-40);
                glRotatef(90,1,0,0);
                drawCylinder(10,60,5);
            }
            glPopMatrix();
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// road over bridge
            glTranslatef(0,-105,0);
            glScalef(1.7,.1,1);
            glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 1 over bridge
            glTranslatef(0,-30,50);
            glScalef(1.2,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 2 over bridge
            glTranslatef(0,-30,-50);
            glScalef(1.2,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 1 angle 1 over bridge
            glTranslatef(-80,-65,50);
            glRotatef(70,0,0,1);
            glScalef(.7,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 1 angle 2 over bridge
            glTranslatef(-80,-65,-50);
            glRotatef(70,0,0,1);
            glScalef(.7,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 2 angle 1 over bridge
            glTranslatef(80,-65,50);
            glRotatef(290,0,0,1);
            glScalef(.7,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 2 angle 2 over bridge
            glTranslatef(80,-65,-50);
            glRotatef(290,0,0,1);
            glScalef(.7,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 1 angle 3 over bridge
            glTranslatef(25,-65,50);
            glRotatef(50,0,0,1);
            glScalef(.7,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 1 angle 4 over bridge
            glTranslatef(25,-65,-50);
            glRotatef(50,0,0,1);
            glScalef(.7,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 2 angle 3 over bridge
            glTranslatef(-25,-65,50);
            glRotatef(310,0,0,1);
            glScalef(.7,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 2 angle 4 over bridge
            glTranslatef(-25,-65,-50);
            glRotatef(310,0,0,1);
            glScalef(.7,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();
    {
        /// bridge left side control
        glTranslatef(-100,0,0);
        glPushMatrix();
        {
            /// 4 pillar control
            glTranslatef(0,-140,0);
            glPushMatrix();
            {
                /// 1st pillar
                glTranslatef(-45,0,40);
                glRotatef(90,1,0,0);
                drawCylinder(10,60,5);
            }
            glPopMatrix();
            glPushMatrix();
            {
                /// 2nd pillar
                glTranslatef(-45,0,-40);
                glRotatef(90,1,0,0);
                drawCylinder(10,60,5);
            }
            glPopMatrix();
            glPushMatrix();
            {
                /// 3rd pillar
                glTranslatef(45,0,40);
                glRotatef(90,1,0,0);
                drawCylinder(10,60,5);
            }
            glPopMatrix();
            glPushMatrix();
            {
                /// 4th pillar
                glTranslatef(45,0,-40);
                glRotatef(90,1,0,0);
                drawCylinder(10,60,5);
            }
            glPopMatrix();
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// road over bridge
            glTranslatef(0,-105,0);
            glScalef(1.7,.1,1);
            glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 1 over bridge
            glTranslatef(0,-30,50);
            glScalef(1.2,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 2 over bridge
            glTranslatef(0,-30,-50);
            glScalef(1.2,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 1 angle 1 over bridge
            glTranslatef(-80,-65,50);
            glRotatef(70,0,0,1);
            glScalef(.7,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 1 angle 2 over bridge
            glTranslatef(-80,-65,-50);
            glRotatef(70,0,0,1);
            glScalef(.7,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 2 angle 1 over bridge
            glTranslatef(80,-65,50);
            glRotatef(290,0,0,1);
            glScalef(.7,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 2 angle 2 over bridge
            glTranslatef(80,-65,-50);
            glRotatef(290,0,0,1);
            glScalef(.7,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 1 angle 3 over bridge
            glTranslatef(25,-65,50);
            glRotatef(50,0,0,1);
            glScalef(.7,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 1 angle 4 over bridge
            glTranslatef(25,-65,-50);
            glRotatef(50,0,0,1);
            glScalef(.7,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 2 angle 3 over bridge
            glTranslatef(-25,-65,50);
            glRotatef(310,0,0,1);
            glScalef(.7,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
        glPushMatrix();
        {
            /// side 2 angle 4 over bridge
            glTranslatef(-25,-65,-50);
            glRotatef(310,0,0,1);
            glScalef(.7,.1,.1);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            drawCube(60);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
void drawCars()
{
    glPushMatrix();
    {
        glScalef(.7,.7,.7);
        // car 1
        glPushMatrix();
        {
            glTranslatef(tx1,0,0);
            glTranslatef(200,-125,40);
            drawCar();
        }
        glPopMatrix();
        // car 2
        glPushMatrix();
        {
            glTranslatef(tx2,0,0);
            glTranslatef(-200,-125,-20);
            drawCar();
        }
        glPopMatrix();
        // car 3
        glPushMatrix();
        {
            glTranslatef(0,0,tx4);
            glTranslatef(-400,-120,-350);
            glRotatef(90,0,1,0);
            drawCar();
        }
        glPopMatrix();
        // car 4
        glPushMatrix();
        {
            glTranslatef(0,0,tx3);
            glTranslatef(-300,-120,350);
            glRotatef(90,0,1,0);
            drawCar();
        }
        glPopMatrix();
        // car 5
        glPushMatrix();
        {
            glTranslatef(0,0,tx4);
            glTranslatef(300,-120,-350);
            glRotatef(90,0,1,0);
            drawCar();
        }
        glPopMatrix();
        // car 6
        glPushMatrix();
        {
            glTranslatef(0,0,tx3);
            glTranslatef(400,-120,350);
            glRotatef(90,0,1,0);
            drawCar();
        }
        glPopMatrix();
    }
    glPopMatrix();
}
void drawBuildings()
{
    glPushMatrix();
    {
        glTranslatef(-350,-35,-250);
        drawHouse2();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(-350,-35,-150);
        drawHouse5();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(-350,-35,-50);
        drawHouse2();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(-350,-35,50);
        drawHouse2();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(-350,-35,150);
        drawHouse5();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(-350,-35,250);
        drawHouse5();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(350,-35,250);
        drawHouse2();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(350,-35,150);
        drawHouse5();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(350,-35,50);
        drawHouse2();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(350,-35,-50);
        drawHouse2();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(350,-35,-150);
        drawHouse5();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(350,-35,-250);
        drawHouse5();
    }
    glPopMatrix();
}
void drawBoats()
{
    glPushMatrix();
    {
        glTranslatef(0,0,tx5);
        glScalef(.7,.7,.7);
        glTranslatef(-130,-200,350);
        glRotatef(90,0,1,0);
        drawBoat();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,0,tx6);
        glScalef(.7,.7,.7);
        glTranslatef(130,-200,-350);
        glRotatef(90,0,1,0);
        drawBoat();
    }
    glPopMatrix();
}
void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {

    case 'q':
        posx=posx+lx;
        posy=posy+ly;
        posz=posz+lz;
        break;
    case 'w':
        posx=posx-lx;
        posy=posy-ly;
        posz=posz-lz;
        break;
    case 'a':
        posx=posx+rx;
        posy=posy+ry;
        posz=posz+rz;
        break;
    case 's':
        posx=posx-rx;
        posy=posy-ry;
        posz=posz-rz;
        break;
    case 'z':
        posx=posx+ux;
        posy=posy+uy;
        posz=posz+uz;
        break;
    case 'x':
        posx=posx-ux;
        posy=posy-uy;
        posz=posz-uz;
        break;

    default:
        break;
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posx,posy,posz,	posx+lx,posy+lz,posz+lz,	0,1,0);
    glMatrixMode(GL_MODELVIEW);
    drawAxes();
    glPushMatrix();
    {
        glRotatef(90,0,1,0);
        drawSurfaceRiver();
        drawBridge();
        drawCars();
        drawBuildings();
        drawBoats();
    }
    glPopMatrix();
    glutSwapBuffers();
}
void animate()
{
    angle+=2;
    dx=((2*pi*15)/360)*2;
    tx1=tx1-dx;
    if(tx1<-420)
        tx1=0;
    tx2=tx2+dx;
    if(tx2>420)
        tx2=0;
    tx3=tx3-dx;
    if(tx3<-720)
        tx3=0;
    tx4=tx4+dx;
    if(tx4>720)
        tx4=0;
    tx5=tx5-dx;
    if(tx5<-500)
        tx5=0;
    tx6=tx6+dx;
    if(tx6>500)
        tx6=0;
    glutPostRedisplay();
}
void init()
{
    cameraHeight=150.0;
    cameraAngle=1.0;
    bridge_angle=0;
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80,	1,	1,	1000.0);
}
int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(1400, 900);
    glutInitWindowPosition(00, 100);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("City Bridge Project");
    init();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutKeyboardFunc(keyboardListener);
    glutMainLoop();
    return 0;
}
