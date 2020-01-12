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
double m= 0;

void LeftOuterMostFrame()
{

    glPushMatrix();
   {
       glRotatef(20,0,1,0);
        /////////////////////////// left most frame Box///////////////////////////////////
        glPushMatrix();
       {
        glTranslatef(-85,55,0);
        glScalef(7,1,1);
        glColor3f(1,1,1);
        drawCube(2);    //upper side
        }
       glPopMatrix();

       glPushMatrix();
       {
        glTranslatef(-85,5,0);
        glScalef(7,1,1);
        glColor3f(1,1,1);
        drawCube(2);    //lower side
        }
       glPopMatrix();

       glPushMatrix();
       {
        glTranslatef(-97,30,0);
        glScalef(1,13,1);
        glColor3f(1,1,1);
        drawCube(2);  // left side
        }
       glPopMatrix();

         glPushMatrix();
       {
        glTranslatef(-72,30,0);
        glScalef(1,13,1);
        glColor3f(1,1,1);
        drawCube(2);    //right side
        }
       glPopMatrix();


       //////////////////////////////////// //cylinder rod/////////////////////////
        ///////////////////////////////////////////////////////////////////////////
        glPushMatrix();
       {
        glColor3f(.5,0,0);
        glTranslatef(-90,30,0);
        glRotatef(90,1,0,0);
        glScalef(1,5,1);
        drawCylinder(.5,50,3);  //left side rod
       }
       glPopMatrix();

       glPushMatrix();
       {
         glColor3f(.5,0,0);
        glTranslatef(-85,30,0);
        glRotatef(90,1,0,0);
        glScalef(1,5,1);
        drawCylinder(.5,50,3);   //middle rod
       }
       glPopMatrix();

       glPushMatrix();
       {
         glColor3f(.5,0,0);
        glTranslatef(-80,30,0);
        glRotatef(90,1,0,0);
        glScalef(1,5,1);
        drawCylinder(.5,50,3);   //right side rod
       }
       glPopMatrix();
   }
   glPopMatrix();

}
void RightOuterMostFrame()
{
     glPushMatrix();
   {
    glRotatef(-20,0,1,0);
      ////////////////////////////////// Right most frame /////////////////////
    glPushMatrix();
   {
    glTranslatef(85,55,0);
    glScalef(7,1,1);
    glColor3f(1,1,1);
    drawCube(2);    //upper side
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(85,5,0);
    glScalef(7,1,1);
    glColor3f(1,1,1);
    drawCube(2);    //lower side
    }
   glPopMatrix();

    glPushMatrix();
   {
    glTranslatef(97,30,0);
    glScalef(1,13,1);
    glColor3f(1,1,1);
    drawCube(2); //right side
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(72,30,0);
    glScalef(1,13,1);
    glColor3f(1,1,1);
    drawCube(2);    //left side
    }
   glPopMatrix();

   ////////////////////////////////// Cylinder Rod /////////////////////
    glPushMatrix();
   {
     glColor3f(.5,0,0);
    glTranslatef(90,30,0);
    glRotatef(90,1,0,0);
    glScalef(1,5,1);
    drawCylinder(.5,50,3);  //right side rod
   }
   glPopMatrix();

   glPushMatrix();
   {
     glColor3f(.5,0,0);
    glTranslatef(85,30,0);
    glRotatef(90,1,0,0);
    glScalef(1,5,1);
    drawCylinder(.5,50,3);  //middle side rod
   }
   glPopMatrix();

   glPushMatrix();
   {
     glColor3f(.5,0,0);
    glTranslatef(80,30,0);
    glRotatef(90,1,0,0);
    glScalef(1,5,1);
    drawCylinder(.5,50,3);      //left side rod
   }
   glPopMatrix();

   }
   glPopMatrix();

}
void LeftInnerMostFrame()
{
    glPushMatrix();
   {
    glRotatef(15,0,1,0);
     ////////////////////////////////Left Inner Most Frame /////////////////////////////
   glPushMatrix();
   {
    glTranslatef(-45,65,0);
    glScalef(7,1,1);
    glColor3f(1,1,1);
    drawCube(2);     //upper side
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(-45,5,0);
    glScalef(7,1,1);
    glColor3f(1,1,1);
    drawCube(2);    //lower side
    }
   glPopMatrix();

    glPushMatrix();
   {
    glTranslatef(-57,35,0);
    glScalef(1,15,1);
    glColor3f(1,1,1);
    drawCube(2);    //left side
    }
   glPopMatrix();

    glPushMatrix();
   {
    glTranslatef(-32,35,0);
    glScalef(1,15,1);
    glColor3f(1,1,1);
    drawCube(2);    //right side
    }
   glPopMatrix();

    /////////////////////////////// Cylinder Rod ////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////

    glPushMatrix();
   {
     glColor3f(.5,0,0);
    glTranslatef(-50,35,0);
    glRotatef(90,1,0,0);
    glScalef(1,5,1);
    drawCylinder(.5,57,3);  //left side rod
   }
   glPopMatrix();

   glPushMatrix();
   {
     glColor3f(.5,0,0);
    glTranslatef(-45,35,0);
    glRotatef(90,1,0,0);
    glScalef(1,5,1);
    drawCylinder(.5,57,3);  //middle rod
   }
   glPopMatrix();

    glPushMatrix();
   {
     glColor3f(.5,0,0);
    glTranslatef(-40,35,0);
    glRotatef(90,1,0,0);
    glScalef(1,5,1);
    drawCylinder(.5,57,3);  //right side rod
   }
   glPopMatrix();

     }
   glPopMatrix();

}

