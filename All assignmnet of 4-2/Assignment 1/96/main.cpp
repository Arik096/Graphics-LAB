#include<bits/stdc++.h>
#include <windows.h>
#include <glut.h>
#define pi (2*acos(0.0))
using namespace std;
double cameraHeight;
double cameraAngle;
int drawaxes;
double angle;
double tx;
double dx;
struct point
{
    double x,y,z;
};
void drawAxes()
{
    if(drawaxes==1)
        {
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_LINES);
            {
                glVertex3f( 900,0,0);
                glVertex3f(-900,0,0);
                glVertex3f(0,-900,0);
                glVertex3f(0, 900,0);
                glVertex3f(0,0, 900);
                glVertex3f(0,0,-900);
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
        glColor3f(1.0,0.0,0.0);
        glVertex3f( a, a, a);
        glVertex3f( a,-a,a);
        glVertex3f(-a,-a,a);
        glVertex3f(-a, a,a);
        glColor3f(0.0,1.0,0.0);
        glVertex3f( a, a, -a);
        glVertex3f( a,-a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a, a,-a);
        glColor3f(0.0,0.0,1.0);
        glVertex3f( a, a, a);
        glVertex3f(a, a,-a);
        glVertex3f(a,-a,-a);
        glVertex3f(a,-a, a);
        glColor3f(1.0,1.0,0.0);
        glVertex3f( -a, a, a);
        glVertex3f(-a, a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a,-a, a);
        glColor3f(1.0,0.0,1.0);
        glVertex3f( a,a, a);
        glVertex3f( a,a,-a);
        glVertex3f(-a,a,-a);
        glVertex3f(-a,a, a);
        glColor3f(1.0,1.0,1.0);
        glVertex3f( a,-a, a);
        glVertex3f( a,-a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a,-a, a);
    }
    glEnd();
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
            glColor3f(1.0,1.0,0.0);
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
            drawCube(a);
        }
        glPopMatrix();
        glPushMatrix();
        {
            //side 2
            glRotatef(30,0,0,1);
            glTranslatef(22,-10,0);
            glScalef(.2,2,1);
            drawCube(a);
        }
        glPopMatrix();
        glPushMatrix();
        {
            //roof
            glTranslatef(0,20,0);
            glScalef(1.7,.2,1);
            drawCube(a);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
void drawSS()
{
    double a=10;
    glPushMatrix();
    {
        // road segment
        glTranslatef(0,-20,0);
        glScalef(100,1,2);
        glBegin(GL_QUADS);
        {
            glColor3f(1,1,1);
            glVertex3f( a,a, a);
            glVertex3f( a,a,-a);
            glVertex3f(-a,a,-a);
            glVertex3f(-a,a, a);
        }
        glEnd();
    }
    glPopMatrix();
    glTranslatef(tx,6,0);
    glPopMatrix();
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
        drawCube(a);
    }
    glPopMatrix();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(00,00,200,	0,0,0,	0,1,0);
    glMatrixMode(GL_MODELVIEW);
    drawAxes();
    drawSS();
    glutSwapBuffers();
}
void animate()
{
    angle+=.2;
    dx=((2*pi*15)/360)*.2;
    tx=tx-dx;
    if(tx<-240)
        tx=240;
    glutPostRedisplay();
}
void init()
{
    drawaxes=0;
    cameraHeight=150.0;
    cameraAngle=1.0;
    angle=0;
    tx=0;
    dx=0;
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80,	1,	1,	1000.0);
}
int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("My OpenGL Program");
    init();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();
    return 0;
}
