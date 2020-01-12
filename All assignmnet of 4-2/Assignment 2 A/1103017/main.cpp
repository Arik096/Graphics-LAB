#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <glut.h>
#define pi (2*acos(0.0))
double cameraHeight;
double cameraAngle;
int drawaxes;
double angle;
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
void drawRoad()
{
    glPushMatrix(); // Draw the main ground
    {
        glTranslatef(0,-100,0);
        glScalef(20,.001,15);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the road of over-bridge on the ground
    {
        glTranslatef(0,-99,0);
        glScalef(20,.001,7);
        glColor3f(1,0,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the road on the ground
    {
        glTranslatef(-100,-99,0);
        glScalef(5,.001,15);
        glColor3f(1,0,0);
        drawCube(20);
    }
    glPopMatrix();

}
void drawFootpath()
{
    glPushMatrix(); // Draw front left footpath 1
    {
        glTranslatef(-220,-99,220);
        glScalef(1,.001,4);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw front left footpath 2
    {
        glTranslatef(-320,-99,160);
        glScalef(4,.001,1);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw front right footpath 1
    {
        glTranslatef(20,-99,220);
        glScalef(1,.001,4);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw front right footpath 2
    {
        glTranslatef(220,-99,170);
        glScalef(9,.001,1.5);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back left footpath 1
    {
        glTranslatef(-220,-99,-220);
        glScalef(1,.001,4);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back left footpath 2
    {
        glTranslatef(-320,-99,-160);
        glScalef(4,.001,1);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back right footpath 1
    {
        glTranslatef(20,-99,-220);
        glScalef(1,.001,4);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back right footpath 2
    {
        glTranslatef(220,-99,-170);
        glScalef(9,.001,1.5);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
}
void drawPolicebox()
{
    glPushMatrix(); // Draw the base of the police box
    {
        glTranslatef(-100,-85,0);
        glScalef(1,.3,1);
        glColor3f(1,.5,0);
        drawCube(50);
    }
    glPopMatrix();
    glPushMatrix(); // Draw front left pole
    {
        glTranslatef(-140,-10,45);
        glRotatef(90,1,0,0);
        drawCylinder(5,140,10);
    }
    glPopMatrix();
    glPushMatrix(); // Draw front right pole
    {
        glTranslatef(-55,-10,45);
        glRotatef(90,1,0,0);
        drawCylinder(5,140,10);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back left pole
    {
        glTranslatef(-140,-10,-45);
        glRotatef(90,1,0,0);
        drawCylinder(5,140,10);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back right pole
    {
        glTranslatef(-55,-10,-45);
        glRotatef(90,1,0,0);
        drawCylinder(5,140,10);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the roof of the police box
    {
        glTranslatef(-100,50,0);
        glScalef(1,.3,1);
        glColor3f(1,.5,0);
        drawCube(50);
    }
    glPopMatrix();
}
void drawOverbridge()
{
    glPushMatrix();
    {
        glTranslatef(75,0,0);
        glPushMatrix(); // draw the main box of over-bridge
        {
            glTranslatef(130,50,0);
            glScalef(2,.2,7);
            glColor3f(1,1,0);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side of main box of over-bridge 1
        {
            glTranslatef(95,90,0);
            glScalef(.1,.1,7.2);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side of main box of over-bridge 2
        {
            glTranslatef(95,70,0);
            glScalef(.1,.1,7.2);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side of main box of over-bridge 1
        {
            glTranslatef(165,90,0);
            glScalef(.1,.1,7.2);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side of main box of over-bridge 2
        {
            glTranslatef(165,70,0);
            glScalef(.1,.1,7.2);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side front edge of main box of over-bridge
        {
            glTranslatef(100,70,138);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side middle edge of main box of over-bridge
        {
            glTranslatef(100,70,0);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back edge of main box of over-bridge
        {
            glTranslatef(100,70,-138);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side front edge of main box of over-bridge
        {
            glTranslatef(160,70,138);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side middle edge of main box of over-bridge
        {
            glTranslatef(160,70,0);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back edge of main box of over-bridge
        {
            glTranslatef(160,70,-138);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the front pillar
        {
            glTranslatef(130,-30,100);
            glRotatef(90,1,0,0);
            drawCylinder(20,150,10);
        }
        glPopMatrix();
        glPushMatrix(); // draw the back pillar
        {
            glTranslatef(130,-30,-100);
            glRotatef(90,1,0,0);
            drawCylinder(20,150,10);
        }
        glPopMatrix();
        glPushMatrix(); // draw the front box of over-bridge
        {
            glTranslatef(130,50,160);
            glScalef(2,.2,1);
            glColor3f(1,1,0);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the back box of over-bridge
        {
            glTranslatef(130,50,-160);
            glScalef(2,.2,1);
            glColor3f(1,1,0);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the side of front box
        {
            glTranslatef(130,0,270);
            glScalef(.28,1,1);
            glRotatef(90,0,1,0);
            glPushMatrix();
            {
                glTranslatef(95,90,0);
                glScalef(.1,.1,7);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,0);
                glScalef(.1,.1,7);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,138);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,0);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,-138);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
        }
        glPopMatrix();
        glPushMatrix(); // draw the side of back box
        {
            glTranslatef(130,0,-80);
            glScalef(.28,1,1);
            glRotatef(90,0,1,0);
            glPushMatrix();
            {
                glTranslatef(95,90,0);
                glScalef(.1,.1,7);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,0);
                glScalef(.1,.1,7);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,138);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,0);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,-138);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix(); // Draw the slide of front left
    {
        glTranslatef(105,-25,160);
        glRotatef(50,0,0,1);
        glScalef(5,.2,1);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the slide of front right
    {
        glTranslatef(305,-25,160);
        glRotatef(310,0,0,1);
        glScalef(5,.2,1);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the slide of back left
    {
        glTranslatef(105,-25,-160);
        glRotatef(50,0,0,1);
        glScalef(5,.2,1);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the slide of back right
    {
        glTranslatef(305,-25,-160);
        glRotatef(310,0,0,1);
        glScalef(5,.2,1);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front lower edge 1
    {
        glTranslatef(40,-80,175);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front lower edge 2
    {
        glTranslatef(40,-80,145);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front slider hand 1
    {
        glTranslatef(103,15,175);
        glRotatef(50,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front slider hand 2
    {
        glTranslatef(105,-5,175);
        glRotatef(50,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front slider hand 3
    {
        glTranslatef(103,15,145);
        glRotatef(50,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front slider hand 4
    {
        glTranslatef(105,-5,145);
        glRotatef(50,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,0,-320);
        glPushMatrix(); // draw the left side back lower edge 1
        {
            glTranslatef(40,-80,175);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back lower edge 2
        {
            glTranslatef(40,-80,145);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back slider hand 1
        {
            glTranslatef(103,15,175);
            glRotatef(50,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back slider hand 2
        {
            glTranslatef(105,-5,175);
            glRotatef(50,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back slider hand 3
        {
            glTranslatef(103,15,145);
            glRotatef(50,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back slider hand 4
        {
            glTranslatef(105,-5,145);
            glRotatef(50,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front lower edge 1
    {
        glTranslatef(370,-80,175);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front lower edge 2
    {
        glTranslatef(370,-80,145);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front lower edge 1
    {
        glTranslatef(370,-80,175);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front lower edge 2
    {
        glTranslatef(370,-80,145);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front slider hand 1
    {
        glTranslatef(305,15,175);
        glRotatef(310,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front slider hand 2
    {
        glTranslatef(305,15,145);
        glRotatef(310,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front slider hand 3
    {
        glTranslatef(300,3,175);
        glRotatef(310,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front slider hand 4
    {
        glTranslatef(303,0,145);
        glRotatef(310,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,0,-320);
        glPushMatrix(); // draw the right side back lower edge 1
        {
            glTranslatef(370,-80,175);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back lower edge 2
        {
            glTranslatef(370,-80,145);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back slider hand 1
        {
            glTranslatef(305,15,175);
            glRotatef(310,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back slider hand 2
        {
            glTranslatef(305,15,145);
            glRotatef(310,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back slider hand 3
        {
            glTranslatef(303,3,175);
            glRotatef(310,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back slider hand 4
        {
            glTranslatef(300,0,145);
            glRotatef(310,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
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
    gluLookAt(400,300,700,	0,0,0,	0,1,0);
    glMatrixMode(GL_MODELVIEW);
    drawAxes();
    drawRoad();
    drawFootpath();
    drawPolicebox();
    drawOverbridge();
    glutSwapBuffers();
}
void animate()
{
    glutPostRedisplay();
}
void init()
{
    drawaxes=0;
    cameraHeight=150.0;
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80,	1,	1,	1000.0);
}
int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(1300, 900);
    glutInitWindowPosition(0,100);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("My OpenGL Program");
    init();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();
    return 0;
}