void RightInnerMostFrame()
{
    glPushMatrix();
   {
    glRotatef(-15,0,1,0);

 /////////////////////////////////////Right Inner MostFrame //////////////////////////
   glPushMatrix();
   {
    glTranslatef(45,65,0);
    glScalef(7,1,1);
    glColor3f(1,1,1);
    drawCube(2);    //upper side
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(45,5,0);
    glScalef(7,1,1);
    glColor3f(1,1,1);
    drawCube(2);    //lower side
    }
   glPopMatrix();

    glPushMatrix();
   {
    glTranslatef(57,35,0);
    glScalef(1,15,1);
    glColor3f(1,1,1);
    drawCube(2);    //right side
    }
   glPopMatrix();

    glPushMatrix();
   {
    glTranslatef(32,35,0);
    glScalef(1,15,1);
    glColor3f(1,1,1);
    drawCube(2);    //left side
    }
   glPopMatrix();

    /////////////////////////////// Cylinder Rod ////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////

    glPushMatrix();
   {
     glColor3f(.5,0,0);
    glTranslatef(50,35,0);
    glRotatef(90,1,0,0);
    glScalef(1,5,1);
    drawCylinder(.5,57,3);  //right side rod
   }
   glPopMatrix();

   glPushMatrix();
   {
     glColor3f(.5,0,0);
    glTranslatef(45,35,0);
    glRotatef(90,1,0,0);
    glScalef(1,5,1);
    drawCylinder(.5,57,3);  //middle side rod
   }
   glPopMatrix();

    glPushMatrix();
   {
     glColor3f(.5,0,0);
    glTranslatef(40,35,0);
    glRotatef(90,1,0,0);
    glScalef(1,5,1);
    drawCylinder(.5,57,3);  //left side rod
   }
   glPopMatrix();

     }
   glPopMatrix();
}

