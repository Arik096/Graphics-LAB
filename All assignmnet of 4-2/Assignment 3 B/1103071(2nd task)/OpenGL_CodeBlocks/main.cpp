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
double ty=0;
double ta=0;
double tb=0;
double tc=0;
double td=0;
double te=0;

float posx=450;
float posy=100;
float posz=0;

float lx=-1/sqrt(2);
float ly=-1/sqrt(2);
float lz=0;

float rx=-1/sqrt(2);
float ry=1/sqrt(2);
float rz=0;

float ux=0;
float uy=0;
float uz=1;

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
//int tx;
//int ty=0;

void underocean()
{
    glPushMatrix(); ///water
    {
        glColor4f(0,1,1,.2);
        glTranslatef(0,0,-150);
        glScalef(35,35,.1);
        drawCube(30);

    }glPopMatrix();


    glPushMatrix();
    {
        glTranslatef(0,-150,0);

        glPushMatrix();
        {

            glTranslatef(tc,0,0);

        glPushMatrix();  ///tree2 left
        {
        glColor3f(0,0,1);
        glTranslatef(-25,0,00);
        drawSphere(20,20,10);
        }glPopMatrix();

        glPushMatrix(); ///tree2 middle
        {
        glTranslatef(0,25,00);
        drawSphere(20,20,10);
        }glPopMatrix();

        glPushMatrix(); ///tree2 right
        {
        glTranslatef(25,0,00);
        drawSphere(20,20,10);
        }glPopMatrix();
        }
        glPopMatrix();

        glPushMatrix(); ///tree2 trunk
        {
        glColor3f(1,1,0);
        glTranslatef(0,-15,0);
        glScalef(.8,4.5,1);
        drawCube(10);

        }glPopMatrix();

        glPushMatrix();
        {

            glTranslatef(tc,0,0);
        glPushMatrix();  ///tree1 left
        {
        glColor3f(0,1,0);
        glTranslatef(-200,0,00);
        drawSphere(20,20,10);
        }glPopMatrix();

        glPushMatrix(); ///tree1 middle
        {
        glColor3f(0,1,0);
        glTranslatef(-175,25,00);
        drawSphere(20,20,10);
        }glPopMatrix();

        glPushMatrix(); ///tree1right
        {
        glColor3f(0,1,0);
        glTranslatef(-150,0,00);
        drawSphere(20,20,10);
        }glPopMatrix();
        }
        glPopMatrix();


        glPushMatrix(); ///tree1 trunk
        {
        glColor3f(1,1,0);
        glTranslatef(-175,-20,0);
        glScalef(.8,4.5,.4);
        drawCube(10);

        }glPopMatrix();

        glPushMatrix();
        {

            glTranslatef(tc,0,0);
        glPushMatrix();  ///tree3 left
        {
        glColor3f(0,1,0);
        glTranslatef(200,0,00);
        drawSphere(20,20,10);
        }glPopMatrix();

        glPushMatrix(); ///tree3 middle
        {
        glColor3f(0,1,0);
        glTranslatef(175,25,00);
        drawSphere(20,20,10);
        }glPopMatrix();

        glPushMatrix(); ///tree3 right
        {
        glColor3f(0,1,0);

        glTranslatef(150,0,00);
        drawSphere(20,20,10);
        }glPopMatrix();

        }
        glPopMatrix();

        glPushMatrix(); ///tree3 trunk
        {
        glColor3f(1,1,0);
        glTranslatef(175,-20,0);
        glScalef(.8,4.5,.4);
        drawCube(10);

        }glPopMatrix();
///////////////////////////////////////Fish1


    glPushMatrix();
    {

        glTranslatef(ty,0,0);
        glTranslatef(160,0,0);

        glPushMatrix(); ///fish1 body
        {
        glScalef(1.9,.8,.2);
        glTranslatef(0,150,0);
        glRotatef(45,0,0,1);
        drawCube(30);
        }glPopMatrix();

        glPushMatrix(); ///fish1 fin1
        {
        glColor3f(1,0,0);
        glScalef(.7,1,.1);
        glTranslatef(20,140,0);
        glRotatef(120,0,0,1);
        drawCube(30);
        }glPopMatrix();

        glPushMatrix(); ///fish1 fin2
        {
        glColor3f(1,0,0);
        glScalef(.7,1,.1);
        glTranslatef(20,100,0);
        glRotatef(60,0,0,1);
        drawCube(30);
        }glPopMatrix();


        glPushMatrix(); ///fish1 tail
        {
        glTranslatef(90,120,0);
        glRotatef(180,0,0,1);
        drawCylinder(25,10,3);
        }glPopMatrix();

        glPushMatrix(); ///eye1
        {
        glColor3f(1,1,1);
        glTranslatef(-50,119,7);
        drawCircle(8,30);
        }glPopMatrix();

        glPushMatrix(); ///eyeball1
        {
        glColor3f(0,0,0);
        glTranslatef(-50,119,7);
        drawCircle(2,50);
        }glPopMatrix();

        glPushMatrix(); ///eye2
        {
        glColor3f(1,1,1);
        glTranslatef(-50,119,-7);
        drawCircle(8,30);
        }glPopMatrix();

        glPushMatrix(); ///eyeball2
        {
        glColor3f(0,0,0);
        glTranslatef(-50,119,-7);
        drawCircle(2,50);
    }glPopMatrix();


    }
    glPopMatrix();

    ////////////////////////////////Fish2
    glPushMatrix();
    {

        glTranslatef(tx,0,0);
        glPushMatrix();
        {

        glTranslatef(-180,200,-50);
        glRotatef(180,0,1,0);
        glPushMatrix(); ///fish2 body
        {
        glColor3f(1,1,0);
        glScalef(1.9,.8,.2);
        glTranslatef(0,150,0);
        glRotatef(45,0,0,1);
        drawCube(30);
        }glPopMatrix();

        glPushMatrix(); ///fish2 fin1
        {
        glColor3f(1,0,0);
        glScalef(.7,1,.1);
        glTranslatef(20,140,0);
        glRotatef(120,0,0,1);
        drawCube(30);
        }glPopMatrix();

        glPushMatrix(); ///fish2 fin2
        {
        glColor3f(1,0,0);
        glScalef(.7,1,.1);
        glTranslatef(20,100,0);
        glRotatef(60,0,0,1);
        drawCube(30);
        }glPopMatrix();


        glPushMatrix(); ///fish2 tail
        {
        glTranslatef(90,120,0);
        glRotatef(180,0,0,1);
        drawCylinder(25,10,3);
        }glPopMatrix();

        glPushMatrix(); ///eye1
        {
        glColor3f(1,1,1);
        glTranslatef(-50,119,7);
        drawCircle(8,30);
        }glPopMatrix();

        glPushMatrix(); ///eyeball1
        {
        glColor3f(0,0,0);
        glTranslatef(-50,119,7);
        drawCircle(2,50);
        }glPopMatrix();

        glPushMatrix(); ///eye2
        {
        glColor3f(1,1,1);
        glTranslatef(-50,119,-7);
        drawCircle(8,30);
        }glPopMatrix();

        glPushMatrix(); ///eyeball2
        {
        glColor3f(0,0,0);
        glTranslatef(-50,119,-7);
        drawCircle(2,50);
        }glPopMatrix();



        }
        glPopMatrix();
    }
    glPopMatrix();

    }glPopMatrix();
}

