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
struct point
{
	double x,y,z;
};
void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}

void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
				//lines parallal to z axis

				//glVertex3f( 0, 90, i*10);
				//glVertex3f(0, -90, i*10);


			}
		}glEnd();
	}
}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,0);
		glVertex3f( a,-a,0);
		glVertex3f(-a,-a,0);
		glVertex3f(-a, a,0);
	}glEnd();
}

//draws a cube of side length 2a
void drawCube(double a)
{
    glBegin(GL_QUADS);{


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
	}glEnd();
}
//draws a cylinder of given radius and height
void drawCylinder(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw quads using generated points
    for(i=0;i<segments;i++)
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
void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
     //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_QUADS);
        {
			glVertex3f(points[i].x,points[i].y,90);
			glVertex3f(points[i+1].x,points[i+1].y,90);
			glVertex3f(points[i].x,points[i].y,-90);
			glVertex3f(points[i+1].x,points[i+1].y,-90);
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
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0;i<segments;i++)
    {
        //create shading effect
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);
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
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
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
			}glEnd();
		}
	}
}
double tx= 0;
double ty= 0;
double tz= 0;
void drawBuilding1()
{
      glPushMatrix();
   {
     glTranslatef(-100,0,-100);
     ////////////////////////////// underground //////////////////////////////

    glPushMatrix();
   {
    glTranslatef(0,-15,0);
    glScalef(1,.1,1);
    glColor3f(1,0,1);
    drawCube(35);
    }
   glPopMatrix();
   ///////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////  One Story ////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(0,15,0);
    glScalef(1,.1,1);
    glColor3f(1,0,1);
    drawCube(31);
    }
   glPopMatrix();
   //////////////////////////////////////
    glPushMatrix();
   {
    glColor3f(1,0,0);
    glScalef(1,.5,1);
    drawCube(30);
    }
   glPopMatrix();
   ////////////////////////////////window//////////////

     glPushMatrix();
   {
    glTranslatef(-19,0,31);
    glColor3f(1,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   /////////////////////////////////////////////////////////////
     glPushMatrix();
   {
    glTranslatef(0,0,31);
    glColor3f(1,1,0);
    drawSquare(5);
    }
   glPopMatrix();
//////////////////////////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(19,0,31);
    glColor3f(1,1,0);
    drawSquare(5);
    }
   glPopMatrix();


   /////////////////////////////////////////////////////////////////////////////////////
   glPushMatrix();
   {
    glTranslatef(31,0,20);
    glColor3f(1,1,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,0,0);
    glColor3f(1,1,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,0,-20);
    glColor3f(1,1,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();
   ////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////// Two Story ///////////////////////////////////////

   glPushMatrix();
   {
    glTranslatef(0,45,0);
    glScalef(1,.1,1);
    glColor3f(1,0,0);
    drawCube(31);
    }
   glPopMatrix();
   ///////////////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(0,30,0);
    glScalef(1,.5,1);
    glColor3f(0,0,1);
    drawCube(30);
    }
   glPopMatrix();
    ////////////////////  ////////////////////////
     glPushMatrix();
   {
    glTranslatef(-19,30,31);
    glColor3f(0,1,1);
    drawSquare(5);
    }
   glPopMatrix();

    glPushMatrix();
   {
    glTranslatef(19,30,31);
    glColor3f(0,1,1);
    drawSquare(5);
    }
   glPopMatrix();

   /////////////////////////////////////////////////////////////
     glPushMatrix();
   {
    glTranslatef(0,30,31);
    glColor3f(0,1,1);
    drawSquare(5);
    }
   glPopMatrix();

   //////////////////////////////////////////////////////////////////////////////////////
   glPushMatrix();
   {
    glTranslatef(31,30,20);
    glColor3f(0,1,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,30,0);
    glColor3f(0,1,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,30,-20);
    glColor3f(0,1,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   ///////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////// Three story ////////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(0,75,0);
    glScalef(1,.1,1);
    glColor3f(1,0,0);
    drawCube(31);
    }
   glPopMatrix();
   //////////////////////////////
      glPushMatrix();
   {
    glTranslatef(0,60,0);
    glScalef(1,.5,1);
    glColor3f(0,1,0);
    drawCube(30);
    }
   glPopMatrix();
   //////////////////////////////////////////
     glPushMatrix();
   {
    glTranslatef(-19,60,31);
    glRotatef(90,0,0,1);
    glColor3f(1,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   /////////////////////////////////////////////////////////////
     glPushMatrix();
   {
    glTranslatef(0,60,31);
    glColor3f(1,1,0);
    drawSquare(5);
    }
   glPopMatrix();
//////////////////////////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(19,60,31);
    glColor3f(1,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   ////////////////////////////////////////////////////////////////////////////////////////////////
   glPushMatrix();
   {
    glTranslatef(31,60,20);
    glColor3f(1,1,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,60,0);
    glColor3f(1,1,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,60,-20);
    glColor3f(1,1,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();


   }
   glPopMatrix();

}

void drawBuilding2()
{
    glPushMatrix();
   {
    glTranslatef(-100,0,150);
     ////////////////////////////// underground //////////////////////////////

    glPushMatrix();
   {
    glTranslatef(0,-15,0);
    glScalef(1,.1,1);
    glColor3f(0,0,1);
    drawCube(35);
    }
   glPopMatrix();
   ///////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////  One Story ////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(0,15,0);
    glScalef(1,.1,1);
    glColor3f(1,0,0);
    drawCube(31);
    }
   glPopMatrix();
   //////////////////////////////////////
    glPushMatrix();
   {
    glColor3f(1,1,0);
    glScalef(1,.5,1);
    drawCube(30);
    }
   glPopMatrix();
   ////////////////////////////////window//////////////

     glPushMatrix();
   {
    glTranslatef(-19,0,31);
    glColor3f(1,0,0);
    drawSquare(5);
    }
   glPopMatrix();

   /////////////////////////////////////////////////////////////
     glPushMatrix();
   {
    glTranslatef(0,0,31);
    glColor3f(1,0,0);
    drawSquare(5);
    }
   glPopMatrix();
//////////////////////////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(19,0,31);
    glColor3f(1,0,0);
    drawSquare(5);
    }
   glPopMatrix();


   /////////////////////////////////////////////////////////////////////////////////////
   glPushMatrix();
   {
    glTranslatef(31,0,20);
    glColor3f(1,0,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,0,0);
    glColor3f(1,0,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,0,-20);
    glColor3f(1,0,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();
   ////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////// Two Story ///////////////////////////////////////

   glPushMatrix();
   {
    glTranslatef(0,45,0);
    glScalef(1,.1,1);
    glColor3f(1,0,0);
    drawCube(31);
    }
   glPopMatrix();
   ///////////////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(0,30,0);
    glScalef(1,.5,1);
    glColor3f(0,0,1);
    drawCube(30);
    }
   glPopMatrix();
    ////////////////////  ////////////////////////
     glPushMatrix();
   {
    glTranslatef(-19,30,31);
    glColor3f(0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

    glPushMatrix();
   {
    glTranslatef(19,30,31);
    glColor3f(0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   /////////////////////////////////////////////////////////////
     glPushMatrix();
   {
    glTranslatef(0,30,31);
    glColor3f(0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   //////////////////////////////////////////////////////////////////////////////////////
   glPushMatrix();
   {
    glTranslatef(31,30,20);
    glColor3f(0,1,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,30,0);
    glColor3f(0,1,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,30,-20);
    glColor3f(0,1,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   ///////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////// Three story ////////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(0,75,0);
    glScalef(1,.1,1);
    glColor3f(1,0,1);
    drawCube(31);
    }
   glPopMatrix();
   //////////////////////////////
      glPushMatrix();
   {
    glTranslatef(0,60,0);
    glScalef(1,.5,1);
    glColor3f(0,1,0);
    drawCube(30);
    }
   glPopMatrix();
   //////////////////////////////////////////
     glPushMatrix();
   {
    glTranslatef(-19,60,31);
    glRotatef(90,0,0,1);
    glColor3f(0,0,1);
    drawSquare(5);
    }
   glPopMatrix();

   /////////////////////////////////////////////////////////////
     glPushMatrix();
   {
    glTranslatef(0,60,31);
    glColor3f(0,0,1);
    drawSquare(5);
    }
   glPopMatrix();
//////////////////////////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(19,60,31);
    glColor3f(0,0,1);
    drawSquare(5);
    }
   glPopMatrix();

   ////////////////////////////////////////////////////////////////////////////////////////////////
   glPushMatrix();
   {
    glTranslatef(31,60,20);
    glColor3f(0,0,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,60,0);
    glColor3f(0,0,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,60,-20);
    glColor3f(0,0,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   }
   glPopMatrix();

}

void drawBuilding3()
{
     glPushMatrix();
   {
     glTranslatef(100,0,150);
     ////////////////////////////// underground //////////////////////////////

    glPushMatrix();
   {
    glTranslatef(0,-15,0);
    glScalef(1,.1,1);
    glColor3f(1,0,1);
    drawCube(35);
    }
   glPopMatrix();
   ///////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////  One Story ////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(0,15,0);
    glScalef(1,.1,1);
    glColor3f(1,0,0);
    drawCube(31);
    }
   glPopMatrix();
   //////////////////////////////////////
    glPushMatrix();
   {
    glColor3f(1,1,0);
    glScalef(1,.5,1);
    drawCube(30);
    }
   glPopMatrix();
   ////////////////////////////////window//////////////

     glPushMatrix();
   {
    glTranslatef(-19,0,31);
    glColor3f(1,0,0);
    drawSquare(5);
    }
   glPopMatrix();

   /////////////////////////////////////////////////////////////
     glPushMatrix();
   {
    glTranslatef(0,0,31);
    glColor3f(1,0,0);
    drawSquare(5);
    }
   glPopMatrix();
//////////////////////////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(19,0,31);
    glColor3f(1,0,0);
    drawSquare(5);
    }
   glPopMatrix();


   /////////////////////////////////////////////////////////////////////////////////////
   glPushMatrix();
   {
    glTranslatef(31,0,20);
    glColor3f(1,0,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,0,0);
    glColor3f(1,0,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,0,-20);
    glColor3f(1,0,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();
   ////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////// Two Story ///////////////////////////////////////

   glPushMatrix();
   {
    glTranslatef(0,45,0);
    glScalef(1,.1,1);
    glColor3f(1,0,0);
    drawCube(31);
    }
   glPopMatrix();
   ///////////////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(0,30,0);
    glScalef(1,.5,1);
    glColor3f(0,0,1);
    drawCube(30);
    }
   glPopMatrix();
    ////////////////////  ////////////////////////
     glPushMatrix();
   {
    glTranslatef(-19,30,31);
    glColor3f(0,1,1);
    drawSquare(5);
    }
   glPopMatrix();

    glPushMatrix();
   {
    glTranslatef(19,30,31);
    glColor3f(0,1,1);
    drawSquare(5);
    }
   glPopMatrix();

   /////////////////////////////////////////////////////////////
     glPushMatrix();
   {
    glTranslatef(0,30,31);
    glColor3f(0,1,1);
    drawSquare(5);
    }
   glPopMatrix();

   //////////////////////////////////////////////////////////////////////////////////////
   glPushMatrix();
   {
    glTranslatef(31,30,20);
    glColor3f(0,1,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,30,0);
    glColor3f(0,1,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,30,-20);
    glColor3f(0,1,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   ///////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////// Three story ////////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(0,75,0);
    glScalef(1,.1,1);
    glColor3f(1,1,0);
    drawCube(31);
    }
   glPopMatrix();
   //////////////////////////////
      glPushMatrix();
   {
    glTranslatef(0,60,0);
    glScalef(1,.5,1);
    glColor3f(1,0,1);
    drawCube(30);
    }
   glPopMatrix();
   //////////////////////////////////////////
     glPushMatrix();
   {
    glTranslatef(-19,60,31);
    glRotatef(90,0,0,1);
    glColor3f(1,0,0);
    drawSquare(5);
    }
   glPopMatrix();

   /////////////////////////////////////////////////////////////
     glPushMatrix();
   {
    glTranslatef(0,60,31);
    glColor3f(1,0,0);
    drawSquare(5);
    }
   glPopMatrix();
//////////////////////////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(19,60,31);
    glColor3f(1,0,0);
    drawSquare(5);
    }
   glPopMatrix();

   ////////////////////////////////////////////////////////////////////////////////////////////////
   glPushMatrix();
   {
    glTranslatef(31,60,20);
    glColor3f(1,0,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,60,0);
    glColor3f(1,0,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,60,-20);
    glColor3f(1,0,0);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   }
   glPopMatrix();

}
void drawBuilding4()
{
     glPushMatrix();
   {
     glTranslatef(100,0,-100);
     ////////////////////////////// underground //////////////////////////////

    glPushMatrix();
   {
    glTranslatef(0,-15,0);
    glScalef(1,.1,1);
    glColor3f(1,0,1);
    drawCube(35);
    }
   glPopMatrix();
   ///////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////  One Story ////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(0,15,0);
    glScalef(1,.1,1);
    glColor3f(1,0,0);
    drawCube(31);
    }
   glPopMatrix();
   //////////////////////////////////////
    glPushMatrix();
   {
    glColor3f(1,1,1);
    glScalef(1,.5,1);
    drawCube(30);
    }
   glPopMatrix();
   ////////////////////////////////window//////////////

     glPushMatrix();
   {
    glTranslatef(-19,0,31);
    glColor3f(1,0,1);
    drawSquare(5);
    }
   glPopMatrix();

   /////////////////////////////////////////////////////////////
     glPushMatrix();
   {
    glTranslatef(0,0,31);
    glColor3f(1,0,1);
    drawSquare(5);
    }
   glPopMatrix();
//////////////////////////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(19,0,31);
    glColor3f(1,0,1);
    drawSquare(5);
    }
   glPopMatrix();


   /////////////////////////////////////////////////////////////////////////////////////
   glPushMatrix();
   {
    glTranslatef(31,0,20);
    glColor3f(1,0,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,0,0);
    glColor3f(1,0,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,0,-20);
    glColor3f(1,0,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();
   ////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////// Two Story ///////////////////////////////////////

   glPushMatrix();
   {
    glTranslatef(0,45,0);
    glScalef(1,.1,1);
    glColor3f(1,0,0);
    drawCube(31);
    }
   glPopMatrix();
   ///////////////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(0,30,0);
    glScalef(1,.5,1);
    glColor3f(0,0,1);
    drawCube(30);
    }
   glPopMatrix();
    ////////////////////  ////////////////////////
     glPushMatrix();
   {
    glTranslatef(-19,30,31);
    glColor3f(0,1,1);
    drawSquare(5);
    }
   glPopMatrix();

    glPushMatrix();
   {
    glTranslatef(19,30,31);
    glColor3f(0,1,1);
    drawSquare(5);
    }
   glPopMatrix();

   /////////////////////////////////////////////////////////////
     glPushMatrix();
   {
    glTranslatef(0,30,31);
    glColor3f(0,1,1);
    drawSquare(5);
    }
   glPopMatrix();

   //////////////////////////////////////////////////////////////////////////////////////
   glPushMatrix();
   {
    glTranslatef(31,30,20);
    glColor3f(0,1,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,30,0);
    glColor3f(0,1,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,30,-20);
    glColor3f(0,1,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   ///////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////// Three story ////////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(0,75,0);
    glScalef(1,.1,1);
    glColor3f(1,1,0);
    drawCube(31);
    }
   glPopMatrix();
   //////////////////////////////
      glPushMatrix();
   {
    glTranslatef(0,60,0);
    glScalef(1,.5,1);
    glColor3f(0,1,0);
    drawCube(30);
    }
   glPopMatrix();
   //////////////////////////////////////////
     glPushMatrix();
   {
    glTranslatef(-19,60,31);
    glRotatef(90,0,0,1);
    glColor3f(1,0,1);
    drawSquare(5);
    }
   glPopMatrix();

   /////////////////////////////////////////////////////////////
     glPushMatrix();
   {
    glTranslatef(0,60,31);
    glColor3f(1,0,1);
    drawSquare(5);
    }
   glPopMatrix();
//////////////////////////////////////////////////////////////
    glPushMatrix();
   {
    glTranslatef(19,60,31);
    glColor3f(1,0,1);
    drawSquare(5);
    }
   glPopMatrix();

   ////////////////////////////////////////////////////////////////////////////////////////////////
   glPushMatrix();
   {
    glTranslatef(31,60,20);
    glColor3f(1,0,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,60,0);
    glColor3f(1,0,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(31,60,-20);
    glColor3f(1,0,1);
    glRotatef(90,0,1,0);
    drawSquare(5);
    }
   glPopMatrix();

   }
   glPopMatrix();


}

void drawRoad1()
{


    glPushMatrix();
   {
   //car
    glPushMatrix();
   {
   glTranslatef(tx,0,0);

    glScalef(2,.3,.5);
    glColor3f(1,1,0);
    glTranslatef(0,50,0);
    drawCube(20);
    }
   glPopMatrix();

    //wheel
   glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(tx,0,0);
   glTranslatef(-25,10,0);
    glRotatef(2*angle,0,0,-1);
    drawCylinder(10,15,20);
   }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(tx,0,0);
    glTranslatef(25,10,0);
    glRotatef(2*angle,0,0,-1);
   drawCylinder(10,15,20);
   }
   glPopMatrix();
    }
   glPopMatrix();




    //Road
    glPushMatrix();
   {
    glScalef(50,1,2);
    glColor3f(0,1,0);
    glRotatef(90,1,0,0);
    drawSquare(15);
   }
   glPopMatrix();



}

void drawRoad2()
{

    glPushMatrix();
   {
       //car
        glPushMatrix();
       {
       glTranslatef(0,0,ty);
        glScalef(.5,.3,2);
        glColor3f(1,1,0);
        glTranslatef(0,50,0);
       drawCube(20);
        }
       glPopMatrix();

        //wheel
       glPushMatrix();
       {
        glColor3f(0,0,0);
        glTranslatef(0,0,ty);
       glTranslatef(0,10,-25);
        glRotatef(2*angle,1,0,0);
        glRotatef(90,0,1,0);
        drawCylinder(10,15,20);
       }
       glPopMatrix();

       glPushMatrix();
       {
        glColor3f(0,0,0);
        glTranslatef(0,0,ty);
        glTranslatef(0,10,25);
        glRotatef(2*angle,1,0,0);
        glRotatef(90,0,1,0);
       drawCylinder(10,15,20);
       }
       glPopMatrix();

    }
   glPopMatrix();



    //Road
   glPushMatrix();
   {
    glScalef(2,1,50);
    glColor3f(0,1,0);
    glRotatef(90,1,0,0);
    drawSquare(15);
   }
   glPopMatrix();

}

void River()

{
    ////////////////////// River //////////////////////
     glPushMatrix();
           {
               glTranslatef(250,5,0);
            glScalef(7.5,.1,50);
            glColor3f(0,0,1);
            glRotatef(90,1,0,0);
            drawCube(10);
            drawSquare(10);
           }
           glPopMatrix();



        glPushMatrix();
           {
        glTranslatef(250,-10,0);



           glPushMatrix();
            {
                glTranslatef(0,50,0);
                ///////////////// Birdge
                    glPushMatrix();
                   {
                    glRotatef(25,0,0,1);
                    glTranslatef(-75,0,0);
                    glScalef(2,.5,2.5);
                    glColor3f(1,0,0);
                    drawCube(10);
                    }
                   glPopMatrix();

                   ///////////////// Birdge
                    glPushMatrix();
                   {
                    glRotatef(-25,0,0,1);
                    glTranslatef(75,0,0);
                    glScalef(2,.5,2.5);
                    glColor3f(1,0,0);
                    drawCube(10);
                    }
                   glPopMatrix();

                   ///////////////// Birdge
                   glPushMatrix();
                   {
                    glTranslatef(0,-22,0);
                    glScalef(5,.5,2.5);
                    glColor3f(1,0,0);
                    drawCube(10);
                    }
                   glPopMatrix();

               }
               glPopMatrix();

           }
           glPopMatrix();


}

void Boat()
{
  glPushMatrix();
    {
        glTranslatef(250,15,tz);
        glScalef(.5,.5,.5);

    glPushMatrix();
    {
    glColor3f(0,1,1);
    glScalef(1.5,1,1);
    glTranslatef(0,100,0);
    drawSquare(40);

    }glPopMatrix();

     glPushMatrix();
    {
    glColor3f(1,1,1);
    glRotatef(15,0,0,-1);
    glTranslatef(-48,50,0);
    glScalef(0.1,2.3,0.3);
    drawSquare(20);

    }glPopMatrix();

         glPushMatrix();
    {
    glColor3f(1,1,1);
    glRotatef(15,0,0,1);
    glTranslatef(48,50,0);
    glScalef(0.1,2.3,0.3);
    drawSquare(20);
    }glPopMatrix();

   glPushMatrix();
    {
    glColor3f(1,0,0);
    glScalef(2.3,-.7,2.3);
    drawCube(15);
    }glPopMatrix();


    glPushMatrix();
    {
    glColor3f(1,0,0);
    glRotatef(-10,0,0,.2);
    glTranslatef(-65,0,0);
    glScalef(1.7,-.6,.8);
    drawCube(15);
    }glPopMatrix();


    glPushMatrix();
    {
    glColor3f(1,0,0);
    glRotatef(10,0,0,.3);
    glTranslatef(65,0,0);
    glScalef(1.7,-.6,.8);
    drawCube(15);
    }glPopMatrix();

    glPushMatrix();
    {
    glColor3f(0,0,1);
    glRotatef(90,0,1,0);
    glScalef(.9,.7,.9);
    glTranslatef(0,39,0);
    drawCylinder(20,80,10);
    }glPopMatrix();

    }glPopMatrix();

}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			drawgrid=1-drawgrid;
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
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
void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
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
void display(){
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
	gluLookAt(100,300,400,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();

    drawBuilding1();
    drawBuilding2();
    drawBuilding3();
    drawBuilding4();
    drawRoad1();
    drawRoad2();
    River();
    Boat();

    //drawSquare(10);
    //drawSS();
    //drawCircle(30,24);
    //drawCone(20,50,24);
	//drawSphere(10,8,6);
	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}
void animate(){

    tx+=((2*pi*10)/360)*.5;
    if(tx>100)
    {
        tx=-200;
    }

    ty+=((2*pi*10)/360)*.5;
    if(ty>-25)
    {
        ty=-300;
    }
    angle+=0.5;


    tz+=.05;
    if(tz>-50)
    {
        tz=-300;
    }

    //codes for any changes in Models, Camera
	glutPostRedisplay();
}
void init(){
	//codes for initialization
	//drawgrid=1;
	drawaxes=1;
	cameraHeight=100.0;
	cameraAngle=1.0;
	angle=0;

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

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(800, 800);
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