void CenteredFrame()
{


   ///////////////////////////////////////Centered Frame ////////////////////////////////////
   glPushMatrix();
   {
    glTranslatef(0,90,28);
    glScalef(8,1,1);
    glColor3f(1,1,1);
    drawCube(2.5);  //upper side
    }
   glPopMatrix();

    glPushMatrix();
   {
    glTranslatef(0,5,0);
    glScalef(8,1,1);
    glColor3f(1,1,1);
    drawCube(2.5);  //lower side
    }
   glPopMatrix();

     glPushMatrix();
   {
    glTranslatef(-20,40,0);
    glScalef(1,18,1);
    glColor3f(1,1,1);
    drawCube(2); //left side
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(20,40,0);
    glScalef(1,18,1);
    glColor3f(1,1,1);
    drawCube(2);    //right side
    }
   glPopMatrix();

   glPushMatrix();
   {
    glTranslatef(0,40,0);
    glScalef(1,18,1);
    glColor3f(1,1,1);
    drawCube(2);    //middle
    }
   glPopMatrix();

   //////////////////////////////// cylinder Rod /////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////////////

   glPushMatrix();
   {
     glColor3f(.5,0,0);
    glTranslatef(-15,40,0);
    glRotatef(90,1,0,0);
    glScalef(1,5,1);
    drawCylinder(.5,70,3);
   }
   glPopMatrix();

   glPushMatrix();
   {
     glColor3f(.5,0,0);
    glTranslatef(-10,40,0);
    glRotatef(90,1,0,0);
    glScalef(1,5,1);
    drawCylinder(.5,70,3);
   }
   glPopMatrix();

   glPushMatrix();
   {
     glColor3f(.5,0,0);
    glTranslatef(-5,40,0);
    glRotatef(90,1,0,0);
    glScalef(1,5,1);
    drawCylinder(.5,70,3);
   }
   glPopMatrix();

   glPushMatrix();
   {
     glColor3f(.5,0,0);
    glTranslatef(15,40,0);
    glRotatef(90,1,0,0);
    glScalef(1,5,1);
    drawCylinder(.5,70,3);
   }
   glPopMatrix();

   glPushMatrix();
   {
     glColor3f(.5,0,0);
    glTranslatef(10,40,0);
    glRotatef(90,1,0,0);
    glScalef(1,5,1);
    drawCylinder(.5,70,3);
   }
   glPopMatrix();

   glPushMatrix();
   {
     glColor3f(.5,0,0);
    glTranslatef(5,40,0);
    glRotatef(90,1,0,0);
    glScalef(1,5,1);
    drawCylinder(.5,70,3);
   }
   glPopMatrix();
}

void upperturn()