void bubble()
{
    //bubble fish1
    glPushMatrix();
    {
        glTranslatef(0,tb,0);
        glTranslatef(10,40,0);
        glPushMatrix(); ///bubble1
        {
        glTranslatef(-100,135,0);
        drawSphere(13,20,30);
        }glPopMatrix();

        glPushMatrix(); ///bubble2
        {
        glTranslatef(-100,185,0);
        drawSphere(10,20,30);
        }glPopMatrix();

        glPushMatrix(); ///bubble2
        {
        glTranslatef(-100,225,0);
        drawSphere(7,20,30);
        }glPopMatrix();
    }
    glPopMatrix();
    //bubble fish2

    glPushMatrix();
    {
        glTranslatef(0,ta,0);
        glTranslatef(180,-138,0);
        glPushMatrix(); ///bubble1
        {
        glTranslatef(-100,135,0);
        drawSphere(13,20,30);
        }glPopMatrix();

        glPushMatrix(); ///bubble2
        {
        glTranslatef(-100,185,0);
        drawSphere(10,20,30);
        }glPopMatrix();

        glPushMatrix(); ///bubble2
        {
        glTranslatef(-100,225,0);
        drawSphere(7,20,30);
        }glPopMatrix();
    }
    glPopMatrix();


}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			drawgrid=1-drawgrid;
			break;

        case 'y':
            posx+=lx;
            posy+=ly;
            posz+=lz;
            break;

        case 'b':
            posx-=lx;
            posy-=ly;
            posz-=lz;
            break;

         case 'g':
            posx+=rx;
            posy+=ry;
            posz+=rz;
            break;

        case 'j':
            posx-=rx;
            posy-=ry;
            posz-=rz;
            break;

        case 'm':
            posx+=ux;
            posy+=uy;
            posz+=uz;
            break;

        case 'n':
            posx-=ux;
            posy-=uy;
            posz-=uz;
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
	 //gluLookAt(0,0,350,	0,0,0,	0,1,0);
	//gluLookAt(200,200,300,	0,0,0,	0,1,0);
    gluLookAt(posx,posy,posz,	posx+lx,posy+ly,posz+lz,	0,1,0);

	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	//drawAxes();
	//drawGrid();

    glColor3f(1,0,0);
    underocean();
    bubble();




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate()
{
    //angle+=.005;
    //for fish2
    tx=tx+.05;
    if(tx>550)
    {
        tx=-200;
    }

    //for bubble of fish2
    ta=ta+.05;
    if(ta>750)
    {
        ta=-20;
    }

    //for bubble of fish1
    tb=tb+.06;
    if(tb>750)
    {
        tb=0;
    }

    //for fish2
    ty=ty-.05;
    if(ty<-550)
    {
        ty=220;
    }

    //for tree
    tc=tc+.006;
    if(tc>5)
    {
        tc=0;
    }


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
