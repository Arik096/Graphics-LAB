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

				//lines parallel to X-axis//ID:1103104
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,2);
		glVertex3f( a,-a,2);
		glVertex3f(-a,-a,2);
		glVertex3f(-a, a,2);
	}glEnd();
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
}


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
//ID:1103104draw quads using generated points
for(i=0;i<segments;i++)
{
glBegin(GL_QUADS);
{
glVertex3f(points[i].x,points[i].y,height/2);
glVertex3f(points[i+1].x,points[i+1].y,height/2);
glVertex3f(points[i].x,points[i].y,-height/2);
glVertex3f(points[i+1].x,points[i+1].y,-
height/2);
}
glEnd();
}
}


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

float Wx=-150;
float Wx2=-100;
void drawSS()
{


 glPushMatrix();
    {glTranslatef(0,1.2,50);
      glScaled(25,1,4);
      glRotated(90,1,0,0);
    glColor3f(0.5,0.5,0.5);
    drawSquare(10);
    }
    glPopMatrix();
    glPushMatrix();
    {
glTranslatef(Wx,9,50);
 glColor3f(1,0,0);
drawCylinder(8,5,35);
        }
    glPopMatrix();

    glPushMatrix();
    {
glTranslatef(Wx,9,80);
 glColor3f(1,0,0);
drawCylinder(8,5,35);
        }
    glPopMatrix();

glPushMatrix();
    {
      glTranslatef(Wx2,9,50);
 glColor3f(1,0,0);
drawCylinder(8,5,35);
        }
    glPopMatrix();

    glPushMatrix();
    {
glTranslatef(Wx2,9,80);
 glColor3f(1,0,0);
drawCylinder(8,5,35);
        }
    glPopMatrix();
   glPushMatrix();
{
    glTranslated(Wx,0,10);
    glPushMatrix();
    {
glPushMatrix();
    {glTranslatef(20,32,50);
   glScaled(5,2,2);
   glColor3f(1,1,1);
    drawCube(10);
     }
    glPopMatrix();
glPushMatrix();
    {
glTranslatef(-10,35,69);
glColor3f(0,1,1);
drawSquare(10);
     }
    glPopMatrix();
glPushMatrix();
    {
glTranslatef(20,35,69);
glColor3f(0,1,1);
drawSquare(10);
     }
    glPopMatrix();
glPushMatrix();
    {
glTranslatef(50,35,69);
glColor3f(0,1,1);
drawSquare(10);
     }
    glPopMatrix();
   glPushMatrix();
    {
    glTranslatef(64.1,38,52);
     glRotated(90,0,1,0);
     glScaled(1,1,3);
     glColor3f(0,1,1);
     drawSquare(14);
     }
    glPopMatrix();
    glPushMatrix();
    {

     glTranslatef(68.1,19,63);
     glRotated(90,0,1,0);

     glColor3f(1,1,0);
     drawSquare(3);
     }
    glPopMatrix();

      glPushMatrix();
       {
         glTranslatef(68.1,19,37);
         glRotated(90,0,1,0);
         glColor3f(1,1,0);
         drawSquare(3);
     }
    glPopMatrix();
    glPushMatrix();
       {
         glTranslatef(-33,19,50);
         glScaled(1,1,2);
         glRotated(90,0,1,0);
         glColor3f(1,0,1);
         drawSquare(3);
     }
    glPopMatrix();
    glPushMatrix();
       {
         glTranslatef(-32.5,35,50);
         glScaled(1,1,2);
         glRotated(90,0,1,0);
         glColor3f(0,1,1);
         drawSquare(6);}
    glPopMatrix();
glPushMatrix();
     {glTranslatef(50,25,68);
        glColor3f(0,1,1);
        glRotated(270,1,0,0);
        drawCone(5,15,67);
     }
    glPopMatrix();

    glPushMatrix();
     {glTranslatef(50,32,70);
      glColor3f(0,0,0);
      drawSphere(3,40,80);
      }
    glPopMatrix();
    glPushMatrix();
    {glTranslatef(25,25,68);
       glColor3f(0,1,1);
       glRotated(270,1,0,0);
       drawCone(5,15,67);
     }
    glPopMatrix();

    glPushMatrix();
    {
glTranslatef(25,32,70);
glColor3f(0,0,0);
  drawSphere(3,40,80);
     }
    glPopMatrix();
glPushMatrix();
    {
glTranslatef(15,25,68);
glColor3f(0,1,1);
glRotated(270,1,0,0);
  drawCone(5,15,67);
     }
    glPopMatrix();

    glPushMatrix();
    {
glTranslatef(15,32,70);
glColor3f(0,0,0);
  drawSphere(3,40,80);
     }
    glPopMatrix();
   glPushMatrix();
    {
glTranslatef(-5,25,68);
glColor3f(0,1,1);
glRotated(270,1,0,0);
  drawCone(5,15,67);
     }
    glPopMatrix();
  glPushMatrix();
    {
glTranslatef(-5,32,70);
glColor3f(0,0,0);
  drawSphere(3,40,80);
     }
    glPopMatrix();
    glPushMatrix();
    {
glTranslatef(-10,25,68);
glColor3f(0,1,1);
glRotated(270,1,0,0);
  drawCone(5,15,67);
     }
    glPopMatrix();

    glPushMatrix();
    {
glTranslatef(-10,32,70);
glColor3f(0,0,0);
  drawSphere(3,40,80);
     }
    glPopMatrix();

        glPushMatrix();
    {
glTranslatef(-15,25,68);
glColor3f(0,1,1);
glRotated(270,1,0,0);
  drawCone(5,15,67);
     }
    glPopMatrix();

    glPushMatrix();
    {
glTranslatef(-15,32,70);
  drawSphere(3,40,80);
     }
    glPopMatrix();
   glPushMatrix();
    {
     glTranslatef(0,50,50);
     drawSphere(8,40,80);
     }
    glPopMatrix();

     glPushMatrix();
    {
     glTranslatef(16,50,50);
     drawSphere(8,40,80);
     }
    glPopMatrix();

     glPushMatrix();
    {
     glTranslatef(32,50,50);
     drawSphere(8,40,80);
     }
    glPopMatrix();
      }
    glPopMatrix();

     }
    glPopMatrix();
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
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? --ID:1103104 solution is checking DOWN or UP
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
	gluLookAt(100,100,200,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	//drawGrid();

    glColor3f(1,0,1);
   //drawSquare(5);

    drawSS();

//drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	angle+=0.05;
	Wx+=0.5;
	Wx2+=0.5;
	//if(Mx==-150)
    //{
       // Mx+=0.1;
    //}

	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
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