{

        ////////////////////////////// majer ta ///////////////////
 glPushMatrix();
   {
    glTranslatef(0,82,15);
    glRotatef(60,1,0,0);
    glScalef(1,8,1);
    glColor3f(1,1,1);
    drawCube(2);    //middle
    }
   glPopMatrix();

   ////////////////////////////// ba paser ta ///////////////////

 glPushMatrix();
   {
    glTranslatef(-20,82,15);
    glRotatef(60,1,0,0);
    glScalef(1,8,1);
    glColor3f(1,1,1);
    drawCube(2);    //left side
    }
   glPopMatrix();

      ////////////////////////////// dan paser ta ///////////////////
 glPushMatrix();
   {
    glTranslatef(20,82,15);
    glRotatef(60,1,0,0);
    glScalef(1,8,1);
    glColor3f(1,1,1);
    drawCube(2);    //right side
    }
   glPopMatrix();

   //////////////////////////////////// upper turn er ROD //////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////////////////////////////
   glPushMatrix();
   {
   glTranslatef(-15,80,15);
    glRotatef(60,1,0,0);
     glColor3f(.5,0,0);
    glScalef(1,35,1);
    drawCube(.5);   //left most rod
    }
   glPopMatrix();

   glPushMatrix();
   {
   glTranslatef(-10,80,15);
    glRotatef(60,1,0,0);
     glColor3f(.5,0,0);
    glScalef(1,35,1);
    drawCube(.5);   //left middle rod
    }
   glPopMatrix();

   glPushMatrix();
   {
   glTranslatef(-5,80,15);
    glRotatef(60,1,0,0);
     glColor3f(.5,0,0);
    glScalef(1,35,1);
    drawCube(.5);   //left rod
    }
   glPopMatrix();

   glPushMatrix();
   {
   glTranslatef(5,80,15);
    glRotatef(60,1,0,0);
     glColor3f(.5,0,0);
    glScalef(1,35,1);
    drawCube(.5);   //right rod
    }
   glPopMatrix();

    glPushMatrix();
   {
   glTranslatef(10,80,15);
    glRotatef(60,1,0,0);
     glColor3f(.5,0,0);
    glScalef(1,35,1);
    drawCube(.5);   //right middle rod
    }
   glPopMatrix();

    glPushMatrix();
   {
   glTranslatef(15,80,15);
    glRotatef(60,1,0,0);
     glColor3f(.5,0,0);
    glScalef(1,35,1);
    drawCube(.5);   //right most rod

    }
   glPopMatrix();


}
void bedi()
{
    glTranslatef(0,0,25);
     glPushMatrix();
   {
             /////////////////////////////////  BEDI//////////////////////
            glPushMatrix();
           {
            glTranslatef(0,0,0);
            glScalef(70,1,30);
            glColor3f(1,0,0);
            drawCube(2);    //bedi
            }
           glPopMatrix();

           glPushMatrix();
           {
            glTranslatef(0,-5,0);
            glScalef(70,1,30);
            glColor3f(0.8,0,0);
            drawCube(2.1);    //bedi
            }
           glPopMatrix();

           glPushMatrix();
           {
            glTranslatef(0,-10,0);
            glScalef(70,1,30);
            glColor3f(.6,0,0);
            drawCube(2.2);    //bedi
            }
           glPopMatrix();

           glPushMatrix();
           {
            glTranslatef(0,-15,0);
            glScalef(70,1,30);
            glColor3f(0.4, 0, 0);
            drawCube(2.3);    //bedi
            }
           glPopMatrix();

           glPushMatrix();
           {
            glTranslatef(0,-20,0);
            glScalef(70,1,30);
            glColor3f(.4,0,0);
            drawCube(2.4);    //bedi
            }
           glPopMatrix();


            glPushMatrix();
           {
            glTranslatef(0,-25,0);
            glScalef(70,1,30);
            glColor3f(.2,0,0);
            drawCube(2.5);    //bedi
            }
           glPopMatrix();

   }
   glPopMatrix();

}
void Flag()
{
    glPushMatrix();
   {
    glTranslatef(-108,90,0);
    glColor3f(0,.5,0);
    glRotatef(90,0,0,1);
   drawSquare(12); // green flag
    }
   glPopMatrix();

    glPushMatrix();
   {
    glTranslatef(-120,50,0);
    glColor3f(0.4, 0.4, 0.4);
    glRotatef(90,1,0,0);
    glScalef(1,3,1);
   drawCylinder(.5,110,25); //flag stand
    }
   glPopMatrix();

      glPushMatrix();
   {
    glTranslatef(-120,5,0);
    glColor3f(0.8, 0.8, 0.8);
    drawCube(5); //flag stand box
    }
   glPopMatrix();

////////////////////////////////// Circle ////////////////////////////////

   glPushMatrix();
   {
    glTranslatef(-107,90,0);
    glColor3f(.8,0,0);
    glScalef(1,2,3);
                                //green circle
    drawCylinder(.1,1,50);
    drawCylinder(.2,1,50);
    drawCylinder(.3,1,50);
    drawCylinder(.4,1,50);
    drawCylinder(.5,1,50);
    drawCylinder(.6,1,50);
    drawCylinder(.7,1,50);
    drawCylinder(.8,1,50);
    drawCylinder(.9,1,50);

    drawCylinder(1,1,50);
    drawCylinder(1.1,1,50);
    drawCylinder(1.2,1,50);
    drawCylinder(1.3,1,50);
    drawCylinder(1.4,1,50);
    drawCylinder(1.5,1,50);
    drawCylinder(1.6,1,50);
    drawCylinder(1.7,1,50);
    drawCylinder(1.8,1,50);
    drawCylinder(1.9,1,50);

    drawCylinder(2,1,50);
    drawCylinder(2.1,1,50);
    drawCylinder(2.2,1,50);
    drawCylinder(2.3,1,50);
    drawCylinder(2.4,1,50);
    drawCylinder(2.5,1,50);
    drawCylinder(2.6,1,50);
    drawCylinder(2.7,1,50);
    drawCylinder(2.8,1,50);
    drawCylinder(2.9,1,50);

    drawCylinder(3,1,50);
    drawCylinder(3.1,1,50);
    drawCylinder(3.2,1,50);
    drawCylinder(3.3,1,50);
    drawCylinder(3.4,1,50);
    drawCylinder(3.5,1,50);
    drawCylinder(3.6,1,50);
    drawCylinder(3.7,1,50);
    drawCylinder(3.8,1,50);
    drawCylinder(3.9,1,50);

    drawCylinder(4,1,50);
    drawCylinder(4.1,1,50);
    drawCylinder(4.2,1,50);
    drawCylinder(4.3,1,50);
    drawCylinder(4.4,1,50);
    drawCylinder(4.5,1,50);
    drawCylinder(4.6,1,50);
    drawCylinder(4.7,1,50);
    drawCylinder(4.8,1,50);
    drawCylinder(4.9,1,50);
    drawCylinder(5,1,50);

    }
   glPopMatrix();

}

