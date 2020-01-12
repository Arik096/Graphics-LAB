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

double poolBall_1,poolBall_2,poolBall_3,poolBall_4,poolBall_5,poolBall_6,poolBall_7,poolBall_8,poolBall_9,poolBall_10,poolBall_11,poolBall_12,poolBall_13,poolBall_14,poolBall_15,poolBall_16;
double stick;



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

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			drawgrid=1-drawgrid;
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




        case 'd':

            movx += 10;
            break;


        case 'a':

            movx -= 10;
            break;

        case 'w':

            movy += 10;
            break;

        case 's':

            movy -= 10;
            break;

        case 'q':

            movz += 10;
            break;

        case 'e':

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






void arnob()
{

    glTranslatef(movx,0,0);
    glTranslatef(0,movy,0);
    glTranslatef(0,0,movz);

/*

    glPushMatrix();
    {

        glRotatef(90,1,0,0);
        glScalef(9,4.5,.3);
        glColor3f(0,1,0);

        drawCube(10);
    }
    glPopMatrix();

  */
    glPushMatrix();
    {

        glRotatef(90,1,0,0);
        glScalef(9,4.5,.3);
        glColor3f(0,1,0);

        drawCube(10);
    }
    glPopMatrix();


    glPushMatrix();
    {
        glScalef(9,.7,.1);
        glTranslatef(0,5.2,470);
        glColor3f(.450,0,0);
        drawCube(10);

    }
    glPopMatrix();


    glPushMatrix();
    {
        glScalef(9,.7,.1);
        glTranslatef(0,5.2,-470);
        glColor3f(.450,0,0);
        drawCube(10);

    }
    glPopMatrix();



    glPushMatrix();
    {
        glScalef(.1,.7,4.7);
        glTranslatef(905,5.2,0);
        glColor3f(.450,0,0);
        drawCube(10);

    }
    glPopMatrix();


    glPushMatrix();
    {
        glScalef(.1,.7,4.7);
        glTranslatef(-905,5.2,0);
        glColor3f(.450,0,0);
        drawCube(10);

    }
    glPopMatrix();





    glPushMatrix();
    {
        glScalef(.25,3.5,.25);
        glTranslatef(340,-10,160);
        glColor3f(0,0,1);
        drawCube(10);

    }
    glPopMatrix();




    glPushMatrix();
    {
        glScalef(.25,3.5,.25);
        glTranslatef(340,-10,-160);
        glColor3f(0,0,1);
        drawCube(10);

    }
    glPopMatrix();



    glPushMatrix();
    {
        glScalef(.25,3.5,.25);
        glTranslatef(-340,-10,-160);
        glColor3f(0,0,1);
        drawCube(10);

    }
    glPopMatrix();



    glPushMatrix();
    {
        glScalef(.25,3.5,.25);
        glTranslatef(-340,-10,160);
        glColor3f(0,0,1);
        drawCube(10);

    }
    glPopMatrix();








// BALLS











/*
    glPushMatrix();
    {


    }
    glPopMatrix();

*/

    glPushMatrix();
    {
        glTranslatef(poolBall_1,0,0);

        glPushMatrix();
        {


            glTranslatef(65,7,0);
            glColor3f(1,0.1,0);
            drawSphere(3,99,99);
        }
        glPopMatrix();

    }
    glPopMatrix();





    glPushMatrix();
    {
        glTranslatef(poolBall_2,0,poolBall_2);
        //glRotatef(20,0,0,1);

        glPushMatrix();
        {

            glTranslatef(65,7,7);
            glColor3f(0,0,1);
            drawSphere(3,99,99);
        }
        glPopMatrix();

    }
    glPopMatrix();



    glPushMatrix();
    {
        glTranslatef(poolBall_3,0,-poolBall_3);

        glPushMatrix();
        {


            glTranslatef(65,7,-7);
            glColor3f(1,0,1);
            drawSphere(3,99,99);
        }
        glPopMatrix();


    }
    glPopMatrix();





    glPushMatrix();
    {

        glTranslatef(poolBall_4,0,-poolBall_4);
        glPushMatrix();
        {


            glTranslatef(65,7,-14);
            glColor3f(1,0.1,0);
            drawSphere(3,99,99);
        }
        glPopMatrix();

    }
    glPopMatrix();





    glPushMatrix();
    {

        glTranslatef(poolBall_5,0,poolBall_5);
        glPushMatrix();
        {


            glTranslatef(65,7,14);
            glColor3f(1,0,0);
            drawSphere(3,99,99);
        }
        glPopMatrix();

    }
    glPopMatrix();





    glPushMatrix();
    {

        glTranslatef(0,0,poolBall_6);
        glPushMatrix();
        {


            glTranslatef(58.5,7,10.5);
            glColor3f(0,.3,0);
            drawSphere(3,99,99);
        }
        glPopMatrix();

    }
    glPopMatrix();







    glPushMatrix();
    {
        glTranslatef(0,0,-poolBall_7);
        glPushMatrix();
        {


            glTranslatef(58.5,7,-10.5);
            glColor3f(0,.3,0);
            drawSphere(3,99,99);
        }
        glPopMatrix();
    }
    glPopMatrix();









    glPushMatrix();
    {
        glTranslatef(poolBall_8,0,-poolBall_8);
        glPushMatrix();
        {


            glTranslatef(58.5,7,-3.5);
            glColor3f(1,0,0);
            drawSphere(3,99,99);
        }
        glPopMatrix();

    }
    glPopMatrix();






    glPushMatrix();
    {
        glTranslatef(poolBall_9,0,poolBall_9);

        glPushMatrix();
        {


            glTranslatef(58.5,7,3.5);
            glColor3f(0,0,1);
            drawSphere(3,99,99);
        }
        glPopMatrix();
    }
    glPopMatrix();







    glPushMatrix();
    {
        glTranslatef(poolBall_10,0,poolBall_10);

        glPushMatrix();
        {


            glTranslatef(52,7,7);
            glColor3f(.450,0,0);
            drawSphere(3,99,99);
        }
        glPopMatrix();
    }
    glPopMatrix();







    glPushMatrix();
    {
        glTranslatef(poolBall_11,0,-poolBall_11);

        glPushMatrix();
        {


            glTranslatef(52,7,-7);
            glColor3f(1,1,0);
            drawSphere(3,99,99);
        }
        glPopMatrix();

    }
    glPopMatrix();










    glPushMatrix();
    {
        glTranslatef(poolBall_12,0,poolBall_12);

        glPushMatrix();
        {


            glTranslatef(52,7,0);
            glColor3f(0,0,0);
            drawSphere(3,99,99);
        }
        glPopMatrix();
    }
    glPopMatrix();








    glPushMatrix();
    {
        glTranslatef(0,0,-poolBall_13);
        glPushMatrix();
        {


            glTranslatef(45.5,7,-4);
            glColor3f(1,0,1);
            drawSphere(3,99,99);
        }
        glPopMatrix();

    }
    glPopMatrix();







    glPushMatrix();
    {
        glTranslatef(0,0,poolBall_14);

        glPushMatrix();
        {


            glTranslatef(45.5,7,4);
            glColor3f(.450,0,0);
            drawSphere(3,99,99);
        }
        glPopMatrix();

    }
    glPopMatrix();





    glPushMatrix();
    {
        glTranslatef(poolBall_15,0,0);
        glPushMatrix();
        {


            glTranslatef(39.5,7,0);
            glColor3f(1,1,0);
            drawSphere(3,99,99);
        }
        glPopMatrix();

    }
    glPopMatrix();









    glPushMatrix();
    {
        glTranslatef(poolBall_16,0,0);

        glPushMatrix();
        {


            glTranslatef(-39.5,7,0);
            glColor3f(1,1,1);
            drawSphere(3,99,99);
        }
        glPopMatrix();

    }
    glPopMatrix();








    glPushMatrix();
    {

        glTranslatef(stick,0,0);
        glPushMatrix();
        {

            glTranslatef(-110,20,0);
            glRotatef(90,0,1,0);
            glRotatef(12,1,0,0);
            glColor3f(1,0,0);
            drawCylinder(1.5,100,99);

        }
        glPopMatrix();

    }
    glPopMatrix();







    glPushMatrix();
    {

        glTranslatef(0,2,-40);
        glRotatef(90,1,0,0);
        glColor3f(0,0,0);
        drawCylinder(4,5,99);
        drawCylinder(3.9,5,99);
        drawCylinder(3.8,5,99);
        drawCylinder(3.7,5,99);
        drawCylinder(3.6,5,99);
        drawCylinder(3.5,5,99);
        drawCylinder(3.4,5,99);
        drawCylinder(3.3,5,99);
        drawCylinder(3.2,5,99);
        drawCylinder(3.1,5,99);
        drawCylinder(3,5,99);
        drawCylinder(2.9,5,99);
        drawCylinder(2.8,5,99);
        drawCylinder(2.7,5,99);
        drawCylinder(2.6,5,99);
        drawCylinder(2.5,5,99);
        drawCylinder(2.4,5,99);
        drawCylinder(2.3,5,99);
        drawCylinder(2.2,5,99);
        drawCylinder(2.1,5,99);
        drawCylinder(2,5,99);
        drawCylinder(1.9,5,99);
        drawCylinder(1.8,5,99);
        drawCylinder(1.7,5,99);
        drawCylinder(1.6,5,99);
        drawCylinder(1.5,5,99);
        drawCylinder(1.4,5,99);
        drawCylinder(1.3,5,99);
        drawCylinder(1.2,5,99);
        drawCylinder(1.1,5,99);
        drawCylinder(1,5,99);
        drawCylinder(0.9,5,99);
        drawCylinder(0.8,5,99);
        drawCylinder(0.7,5,99);
        drawCylinder(0.6,5,99);
        drawCylinder(0.5,5,99);
        drawCylinder(0.4,5,99);
        drawCylinder(0.3,5,99);
        drawCylinder(0.2,5,99);
        drawCylinder(0.1,5,99);

    }
    glPopMatrix();





    glPushMatrix();
    {

        glTranslatef(0,2,40);
        glRotatef(90,1,0,0);
        glColor3f(0,0,0);
        drawCylinder(4,5,99);
        drawCylinder(3.9,5,99);
        drawCylinder(3.8,5,99);
        drawCylinder(3.7,5,99);
        drawCylinder(3.6,5,99);
        drawCylinder(3.5,5,99);
        drawCylinder(3.4,5,99);
        drawCylinder(3.3,5,99);
        drawCylinder(3.2,5,99);
        drawCylinder(3.1,5,99);
        drawCylinder(3,5,99);
        drawCylinder(2.9,5,99);
        drawCylinder(2.8,5,99);
        drawCylinder(2.7,5,99);
        drawCylinder(2.6,5,99);
        drawCylinder(2.5,5,99);
        drawCylinder(2.4,5,99);
        drawCylinder(2.3,5,99);
        drawCylinder(2.2,5,99);
        drawCylinder(2.1,5,99);
        drawCylinder(2,5,99);
        drawCylinder(1.9,5,99);
        drawCylinder(1.8,5,99);
        drawCylinder(1.7,5,99);
        drawCylinder(1.6,5,99);
        drawCylinder(1.5,5,99);
        drawCylinder(1.4,5,99);
        drawCylinder(1.3,5,99);
        drawCylinder(1.2,5,99);
        drawCylinder(1.1,5,99);
        drawCylinder(1,5,99);
        drawCylinder(0.9,5,99);
        drawCylinder(0.8,5,99);
        drawCylinder(0.7,5,99);
        drawCylinder(0.6,5,99);
        drawCylinder(0.5,5,99);
        drawCylinder(0.4,5,99);
        drawCylinder(0.3,5,99);
        drawCylinder(0.2,5,99);
        drawCylinder(0.1,5,99);

    }
    glPopMatrix();





    glPushMatrix();
    {

        glTranslatef(85,2,40);
        glRotatef(90,1,0,0);
        glColor3f(0,0,0);
        drawCylinder(4,5,99);
        drawCylinder(3.9,5,99);
        drawCylinder(3.8,5,99);
        drawCylinder(3.7,5,99);
        drawCylinder(3.6,5,99);
        drawCylinder(3.5,5,99);
        drawCylinder(3.4,5,99);
        drawCylinder(3.3,5,99);
        drawCylinder(3.2,5,99);
        drawCylinder(3.1,5,99);
        drawCylinder(3,5,99);
        drawCylinder(2.9,5,99);
        drawCylinder(2.8,5,99);
        drawCylinder(2.7,5,99);
        drawCylinder(2.6,5,99);
        drawCylinder(2.5,5,99);
        drawCylinder(2.4,5,99);
        drawCylinder(2.3,5,99);
        drawCylinder(2.2,5,99);
        drawCylinder(2.1,5,99);
        drawCylinder(2,5,99);
        drawCylinder(1.9,5,99);
        drawCylinder(1.8,5,99);
        drawCylinder(1.7,5,99);
        drawCylinder(1.6,5,99);
        drawCylinder(1.5,5,99);
        drawCylinder(1.4,5,99);
        drawCylinder(1.3,5,99);
        drawCylinder(1.2,5,99);
        drawCylinder(1.1,5,99);
        drawCylinder(1,5,99);
        drawCylinder(0.9,5,99);
        drawCylinder(0.8,5,99);
        drawCylinder(0.7,5,99);
        drawCylinder(0.6,5,99);
        drawCylinder(0.5,5,99);
        drawCylinder(0.4,5,99);
        drawCylinder(0.3,5,99);
        drawCylinder(0.2,5,99);
        drawCylinder(0.1,5,99);

    }
    glPopMatrix();






    glPushMatrix();
    {

        glTranslatef(85,2,-40);
        glRotatef(90,1,0,0);
        glColor3f(0,0,0);
        drawCylinder(4,5,99);
        drawCylinder(3.9,5,99);
        drawCylinder(3.8,5,99);
        drawCylinder(3.7,5,99);
        drawCylinder(3.6,5,99);
        drawCylinder(3.5,5,99);
        drawCylinder(3.4,5,99);
        drawCylinder(3.3,5,99);
        drawCylinder(3.2,5,99);
        drawCylinder(3.1,5,99);
        drawCylinder(3,5,99);
        drawCylinder(2.9,5,99);
        drawCylinder(2.8,5,99);
        drawCylinder(2.7,5,99);
        drawCylinder(2.6,5,99);
        drawCylinder(2.5,5,99);
        drawCylinder(2.4,5,99);
        drawCylinder(2.3,5,99);
        drawCylinder(2.2,5,99);
        drawCylinder(2.1,5,99);
        drawCylinder(2,5,99);
        drawCylinder(1.9,5,99);
        drawCylinder(1.8,5,99);
        drawCylinder(1.7,5,99);
        drawCylinder(1.6,5,99);
        drawCylinder(1.5,5,99);
        drawCylinder(1.4,5,99);
        drawCylinder(1.3,5,99);
        drawCylinder(1.2,5,99);
        drawCylinder(1.1,5,99);
        drawCylinder(1,5,99);
        drawCylinder(0.9,5,99);
        drawCylinder(0.8,5,99);
        drawCylinder(0.7,5,99);
        drawCylinder(0.6,5,99);
        drawCylinder(0.5,5,99);
        drawCylinder(0.4,5,99);
        drawCylinder(0.3,5,99);
        drawCylinder(0.2,5,99);
        drawCylinder(0.1,5,99);

    }
    glPopMatrix();







    glPushMatrix();
    {

        glTranslatef(-85,2,40);
        glRotatef(90,1,0,0);
        glColor3f(0,0,0);
        drawCylinder(4,5,99);
        drawCylinder(3.9,5,99);
        drawCylinder(3.8,5,99);
        drawCylinder(3.7,5,99);
        drawCylinder(3.6,5,99);
        drawCylinder(3.5,5,99);
        drawCylinder(3.4,5,99);
        drawCylinder(3.3,5,99);
        drawCylinder(3.2,5,99);
        drawCylinder(3.1,5,99);
        drawCylinder(3,5,99);
        drawCylinder(2.9,5,99);
        drawCylinder(2.8,5,99);
        drawCylinder(2.7,5,99);
        drawCylinder(2.6,5,99);
        drawCylinder(2.5,5,99);
        drawCylinder(2.4,5,99);
        drawCylinder(2.3,5,99);
        drawCylinder(2.2,5,99);
        drawCylinder(2.1,5,99);
        drawCylinder(2,5,99);
        drawCylinder(1.9,5,99);
        drawCylinder(1.8,5,99);
        drawCylinder(1.7,5,99);
        drawCylinder(1.6,5,99);
        drawCylinder(1.5,5,99);
        drawCylinder(1.4,5,99);
        drawCylinder(1.3,5,99);
        drawCylinder(1.2,5,99);
        drawCylinder(1.1,5,99);
        drawCylinder(1,5,99);
        drawCylinder(0.9,5,99);
        drawCylinder(0.8,5,99);
        drawCylinder(0.7,5,99);
        drawCylinder(0.6,5,99);
        drawCylinder(0.5,5,99);
        drawCylinder(0.4,5,99);
        drawCylinder(0.3,5,99);
        drawCylinder(0.2,5,99);
        drawCylinder(0.1,5,99);

    }
    glPopMatrix();





    glPushMatrix();
    {

        glTranslatef(-85,2,-40);
        glRotatef(90,1,0,0);
        glColor3f(0,0,0);
        drawCylinder(4,5,99);
        drawCylinder(3.9,5,99);
        drawCylinder(3.8,5,99);
        drawCylinder(3.7,5,99);
        drawCylinder(3.6,5,99);
        drawCylinder(3.5,5,99);
        drawCylinder(3.4,5,99);
        drawCylinder(3.3,5,99);
        drawCylinder(3.2,5,99);
        drawCylinder(3.1,5,99);
        drawCylinder(3,5,99);
        drawCylinder(2.9,5,99);
        drawCylinder(2.8,5,99);
        drawCylinder(2.7,5,99);
        drawCylinder(2.6,5,99);
        drawCylinder(2.5,5,99);
        drawCylinder(2.4,5,99);
        drawCylinder(2.3,5,99);
        drawCylinder(2.2,5,99);
        drawCylinder(2.1,5,99);
        drawCylinder(2,5,99);
        drawCylinder(1.9,5,99);
        drawCylinder(1.8,5,99);
        drawCylinder(1.7,5,99);
        drawCylinder(1.6,5,99);
        drawCylinder(1.5,5,99);
        drawCylinder(1.4,5,99);
        drawCylinder(1.3,5,99);
        drawCylinder(1.2,5,99);
        drawCylinder(1.1,5,99);
        drawCylinder(1,5,99);
        drawCylinder(0.9,5,99);
        drawCylinder(0.8,5,99);
        drawCylinder(0.7,5,99);
        drawCylinder(0.6,5,99);
        drawCylinder(0.5,5,99);
        drawCylinder(0.4,5,99);
        drawCylinder(0.3,5,99);
        drawCylinder(0.2,5,99);
        drawCylinder(0.1,5,99);

    }
    glPopMatrix();









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

	//gluLookAt(100,100,100,	0,0,0,	0,1,0);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(posx, posy, posz,	 posx+lx, posy+ly, posz+lz,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	//drawAxes();
	//drawGrid();

    glColor3f(1,0,0);
    //drawSquare(40);
    arnob();

    //drawSS();

    //drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}





void animate(){

	angle+=0.05;


	//codes for any changes in Models, Camera




	stick += 3;

	if(stick > 20)
    {
        stick = 20;







        poolBall_16 += 6;

            if(poolBall_16 > 72)

                {
                    poolBall_16 = 72;





                    poolBall_1 += 2;

                    if(poolBall_1 > 20)
                    {
                        poolBall_1 = 20;

                    }



                    poolBall_2 += 2;

                    if(poolBall_2 > 22)
                    {
                        poolBall_2 = 22;
                    }



                    poolBall_3 += 2;

                    if(poolBall_3 > 22)
                    {
                        poolBall_3 = 22;
                    }



                    poolBall_4 += 2;

                    if(poolBall_4 > 22)
                    {
                        poolBall_4 = 22;
                    }


                    poolBall_5 += 2;

                    if(poolBall_5 > 22)
                    {
                        poolBall_5 = 22;
                    }


                    poolBall_6 += 2;

                    if(poolBall_6 > 22)
                    {
                        poolBall_6 = 22;
                    }



                    poolBall_7 += 2;

                    if(poolBall_7 > 22)
                    {
                        poolBall_7 = 22;
                    }


                    poolBall_8 += 2;

                    if(poolBall_8 > 22)
                    {
                        poolBall_8 = 22;
                    }



                    poolBall_9 += 2;

                    if(poolBall_9 > 22)
                    {
                        poolBall_9 = 22;
                    }


                    poolBall_10 += 2;

                    if(poolBall_10 > 22)
                    {
                        poolBall_10 = 22;
                    }



                    poolBall_11 += 2;

                    if(poolBall_11 > 22)
                    {
                        poolBall_11 = 22;
                    }



                    poolBall_12 += 2;

                    if(poolBall_12 > 22)
                    {
                        poolBall_12 = 22;
                    }



                    poolBall_13 += 2;

                    if(poolBall_13 > 22)
                    {
                        poolBall_13 = 22;
                    }


                    poolBall_14 += 2;

                    if(poolBall_14 > 22)
                    {
                        poolBall_14 = 22;
                    }



                    poolBall_15 += 2;

                    if(poolBall_15 > 22)
                    {
                        poolBall_15 = 22;
                    }



                    if(poolBall_15 == 22)
                    {
                        	poolBall_1=0;
                            poolBall_2=0;
                            poolBall_3=0;
                            poolBall_4=0;
                            poolBall_5=0;
                            poolBall_6=0;
                            poolBall_7=0;
                            poolBall_8=0;
                            poolBall_9=0;
                            poolBall_10=0;
                            poolBall_11=0;
                            poolBall_12=0;
                            poolBall_13=0;
                            poolBall_14=0;
                            poolBall_15=0;
                            poolBall_16=0;
                            stick = 0;
                    }






                }



    }

/*
















*/


	glutPostRedisplay();
}


void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;
	poolBall_1=0;
	poolBall_2=0;
	poolBall_3=0;
	poolBall_4=0;
	poolBall_5=0;
	poolBall_6=0;
	poolBall_7=0;
	poolBall_8=0;
	poolBall_9=0;
	poolBall_10=0;
	poolBall_11=0;
	poolBall_12=0;
	poolBall_13=0;
	poolBall_14=0;
	poolBall_15=0;
	poolBall_16=0;
	stick = 0;


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
