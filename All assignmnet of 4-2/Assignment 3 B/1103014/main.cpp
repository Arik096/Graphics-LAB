#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
double angle2;
double tx,dx,a,r;
double tx2;

double posx;
double posy;
double posz;
double lx=-1/sqrt(2);
double ly=-1/sqrt(2);
double lz=0;
double rx=-1/sqrt(2);
double ry=1/sqrt(2);
double rz=0;
double ux=0;
double uy=0;
double uz=1;

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


void drawGrid()
{
    int i;
    if(drawgrid==1)
        {
            glColor3f(0.6, 0.6, 0.6);	//grey
            glBegin(GL_LINES);
            {
                for(i=-8; i<=8; i++)
                    {

                        if(i==0)
                            continue;	//SKIP the MAIN axes

                        //lines parallel to Y-axis
                        glVertex3f(i*10, -90, 0);
                        glVertex3f(i*10,  90, 0);

                        //lines parallel to X-axis
                        glVertex3f(-90, i*10, 0);
                        glVertex3f( 90, i*10, 0);
                    }
            }
            glEnd();
        }
}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    {
        glVertex3f( a/2, a/2,2);
        glVertex3f( a/2,-a/2,2);
        glVertex3f(-a/2,-a/2,2);
        glVertex3f(-a/2, a/2,2);
    }
    glEnd();
}


