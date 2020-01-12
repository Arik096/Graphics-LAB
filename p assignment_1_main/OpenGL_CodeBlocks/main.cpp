#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <glut.h>
#define pi (2*acos(0.0))
double cameraHeight;
double cameraAngle;
int drawaxes;
double theta;
double forwardmove,tire;
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
            glVertex3f( 100,0,0);
            glVertex3f(-100,0,0);

            glVertex3f(0,-100,0);
            glVertex3f(0, 100,0);

            glVertex3f(0,0, 100);
            glVertex3f(0,0,-100);
        }
        glEnd();
    }
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
void drawCube(double a)
{
    glBegin(GL_QUADS);
    {
        glColor3f(0.0,0.0,1.0);
        glVertex3f( a, a, a);
        glVertex3f( a,-a, a);
        glVertex3f(-a,-a, a);
        glVertex3f(-a, a, a);

        glColor3f(0.0,0.0,1.0);
        glVertex3f( a, a,-a);
        glVertex3f( a,-a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a, a,-a);

        glColor3f(1.0,0,1.0);
        glVertex3f( a, a, a);
        glVertex3f( a, a,-a);
        glVertex3f( a,-a,-a);
        glVertex3f( a,-a, a);

        glColor3f(0.0,1.0,1.0);
        glVertex3f(-a, a, a);
        glVertex3f(-a, a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a,-a, a);

        glColor3f(1.0,0.0,1.0);
        glVertex3f( a, a, a);
        glVertex3f( a, a,-a);
        glVertex3f(-a, a,-a);
        glVertex3f(-a, a, a);

        glColor3f(0.0,1.0,1.0);
        glVertex3f( a,-a, a);
        glVertex3f( a,-a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a,-a, a);
    }
    glEnd();
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
drawRoad(double rs)
{
    //road
    glPushMatrix();
    {
        glTranslatef(0,-20,0);
        glScalef(10,.1,2);
        drawCube(rs);
    }
    glPopMatrix();
}
drawJeep(double js)
{
    glTranslatef(tire,0,0);
    //main box
    glPushMatrix();
    {
        glTranslatef(0,35,0);
        glScalef(1.5,1,1);
        drawCube(js);
    }
    glPopMatrix();

    //front box

    glPushMatrix();
    {
        glTranslatef(40,25,0);
        glScalef(1,.5,1);
        drawCube(js);
    }
    glPopMatrix();


}
void drawWindow(double ws)
{

    //window 1
    glPushMatrix();
    {
        glScalef(.5,.4,1);
        glTranslatef(-25,100,20);
        drawSquare(ws);
    }
    glPopMatrix();
    //window 2
    glPushMatrix();
    {
        glScalef(.5,.4,1);
        glTranslatef(25,100,20);
        drawSquare(ws);
    }
    glPopMatrix();
}
void drawWheel()
{
    // 1st tire
    glPushMatrix();
    {
        glTranslatef(-10,0,18);
        glColor3f(0,0,1); //RGB
        glRotatef(theta,0,0,1);
        drawCylinder(15,4,15);
    }
    glPopMatrix();
    //2nd tire
    glPushMatrix();
    {
        glTranslatef(-10,0,-18);
        glColor3f(0,0,1);
        glRotatef(theta,0,0,1);
        drawCylinder(15,4,15);
    }
    glPopMatrix();
    //3rd tire
    glPushMatrix();
    {
        glTranslatef(40,0,18);
        glColor3f(0,0,1);
        glRotatef(theta,0,0,1);
        drawCylinder(15,4,15);
    }
    glPopMatrix();
    //4th tire
    glPushMatrix();
    {
        glTranslatef(40,0,-18);
        glColor3f(0,0,1);
        glRotatef(theta,0,0,1);
        drawCylinder(15,4,15);
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
    gluLookAt(0,0,200,	0,0,0,	0,1,0);
    glMatrixMode(GL_MODELVIEW);
    drawAxes();
    double jeepsize=20;
    double roadsize=20;
    double windowsize=20;
    drawRoad(roadsize);
    drawJeep(jeepsize);
    drawWindow(windowsize);
    drawWheel();
    glutSwapBuffers();
}
void animate()
{
    theta=theta-0.3;
    forwardmove=((2*pi*15)/360)*0.3;
    tire=tire+forwardmove;
    if(tire>200)
    {
        tire=-200;
    }
    glutPostRedisplay();
}
void init()
{
    drawaxes=1;
    cameraHeight=150.0;
    cameraAngle=1.0;
    theta=0;
    forwardmove=0;
    tire=0;
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
