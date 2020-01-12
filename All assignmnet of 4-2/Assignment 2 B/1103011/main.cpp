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
double tx=0;
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
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
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


void drawpinball()
{
    glPushMatrix();
    {
        glColor3f(0,1,1);
        glTranslatef(0,-35,0);
        glScalef(8.2,11,1);
        drawSquare(20);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0,1,1);
        glTranslatef(0,168,0);
        glScalef(1.5,1,1);
        drawSphere(110,30,1);
    }glPopMatrix();

    glPushMatrix(); ///red button
    {
        glColor3f(1,0,0); //red
        glTranslatef(0,-210,0);
        drawSphere(40,30,1);
    }glPopMatrix();

    glPushMatrix(); ///ball holder
    {
        glColor3f(0.658824,0.658824,0.658824);
        glTranslatef(146,-208,-15);
        glScalef(.8,2.2,1);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix(); ///spring
    {
        glColor3f(0.329412,0.329412,0.329412);
        glTranslatef(145,-195,9);
        glRotatef(90,1,0,0);
        drawCylinder(7,40,10);
    }glPopMatrix();

    glPushMatrix(); ///ball
    {
        //glRotatef(tx,0,0,1);
        glColor3f(0,0,0);
        glTranslatef(150,-150,0);
        drawSphere(15,20,1);
    }glPopMatrix();

  /*  glPushMatrix();    ///right curve
    {
        glColor3f(0,0,0);
        glRotatef(85,1,1,0);
        glTranslatef(75,90,0);
        glScalef(.02,1,1);
        drawSphere(50,30,40);
    }glPopMatrix();

     glPushMatrix();  ///left curve
    {
        glColor3f(0,0,0);
        glRotatef(275,1,1,0);
        glTranslatef(85,90,0);
        glScalef(.02,1,1);
        drawSphere(50,30,40);
    }glPopMatrix(); */

    glPushMatrix();
    {
        glColor3f(1,0,0);
        glTranslatef(100,-180,0);
        drawSphere(15,10,10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,0,0);
        glTranslatef(-100,-180,0);
        drawSphere(15,10,10);
    }glPopMatrix();

    glPushMatrix(); ///shoot panel 1
    {
        //glRotatef(tx,0,1,0);
        glColor3f(0,0,1);
        glTranslatef(-60,-150,0);
        glRotatef(-35,0,0,1);
        glScalef(2.9,1,1);
        drawSphere(20,3,10);
    }glPopMatrix();

    glPushMatrix(); ///shoot panel 2
    {
        //glRotatef(tx,0,1,0);
        glColor3f(0,0,1);
        glTranslatef(60,-150,0);
        glRotatef(215,0,0,1);
        glScalef(2.9,1,1);
        drawSphere(20,3,10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0.89,0.47,0.20);
        glTranslatef(0,-105,0);
        glRotatef(90,0,0,1);
        drawSphere(17,3,10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,.5,0);
        glTranslatef(0,-75,0);
        glRotatef(90,0,0,1);
        drawSphere(17,3,10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,1,0);
        glTranslatef(0,-45,0);
        glRotatef(90,0,0,1);
        drawSphere(17,3,10);
    }glPopMatrix();

    glPushMatrix(); ///obs1
    {
        glColor3f(0,0,1);
        glRotatef(-30,0,0,1);
        glTranslatef(110,-10,0);
        glScalef(.5,1,1);
        drawSphere(40,3,10);
    }glPopMatrix();

    glPushMatrix(); ///obs2
    {
        glColor3f(0,0,1);
        glRotatef(210,0,0,1);
        glTranslatef(110,10,0);
        glScalef(.5,1,1);
        drawSphere(40,3,10);
    }glPopMatrix();

   /* glPushMatrix(); ///obs 3
    {
        glTranslatef(0,10,0);
        glScalef(1,.7,1);
        drawCube(25);
    }glPopMatrix();*/

    glPushMatrix();  ///balck line 1
    {
        glColor3f(0,0,0);
        glTranslatef(105,-125,0);
        glScalef(.1,1,1);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix();  ///balck line 2
    {
        glColor3f(0,0,0);
        glTranslatef(-105,-125,0);
        glScalef(.1,1,1);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix();  ///balck line 3
    {
        glColor3f(0,0,0);
        glTranslatef(120,-55,0);
        glScalef(.1,1,1);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix();  ///balck line 4
    {
        glColor3f(0,0,0);
        glTranslatef(-120,-55,0);
        glScalef(.1,1,1);
        drawCube(20);
    }glPopMatrix();

    glPushMatrix(); ///left arrow yellow
    {
        glColor3f(1,1,0);
        glRotatef(30,0,0,1);
        glTranslatef(-75,160,0);
        drawSphere(14,3,10);
    }glPopMatrix();

    glPushMatrix(); ///left arrow olive
    {
        glColor3f(0.309804 ,0.309804,0.184314);
        glRotatef(75,0,0,1);
        glTranslatef(45,145,0);
        drawSphere(14,3,10);
    }glPopMatrix();

   /* glPushMatrix();
    {
        glColor3f(0.184314 ,0.184314 ,0.309804);
        glTranslatef(0,60,0);
        drawSphere(25,20,10);
    }glPopMatrix();*/

    glPushMatrix();
    {
        glColor3f(1.00 ,0.43 ,0.78);
        glTranslatef(35,90,0);
        drawSphere(30,20,10);
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
	gluLookAt(00,00,350,	0,0,0,	0,1,0);
	//gluLookAt(200,200,300,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	//drawAxes();
	//drawGrid();

    glColor3f(1,0,0);
    drawpinball();




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate()
{
    //angle+=.005;
    if(tx>200)
        tx=-200;
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