void sun()
{
    glPushMatrix();
   {
    glScalef(4,5,8);
    glTranslatef(0,10,-1);
    glColor3f(1,0,0);
                            //green circle
    drawCylinder(.1,1,50);
    drawCylinder(.2,1,50);
    drawCylinder(.3,1,50);
    drawCylinder(.4,1,50);
    drawCylinder(.5,1,50);
    drawCylinder(.6,1,50);
    drawCylinder(.7,1,50);
    drawCylinder(.8,1,50);
    drawCylinder(.9,1,50);

    drawCylinder(1,1,50);
    drawCylinder(1.1,1,50);
    drawCylinder(1.2,1,50);
    drawCylinder(1.3,1,50);
    drawCylinder(1.4,1,50);
    drawCylinder(1.5,1,50);
    drawCylinder(1.6,1,50);
    drawCylinder(1.7,1,50);
    drawCylinder(1.8,1,50);
    drawCylinder(1.9,1,50);

    drawCylinder(2,1,50);
    drawCylinder(2.1,1,50);
    drawCylinder(2.2,1,50);
    drawCylinder(2.3,1,50);
    drawCylinder(2.4,1,50);
    drawCylinder(2.5,1,50);
    drawCylinder(2.6,1,50);
    drawCylinder(2.7,1,50);
    drawCylinder(2.8,1,50);
    drawCylinder(2.9,1,50);

    drawCylinder(3,1,50);
    drawCylinder(3.1,1,50);
    drawCylinder(3.2,1,50);
    drawCylinder(3.3,1,50);
    drawCylinder(3.4,1,50);
    drawCylinder(3.5,1,50);
    drawCylinder(3.6,1,50);
    drawCylinder(3.7,1,50);
    drawCylinder(3.8,1,50);
    drawCylinder(3.9,1,50);

    drawCylinder(4,1,50);
    drawCylinder(4.1,1,50);
    drawCylinder(4.2,1,50);
    drawCylinder(4.3,1,50);
    drawCylinder(4.4,1,50);
    drawCylinder(4.5,1,50);
    drawCylinder(4.6,1,50);
    drawCylinder(4.7,1,50);
    drawCylinder(4.8,1,50);
    drawCylinder(4.9,1,50);
    drawCylinder(5,1,50);



    }
   glPopMatrix();

}
void drawSS()
{


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
	gluLookAt(50,150,250,	1,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();
    glColor3f(1,0,0);

    LeftOuterMostFrame();
    LeftInnerMostFrame();

    CenteredFrame();
    upperturn();

    RightInnerMostFrame();
    RightOuterMostFrame();
    sun();

    bedi();
    Flag();

    //drawSS();
    //drawSquare(10);
   // glTranslatef(0,55,0);
   // drawCircle(15,25);
    //drawCone(20,50,24);

	//drawSphere(30,24,20);
	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}
void animate(){
/*
    m+=((2*pi*10)/360)*.1;
    if(m>100)
    {
        m=-100;
    }
    angle+=0.05;
    //angle+=0.01;
    //codes for any changes in Models, Camera
	glutPostRedisplay();
	*/
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
	glutInitWindowSize(1000, 1000);
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
