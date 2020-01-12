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



void drawSquare(double a)
{

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
//draws a cylinder of given radius and height is used as wheel
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


double speed= 0;
//double m= 0;
//double n=0;

void car()
{
    glScalef(2,1,1);
    glTranslatef(speed,50,0);
    glScalef(3,1,1);
    glColor3f(1,0,0);

    drawCube(16);

     glPushMatrix();
   {
        glTranslatef(-7.3,25,0);
        glScalef(1.7,2,4);
        glColor3f(1,1,0);
        drawCube(5);}
        glPopMatrix();

        glPushMatrix();
   {
        glTranslatef(-7.3,40,0);
        glScalef(2,4,4);
        glColor3f(0,0,1);
        drawCube(4);}
        glPopMatrix();



        glPushMatrix();
         {

        glScalef(1,2,2);
        glColor3f(1,1,1);
        glTranslatef(16,9,5);
        drawCube(1);}
        glPopMatrix();

        glPushMatrix();
         {

        glScalef(1,2,2);
        glColor3f(1,1,1);
        glTranslatef(16,9,-5);
        drawCube(1);}
        glPopMatrix();

}

void wheel()
{
    //this operation works on backside wheel
   glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(-15,-8,5);
    glRotatef(2*angle,0,0,-1); //rotation of wheel
    drawCylinder(5,90,25);

   }
   glPopMatrix();
   //this operation works on forward  wheel

   glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(15,-8,5);
    glRotatef(2*angle,0,0,-1);
    drawCylinder(5,90,25);
   }
   glPopMatrix();

}
void road()
{

    glTranslatef(0,-15,0);//road position perfection
    glRotatef(90,1,0,0);
    glScalef(50,3,1); //road length
    glColor3f(1,0,1);
    drawSquare(20);

}


void display(){
	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,1,1,1);	// remove black
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

	gluLookAt(0,100,200,	0,0,0,	0,1,0);

    //again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);

	/****************************
	/ Add your objects from here
	****************************/
    drawAxes();
    car();
    wheel();
    road();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}
void animate(){

   speed+=((2*pi*5)/360)*0.14;
    if(speed>180)
    {
         speed=-180;
    }
    angle+=0.07;
    //codes for any changes in Models, Camera
	glutPostRedisplay();
}
void init(){
	//codes for initialization

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
	glutInitWindowSize(650, 650);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