void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0; i<=segments; i++)
        {
            points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
            points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
        }
    //draw segments using generated points
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
    //generate points
    for(i=0; i<=segments; i++)
        {
            points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
            points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
        }
    //draw triangles using generated points
    for(i=0; i<segments; i++)
        {
            //create shading effect
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


void drawCube(double a)
{
    glBegin(GL_QUADS);
        {
            glVertex3f( a, a, a);
            glVertex3f( a,-a, a);
            glVertex3f(-a,-a, a);
            glVertex3f(-a, a, a);

            glVertex3f( a, a,-a);
            glVertex3f( a,-a,-a);
            glVertex3f(-a,-a,-a);
            glVertex3f(-a, a,-a);

            glVertex3f( a, a, a);
            glVertex3f( a, a,-a);
            glVertex3f( a,-a,-a);
            glVertex3f( a,-a, a);

            glVertex3f(-a, a, a);
            glVertex3f(-a, a,-a);
            glVertex3f(-a,-a,-a);
            glVertex3f(-a,-a, a);

            glVertex3f( a, a, a);
            glVertex3f( a, a,-a);
            glVertex3f(-a, a,-a);
            glVertex3f(-a, a, a);

            glVertex3f( a,-a, a);
            glVertex3f( a,-a,-a);
            glVertex3f(-a,-a,-a);
            glVertex3f(-a,-a, a);
        }
        glEnd();
}

void drawSphere(double radius,int slices,int stacks)
{
    struct point points[100][100];
    int i,j;
    double h,r;
    //generate points
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
    //draw quads using generated points
    for(i=0; i<stacks; i++)
        {
            glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
            for(j=0; j<slices; j++)
                {
                    glBegin(GL_QUADS);
                    {
                        //upper hemisphere
                        glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                        glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                        glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                        glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                        //lower hemisphere
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
    //generate points
    for(i=0; i<=segments; i++)
        {
            points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
            points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
        }
    //draw quads using generated points
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


void train1()
{

    //glScalef(1,1,1.5);
    glPushMatrix();
    {
      glTranslatef(0,0,0);
      glScalef(0.6,0.6,0.6);

      glPushMatrix();
      {

        //Line
  glColor3f(0.3,0.3,0.3);
  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(0,0,22);
      glScalef(20,0.1,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(0,0,10);
      glScalef(19.5,0.1,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

   glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(0,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(15,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(30,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(45,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(60,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(75,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(90,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(105,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(120,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(135,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(150,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(165,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(180,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(195,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(210,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(225,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(240,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(255,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(270,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(285,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-15,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-30,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-45,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-60,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-75,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-90,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-105,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-120,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-135,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-150,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-165,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-180,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-195,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-210,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-225,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-240,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-255,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-270,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-285,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();





//Body1
glPushMatrix();
{

    glTranslatef(tx,0,0);
    glPushMatrix();
    {
        glColor3f(0,0,1);
        glTranslatef(0,30,0);
        glScalef(2.5,0.8,0.5);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0,0,1);
        glTranslatef(0,90,0);
        glScalef(2.5,0.8,0.5);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0,0,1);
        glRotatef(90,0,0,1);
        glTranslatef(60,42,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0,0,1);
        glRotatef(90,0,0,1);
        glTranslatef(60,-2,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0,0,1);
        glRotatef(90,0,0,1);
        glTranslatef(60,-42,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0,1,0);
        glTranslatef(120,15,0);
        glScalef(65,1,0.5);
        drawCube(2.5);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,1,0);
        glRotatef(90,0,0,1);
        glTranslatef(100,20,0);
        glScalef(2.5,0.5,0.09);
        drawCube(10);
    }glPopMatrix();

//Wheel
    glColor3f(1,1,1);
    glPushMatrix();
    {

        glTranslatef(25,0,15);
        glRotatef(angle,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();


    glPushMatrix();
    {

        glTranslatef(25,0,-15);
        glRotatef(angle,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();


    glPushMatrix();
    {

        glTranslatef(-25,0,15);
        glRotatef(angle,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();

    glPushMatrix();
    {

        glTranslatef(-25,0,-15);
        glRotatef(angle,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();

}glPopMatrix();


//Body2
glPushMatrix();
{

    glTranslatef(tx,0,0);
    glPushMatrix();
    {
        glColor3f(0,0,1);
        glTranslatef(120,30,0);
        glScalef(2.5,0.8,0.5);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0,0,1);
        glTranslatef(120,90,0);
        glScalef(2.5,0.8,0.5);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0,0,1);
        glRotatef(90,0,0,1);
        glTranslatef(60,-78,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0,0,1);
        glRotatef(90,0,0,1);
        glTranslatef(60,-120,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0,0,1);
        glRotatef(90,0,0,1);
        glTranslatef(60,-162,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

//Wheel
    glColor3f(1,1,1);
    glPushMatrix();
    {

        glTranslatef(95,0,15);
        glRotatef(angle,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();


    glPushMatrix();
    {

        glTranslatef(95,0,-15);
        glRotatef(angle,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();


    glPushMatrix();
    {

        glTranslatef(150,0,15);
        glRotatef(angle,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();

    glPushMatrix();
    {

        glTranslatef(150,0,-15);
        glRotatef(angle,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();

}glPopMatrix();

//Body3
glPushMatrix();
{

    glTranslatef(tx,0,0);
    glPushMatrix();
    {
        glColor3f(0,0,1);
        glTranslatef(240,30,0);
        glScalef(2.5,0.8,0.5);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0,0,1);
        glTranslatef(240,90,0);
        glScalef(2.5,0.8,0.5);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0,0,1);
        glRotatef(90,0,0,1);
        glTranslatef(60,-198,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0,0,1);
        glRotatef(90,0,0,1);
        glTranslatef(60,-240,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0,0,1);
        glRotatef(90,0,0,1);
        glTranslatef(60,-282,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

//Wheel
    glColor3f(1,1,1);
    glPushMatrix();
    {

        glTranslatef(220,0,15);
        glRotatef(angle,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();


    glPushMatrix();
    {

        glTranslatef(220,0,-15);
        glRotatef(angle,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();


    glPushMatrix();
    {

        glTranslatef(270,0,15);
        glRotatef(angle,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();

    glPushMatrix();
    {

        glTranslatef(270,0,-15);
        glRotatef(angle,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();

}glPopMatrix();

      }glPopMatrix();

    }glPopMatrix();


}

void train2()
{
    //glScalef(1,1,1.5);

glPushMatrix();
{
     glTranslatef(0,-120,0);
     glScalef(0.8,0.8,0.8);

     glPushMatrix();
     {

    //Line
  glColor3f(0.3,0.3,0.3);
  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(0,12,-8);
      glScalef(20,0.1,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(0,0,30);
      glScalef(19.5,0.1,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

   glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(0,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(15,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(30,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(45,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(60,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(75,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(90,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(105,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(120,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(135,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(150,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(165,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(180,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(195,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(210,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(225,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(240,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(255,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-15,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-30,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-45,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-60,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-75,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-90,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-105,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-120,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-135,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-150,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-165,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-180,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-195,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-210,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-225,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-240,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();

  glPushMatrix();
  {

      glRotatef(90,1,0,0);
      glTranslatef(-255,0,15);
      glScalef(0.08,1.5,0);
      drawSquare(40);
      //glColor3f(0,1,0);
  }glPopMatrix();





//Body1
glPushMatrix();
{

    glTranslatef(tx2,0,0);
    glPushMatrix();
    {
        glColor3f(1,0,0);
        glTranslatef(0,30,0);
        glScalef(2.5,0.8,0.5);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,0,0);
        glTranslatef(0,90,0);
        glScalef(2.5,0.8,0.5);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,0,0);
        glRotatef(90,0,0,1);
        glTranslatef(60,42,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,0,0);
        glRotatef(90,0,0,1);
        glTranslatef(60,-2,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,0,0);
        glRotatef(90,0,0,1);
        glTranslatef(60,-42,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0,1,0);
        glTranslatef(120,15,0);
        glScalef(65,1,0.5);
        drawCube(2.5);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,1,0);
        glRotatef(90,0,0,1);
        glTranslatef(100,-270,0);
        glScalef(2.5,0.5,0.09);
        drawCube(10);
    }glPopMatrix();

//Wheel
    glColor3f(1,1,1);
    glPushMatrix();
    {

        glTranslatef(25,0,15);
        glRotatef(angle2,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();


    glPushMatrix();
    {

        glTranslatef(25,0,-15);
        glRotatef(angle2,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();


    glPushMatrix();
    {

        glTranslatef(-25,0,15);
        glRotatef(angle2,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();

    glPushMatrix();
    {

        glTranslatef(-25,0,-15);
        glRotatef(angle2,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();

}glPopMatrix();


//Body2
glPushMatrix();
{

    glTranslatef(tx2,0,0);
    glPushMatrix();
    {
        glColor3f(1,0,0);
        glTranslatef(120,30,0);
        glScalef(2.5,0.8,0.5);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,0,0);
        glTranslatef(120,90,0);
        glScalef(2.5,0.8,0.5);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,0,0);
        glRotatef(90,0,0,1);
        glTranslatef(60,-78,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,0,0);
        glRotatef(90,0,0,1);
        glTranslatef(60,-120,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,0,0);
        glRotatef(90,0,0,1);
        glTranslatef(60,-162,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

//Wheel
    glColor3f(1,1,1);
    glPushMatrix();
    {

        glTranslatef(95,0,15);
        glRotatef(angle2,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();


    glPushMatrix();
    {

        glTranslatef(95,0,-15);
        glRotatef(angle2,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();


    glPushMatrix();
    {

        glTranslatef(150,0,15);
        glRotatef(angle2,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();

    glPushMatrix();
    {

        glTranslatef(150,0,-15);
        glRotatef(angle2,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();

}glPopMatrix();

//Body3
glPushMatrix();
{

    glTranslatef(tx2,0,0);
    glPushMatrix();
    {
        glColor3f(1,0,0);
        glTranslatef(240,30,0);
        glScalef(2.5,0.8,0.5);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,0,0);
        glTranslatef(240,90,0);
        glScalef(2.5,0.8,0.5);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,0,0);
        glRotatef(90,0,0,1);
        glTranslatef(60,-198,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,0,0);
        glRotatef(90,0,0,1);
        glTranslatef(60,-240,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,0,0);
        glRotatef(90,0,0,1);
        glTranslatef(60,-282,0);
        glScalef(2.5,0.8,1);
        drawCube(10);
    }glPopMatrix();

//Wheel
    glColor3f(1,1,1);
    glPushMatrix();
    {

        glTranslatef(220,0,15);
        glRotatef(angle2,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();


    glPushMatrix();
    {

        glTranslatef(220,0,-15);
        glRotatef(angle2,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();


    glPushMatrix();
    {

        glTranslatef(270,0,15);
        glRotatef(angle2,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();

    glPushMatrix();
    {

        glTranslatef(270,0,-15);
        glRotatef(angle2,0,0,1);
        drawCylinder(15,5,12);
    }glPopMatrix();

}glPopMatrix();

     }glPopMatrix();


}glPopMatrix();




}

void drawSS()
{
//Platform
    glPushMatrix();
    {
        glColor3f(0.3,0.1,0);
        glRotatef(90,1,0,0);
        glTranslatef(0,0,250);
        glScalef(40,40,0);
        drawSquare(40);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0.3,0.1,0);
        glRotatef(90,0,0,1);
        glTranslatef(0,-300,-520);
        glScalef(40,40,0);
        drawSquare(40);
    }glPopMatrix();




//Field
  glPushMatrix();
  {

      glColor3f(0.70,0.6,0);
      glRotatef(90,1,0,0);
      glTranslatef(0,-260,1);
      glScalef(250,13,100);
      drawSquare(40);

  }glPopMatrix();

//Human
  /*glPushMatrix();
  {


      glTranslatef(0,60,-58);
      //glScalef(250,13,100);
      drawSphere(10,24,20);
      glColor3f(0.3,0.3,0.3);
      glTranslatef(0,-41,-7);
      glScalef(0.5,1.1,0);
      drawSquare(40);
      glTranslatef(0,30,-9);
      glScalef(0.4,0.5,0);
      drawSquare(40);
      glRotatef(90,0,0,1);
      glTranslatef(-25,-5,0);
      glScalef(0.3,6,0);
      drawSquare(40);


      glRotatef(90,1,0,0);
      //glTranslatef(0,30,-7);
      glScalef(3,3.5,0);

      drawSquare(40);

  }glPopMatrix();*/


//Shade
     glPushMatrix();
  {

      glColor3f(0,0,0.2);
      glRotatef(90,1,0,0);
      glTranslatef(90,50,-95);
      glScalef(8,4,0);
      drawSquare(40);

  }glPopMatrix();

     glColor3f(0,0,0);
    glPushMatrix();
    {

        glTranslatef(300,30,-95);
        glRotatef(90,1,0,0);
        drawCylinder(5,120,30);
    }glPopMatrix();

     glColor3f(0,0,0);
    glPushMatrix();
    {

        glTranslatef(-80,30,-95);
        glRotatef(90,1,0,0);
        drawCylinder(5,120,30);
    }glPopMatrix();



//Line Boarder 1
   glPushMatrix();
  {

      glColor3f(0.2,0.2,0.2);
      glRotatef(90,0,0,1);
      glTranslatef(-25,5,-5);
      glScalef(0.1,50,1);
      drawSquare(40);

  }glPopMatrix();

     glPushMatrix();
  {

      glColor3f(0.2,0.2,0.2);
      glRotatef(90,0,0,1);
      glTranslatef(0.1,40,-10);
      glScalef(0.1,50,1);
      drawSquare(40);

  }glPopMatrix();

//Line Boarder 2
  glPushMatrix();
  {

      glColor3f(0.2,0.2,0.2);
      glRotatef(90,0,0,1);
      glTranslatef(-120,5,-20);
      glScalef(0.2,50,1);
      drawSquare(40);

  }glPopMatrix();

     glPushMatrix();
  {

      glColor3f(0.2,0.2,0.2);
      glRotatef(90,0,0,1);
      glTranslatef(2,40,125);
      glScalef(0.1,50,1);
      drawSquare(40);

  }glPopMatrix();
    train1();
    train2();


}

void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
        {

        case '1':
            drawgrid=1-drawgrid;
            break;


        case 'f':
            posx=posx+lx;
            posy=posy+ly;
            posz=posz+lz;
            break;

        case 'b':
            posx=posx-lx;
            posy=posy-ly;
            posz=posz-lz;
            break;


        case 'u':
            posx=posx+rx;
            posy=posy+ry;
            posz=posz+rz;
            break;

        case 'd':
            posx=posx-rx;
            posy=posy-ry;
            posz=posz-rz;
            break;

        case 'm':
            posx=posx+ux;
            posy=posy+uy;
            posz=posz+uz;
            break;

        case 'n':
            posx=posx-ux;
            posy=posy-uy;
            posz=posz-uz;
            break;

        default:
            break;
        }
}


void specialKeyListener(int key, int x,int y)
{
    switch(key)
        {
        case GLUT_KEY_DOWN:		//down arrow key
            cameraHeight -= 3.0;
            break;
        case GLUT_KEY_UP:		// up arrow key
            cameraHeight += 3.0;
            break;

        case GLUT_KEY_RIGHT:
            cameraAngle += 0.03;
            break;
        case GLUT_KEY_LEFT:
            cameraAngle -= 0.03;
            break;

        case GLUT_KEY_PAGE_UP:
            break;
        case GLUT_KEY_PAGE_DOWN:
            break;

        case GLUT_KEY_INSERT:
            break;

        case GLUT_KEY_HOME:
            break;
        case GLUT_KEY_END:
            break;

        default:
            break;
        }
}


void mouseListener(int button, int state, int x, int y) 	//x, y is the x-y of the screen (2D)
{
    switch(button)
        {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN) 		// 2 times?? in ONE click? -- solution is checking DOWN or UP
                {
                    drawaxes=1-drawaxes;
                }
            break;

        case GLUT_RIGHT_BUTTON:
            //........
            break;

        case GLUT_MIDDLE_BUTTON:
            //........
            break;

        default:
            break;
        }
}



void display()
{

    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);	//color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /********************
    / set-up camera here
    ********************/
    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();

    //now give three info
    //1. where is the camera (viewer)?
    //2. where is the camera looking?
    //3. Which direction is the camera's UP direction?

    //gluLookAt(100,100,100,	0,0,0,	0,0,1);
    //gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
    gluLookAt(-50,100,200,	posx+lx,posy+ly,posz+lz,	0,1,0);

    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);


    /****************************
    / Add your objects from here
    ****************************/
    //add objects

    //drawAxes();
    //drawGrid();


    //glColor3f(1,0,0);
    //drawSquare(10);

    drawSS();

    //drawCircle(30,24);

    //drawCone(20,50,24);

    //drawSphere(30,24,20);




    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}


void animate()
{
    angle = angle+0.6;
    angle2 = angle2-0.6;
    dx= ((2*pi*r)/360)*0.6;
    tx = tx-dx;
    tx2 = tx2+dx;

    if(tx<-170)
    {
        tx=200;
    }

    if(tx2>170)
    {
        tx2=-200;
    }

    //codes for any changes in Models, Camera
    glutPostRedisplay();
}

void init()
{
    //codes for initialization
    drawgrid=1;
    drawaxes=1;
    cameraHeight=150.0;
    cameraAngle=1.0;
    angle=0;
    tx=0;
    r=10;
    //clear the screen
    glClearColor(0,0,0,0);

    /************************
    / set-up projection here
    ************************/
    //load the PROJECTION matrix
    glMatrixMode(GL_PROJECTION);

    //initialize the matrix
    glLoadIdentity();

    //give PERSPECTIVE parameters
    gluPerspective(80,	1,	1,	1000.0);
    //field of view in the Y (vertically)
    //aspect ratio that determines the field of view in the X direction (horizontally)
    //near distance
    //far distance
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

    glutCreateWindow("My OpenGL Program");

    init();

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing

    glutDisplayFunc(display);	//display callback function
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    glutMainLoop();		//The main loop of OpenGL

    return 0;
}
