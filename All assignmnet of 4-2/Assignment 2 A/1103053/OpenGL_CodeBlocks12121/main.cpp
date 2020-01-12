#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

//#define pi (2*acos(0.0))
#define pi 3.1416

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

				glVertex3f(-90,0,i*10);
				glVertex3f(90,0,i*10);
			}
		}glEnd();
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
    //draw quads using generated points
    for(i=0;i<segments;i++)
    {

        glBegin(GL_QUADS);
        {
			glVertex3f(points[i].x,points[i].y,height/2);
			glVertex3f(points[i+1].x,points[i+1].y,height/2);
			glVertex3f(points[i+1].x,points[i+1].y,-height/2);
			glVertex3f(points[i].x,points[i].y,-height/2);

        }
        glEnd();
    }
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












void drawhuman()
{


//Body
  glPushMatrix();{
   glTranslatef(0,40,0);
  glRotatef(90,1,0,0);
  glScalef(1,1,8);
  drawCylinder(9.5,2,40);
  }glPopMatrix();

//waist
  glPushMatrix();{
  glColor3f(1,1,1);
  glTranslatef(0,25,0);
  drawCube(7);
  }glPopMatrix();
  glColor3f(0,1,1);

//rightLeg
glPushMatrix();{
   glTranslatef(0,8,5);
  glRotatef(-120,1,0,0);
  glScalef(1,1,8);
  drawCylinder(4,3,10);
  }glPopMatrix();
//leftLeg
glPushMatrix();{
   glTranslatef(0,8,-5);
  glRotatef(-240,1,0,0);
  glScalef(1,1,8);
  drawCylinder(4,3,10);
  }glPopMatrix();
//leftfoot
glPushMatrix();{
glColor3f(1,1,0);
glScalef(2,1,1);
 glTranslatef(0,0,-5);
drawCube(2);
 }glPopMatrix();
//rightfoot
 glPushMatrix();{
glColor3f(1,1,0);
glScalef(2,1,1);
 glTranslatef(0,0,12);
drawCube(2);
}glPopMatrix();
//neck
glPushMatrix();{
   glColor3f(1,1,1);
   glRotatef(90,0,1,0);
   glScalef(1,2,1);
   glTranslatef(0,26,0);
   drawCube(3);
}glPopMatrix();
//Head
glPushMatrix();{
glTranslatef(0,60,0);
drawSphere(10,8,10);
}glPopMatrix();
//rightmuscle
glPushMatrix();{
glColor3f(0,1,1);
glScalef(1,1,2);
glTranslatef(0,45,6);
drawCube(2);
}glPopMatrix();

//leftmuscle
glPushMatrix();{
glColor3f(0,1,1);
glScalef(1,1,2);
glTranslatef(0,45,-6);
drawCube(2);
}glPopMatrix();

//righthand
glPushMatrix();{
glColor3f(1,1,0);
glTranslatef(0,38,18);
glScalef(1,4,1);
drawCube(2);
}glPopMatrix();

//lefthand
glPushMatrix();{
glColor3f(1,1,0);
glTranslatef(0,38,-18);
glScalef(1,4,1);
drawCube(2);
}glPopMatrix();
}

double ty=0;
double tz=0;
double tx=0;
double tj=0;
void drawobject()
{

    //road
   glPushMatrix();{
        glScalef(100,1,2);
        glColor3f(0,1,0);
        drawCube(20);
    }glPopMatrix();



   //cube
   glPushMatrix();{
        glColor3f(1,0,0);
        glScalef(2,1,1);
        glTranslatef(20,60,10);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix();{
        glColor3f(1,1,0);
        glScalef(2,1,1);
        glTranslatef(100,28,10);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix();{
        glColor3f(1,0,1);
        glScalef(2,1,1);
        glTranslatef(-60,60,10);
        drawCube(10);
    }glPopMatrix();

     glPushMatrix();{
        glColor3f(0,0,1);
        glScalef(2,1,1);
        glTranslatef(-110,28,10);
        drawCube(10);
    }glPopMatrix();

}




void drawTempleRun()
{

     drawobject();



   glPushMatrix();{
    glTranslatef(tj,0,0);
    glTranslatef(0,tz,0);
    glTranslatef(0,ty,0);
    glTranslatef(tx,0,0);
    glTranslatef(-300,20,10);
    drawhuman();
    }
    glPopMatrix();






}







void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case 'l':
		        tx+=2;
		    break;
        case 'i':
                ty+=5;
                break;
        case 'm':
               tz+=-5;
               break;
        case 'j':
                tj+=-2 ;

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
		case GLUT_KEY_UP:
		    	// up arrow key
			break;

		case GLUT_KEY_RIGHT:

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
	gluLookAt(-400,100,100,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	//drawGrid();

    glColor3f(1,0,0);
    //drawSquare(10);

     //drawSS();

    //drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);

	//drawCylinder(30,50,24);
    //drawCube(20);
    // drawCylinder();
    drawTempleRun();
    //drawhuman();
    //drawobject();
	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){

  if(tx==650)
  {
      tx=-50;
  }


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
	glutInitWindowPosition(0 ,0);
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
