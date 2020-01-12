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
double tx=0.0;
double ball;




float posx = 200;
float posy = 200;
float posz = 0;

float lx = (-1/sqrt(2));
float ly = (-1/sqrt(2));
float lz = 0;

float rx = (-1/sqrt(2));
float ry = (1/sqrt(2));
float rz = 0;


float ux = 0;
float uy = 0;
float uz = 1;

float movx = 0;
float movy = 0;
float movz = 0;

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
    glScalef(10,0,2);
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_QUADS);{
		glVertex3f( a,0,2*a);
        glVertex3f( a,0,2*-a);
        glVertex3f(-a,0,2*-a);
        glVertex3f(-a,0,2*a);
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

void drawSS()
{
    glColor3f(1,0,0);
    drawSquare(20);

    glRotatef(angle,0,0,1);
    glTranslatef(110,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSquare(15);

    glPushMatrix();
    {
        glRotatef(angle,0,0,1);
        glTranslatef(60,0,0);
        glRotatef(2*angle,0,0,1);
        glColor3f(0,0,1);
        drawSquare(10);
    }
    glPopMatrix();

    glRotatef(3*angle,0,0,1);
    glTranslatef(40,0,0);
    glRotatef(4*angle,0,0,1);
    glColor3f(1,1,0);
    drawSquare(5);
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

    case '1':
        drawgrid = 1 - drawgrid;
        break;

         case 'y':
            posx += lx;
            posy += ly;
            posz += lz;
            break;



        case 'b':
            posx -= lx;
            posy -= ly;
            posz -= lz;
            break;


        case 'g':
            posx += rx;
            posy += ry;
            posz += rz;
            break;

        case 'r':
            posx -= rx;
            posy -= ry;
            posz -= rz;
            break;


        case 'l':
            posx += ux;
            posy += uy;
            posz += uz;
            break;

        case 'j':
            posx -= ux;
            posy -= uy;
            posz -= uz;
            break;




        case 'c':

            movx += 10;
            break;


        case 'z':

            movx -= 10;
            break;

        case 's':

            movy += 10;
            break;

        case 'x':

            movy -= 10;
            break;

        case 'a':

            movz += 10;
            break;

        case 'd':

            movz -= 10;
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

void bottle(double x,double y,double z){
    glPushMatrix();
    {

        glTranslatef(x,y,z);
        glPushMatrix();{
            glScalef(0.25,.50,0.25);
            glTranslatef(-100,15,1);
            glColor3f(0,0,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix();{
            glScalef(0.25,.50,0.25);
            glTranslatef(-100,40,1);
            glColor3f(0,1,1);
            drawCube(10);
        }
        glPopMatrix();


    }
    glPopMatrix();
}

void human(){
    //foot start
    glPushMatrix();{
        glPushMatrix();{
        glTranslatef(-1,2,0);
            glScalef(1,1,2);
            drawCube(3);
        }glPopMatrix();

        glPushMatrix();{
            glTranslatef(12,2,0);
            glScalef(1,1,2);
            drawCube(3);
        }glPopMatrix();
    }glPopMatrix();
    //foot end

    //leg start
    glPushMatrix();{
        glPushMatrix();{
            glTranslatef(-1,8,5);
            glScalef(1,4,1);
            drawCube(3);
        }glPopMatrix();

        glPushMatrix();{

            glTranslatef(12,8,5);
            glScalef(1,4,1);
            drawCube(3);
        }glPopMatrix();
    }glPopMatrix();
    //leg end

    //body start
    glPushMatrix();{
        glTranslatef(5.50,28,5);
        glScalef(1,1,0.50);
        drawCube(10);
    }glPopMatrix();

    //body end

    //head start
    glPushMatrix();{
        glTranslatef(4.5,38,4);
        drawCube(4);
    }glPopMatrix();

    //head end

    //hand start
    glPushMatrix();{
        glPushMatrix();{
            glTranslatef(18,34,3.5);
            drawCube(2);
        }glPopMatrix();

        glPushMatrix();{
            glTranslatef(-6,34,3.5);
            drawCube(2);
        }glPopMatrix();

        glPushMatrix();{
            glColor3f(1,1,1);
            glTranslatef(21,28,4);
            glScalef(1,4,1);
            drawCube(2);
        }glPopMatrix();

        glPushMatrix();{
            //glRotatef(60,0,0,5);
            glColor3f(1,1,1);
            glTranslatef(-10,28,4);
            glScalef(1,4,1);
            drawCube(2);
        }glPopMatrix();
    }glPopMatrix();
    //hand end
}
void NEW()
{

    glTranslatef(movx,0,0);
    glTranslatef(0,movy,0);
    glTranslatef(0,0,movz);

    glPushMatrix();
    {
        glTranslatef(0,0,50);
        glScalef(2.5,.05,8);
        drawCube(20);

    }glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0,-10,50);
        glScalef(5.5,.1,16);
        glColor3f(0,1,0);
        drawCube(20);

    }glPopMatrix();




    glPopMatrix();
    glPushMatrix();
    {
        glScalef(2.5,2,.05);
        glTranslatef(0,20,-2200);
        glColor3f(1,1,0);
        drawCube(20);

    }
    glPopMatrix();

    // start bottle design
    //last line
    glPushMatrix();{
        bottle(-5.0,0.0,-80.0);
    }glPopMatrix();

    glPushMatrix();{
        bottle(15,0.0,-80.0);
    }glPopMatrix();

    glPushMatrix();{
        bottle(35,0.0,-80.0);
    }glPopMatrix();

    glPushMatrix();{
        bottle(55,0.0,-80.0);
    }glPopMatrix();

    //first line
    glPushMatrix();{
        bottle(-5.0,0.0,-60.0);
    }glPopMatrix();

    glPushMatrix();{
        bottle(15,0.0,-60.0);
    }glPopMatrix();

    glPushMatrix();{
        bottle(35,0.0,-60.0);
    }glPopMatrix();

    glPushMatrix();{
        bottle(55,0.0,-60.0);
    }glPopMatrix();

    //end bottle design

    //human design starts
    glPushMatrix();{



        glPushMatrix();{
            glTranslatef(0,0,150);
            human();
        }glPopMatrix();



    }glPopMatrix();


        glPushMatrix();
        {
            glTranslatef(0,0,-ball);
            glPushMatrix();
            {

                glTranslatef(0,8,130);
                drawSphere(10,20,10);

            }glPopMatrix();

        }glPopMatrix();



    //human design end

    glPushMatrix();
    {
        glTranslatef(5,45,155);
        drawSphere(7,20,20);
    }glPopMatrix();



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


	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);

	//gluLookAt(30,50,30,	0,0,0,	0,1,0);
	//gluLookAt(100,30,50,	0,0,0,	0,1,0);
	//gluLookAt(200,150,100,	0,0,0,	0,1,0);
	gluLookAt(posx, posy, posz,	 posx+lx, posy+ly, posz+lz,	0,1,0);
	//gluLookAt(100,30,10,	0,0,0,	0,1,0);


    //gluLookAt(00,100,200,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	//drawAxes();
	//drawGrid();

    glColor3f(1,0,0);

    NEW();
    //drawSquare(10);

    //drawSS();

    //drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){




	ball += .08;

	if(ball > 180)
    {
        ball = 0;
    }




    glutPostRedisplay();
}

void init(){
	//codes for initialization
	//drawgrid=0;
	//drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;
	ball = 0;

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