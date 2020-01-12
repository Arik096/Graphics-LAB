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

float posx=130;
float posy=60;
float posz=0;

float lx=(-1/sqrt(2));
float ly=(-1/sqrt(2));
float lz=0;

float rx= (-1/sqrt(2));
float ry= (1/sqrt(2));
float rz=0;

float ux=0;
float uy=0;
float uz=1;

float mx=0;
float my=0;
float mz=0;


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

				glVertex3f(0, i*10, -90);
				glVertex3f( 0, i*10, 90);




			}
		}glEnd();
	}
}

void drawSquare(double a)
{
    glColor3f(1.0,1.0,1.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,2);
		glVertex3f( a,-a,2);
		glVertex3f(-a,-a,2);
		glVertex3f(-a, a,2);
	}glEnd();
}

void draw3dSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a/2, a/2,a/2);
		glVertex3f( a/2,-a/2,a/2);
		glVertex3f(-a/2,-a/2,a/2);
		glVertex3f(-a/2, a/2,a/2);
	}glEnd();
      //glColor3f(1.0,0.7,0.0);

	glBegin(GL_QUADS);{
		glVertex3f( a/2, a/2,-a/2);
		glVertex3f( a/2,-a/2,-a/2);
		glVertex3f(-a/2,-a/2,-a/2);
		glVertex3f(-a/2, a/2,-a/2);
	}glEnd();
	 //glColor3f(1.0,2.0,1.0);
	glBegin(GL_QUADS);{
		glVertex3f( a/2,a/2,a/2);
		glVertex3f( a/2,a/2,-a/2);
		glVertex3f(-a/2,a/2,-a/2);
		glVertex3f(-a/2,a/2,a/2);
	}glEnd();
	//glColor3f(1.0,.7,2.0);
	glBegin(GL_QUADS);{
		glVertex3f( a/2,-a/2,a/2);
		glVertex3f( a/2,-a/2,-a/2);
		glVertex3f(-a/2,-a/2,-a/2);
		glVertex3f(-a/2,-a/2,a/2);
	}glEnd();
	//glColor3f(.7,.5,1.1);
	glBegin(GL_QUADS);{
		glVertex3f(a/2, a/2,a/2);
		glVertex3f(a/2,-a/2,a/2);
		glVertex3f(a/2,-a/2,-a/2);
		glVertex3f(a/2, a/2,-a/2);
	}glEnd();
	//glColor3f(1.6,.6,1.2);
	glBegin(GL_QUADS);{
		glVertex3f(-a/2, a/2,a/2);
		glVertex3f(-a/2,-a/2,a/2);
		glVertex3f(-a/2,-a/2,-a/2);
		glVertex3f(-a/2, a/2,-a/2);
	}glEnd();
}


void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    //glColor3f(0.7,0.7,0.7);
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
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
			glVertex3f(points[i].x,points[i].y,20);
			glVertex3f(points[i+1].x,points[i+1].y,20);

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
        //glColor3f(shade,shade,shade);

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
double tx=0;


void drawSS()
{
    /*
    glPushMatrix();
    {
    glTranslatef(50,0,0);
    glScalef(2,.5,1);

        glPushMatrix();
        {
        glColor3f(1,0,0);
        //glRotatef(60,0,0,1);
        glTranslatef(0,100,0);
        glScalef(6,1,1);
        drawSquare(20);
        }glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(0,50,0);
            //glRotatef(60,1,0,0);
            glScalef(1,4,1);
            glColor3f(0,1,0);
            drawSquare(20);
        }glPopMatrix();
    }glPopMatrix();
    */
    glPushMatrix();
    {
        glPushMatrix();
            {
                glTranslatef(0,15,25);
                glTranslatef(tx,0,0);
                glRotatef(2*angle,0,0,1);
                drawCircle(10,10);

            }glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(0,15,-40);
                glTranslatef(tx,0,0);
                glRotatef(2*angle,0,0,1);
                drawCircle(10,10);

            }glPopMatrix();

        glTranslatef(0,40,0);
        glTranslatef(tx,0,0);
        glScalef(2,1,1);
        draw3dSquare(40);

    }glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(0,4,0);
                glScalef(20,.1,8);
                draw3dSquare(15);
            }glPopMatrix();
    /*
    //glRotatef(angle,0,0,1);
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
    */
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			drawgrid=1-drawgrid;
			break;

        case 'd':
            posx+=lx;
            posy+=ly;
            posz+=lz;
            break;

        case 'a':
            posx-=lx;
            posy-=ly;
            posz-=lz;
            break;

        case 'w':
            posx+=rx;
            posy+=ry;
            posz+=rz;
            break;

        case 'z':
            posx-=rx;
            posy-=ry;
            posz-=rz;
            break;

        case 'k':
            posx+=ux;
            posy+=uy;
            posz+=uz;
            break;

        case 'l':
            posx-=ux;
            posy-=uy;
            posz-=uz;
            break;

        case 'o':
            mx += 2;
            break;
        case 'p':
            mx -= 2;
            break;
        case 'i':
            my += 2;
            break;
        case 'u':
            my -= 2;
            break;
        case 'y':
            mz += 2;
            break;
        case 't':
            mz -= 2;
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


void drawPark()
{
    glTranslatef(mx,0,0);
    glTranslatef(0,my,0);
    glTranslatef(0,0,mz);
    glRotatef(90,0,1,0);

    glPushMatrix();
    {
        glTranslatef(0,-60,0);

         glColor3f(0,1,0);
        draw3dSquare(120);


    }glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(5,15,10);
        glScalef(1,15,1);
        glColor3f(0.2,0,0);
        draw3dSquare(2);

    }glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(5,15,-10);
        glScalef(1,15,1);
        glColor3f(0.2,0,0);
        draw3dSquare(2);

    }glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(35,15,10);
        glScalef(1,15,1);
        glColor3f(0.2,0,0);
        draw3dSquare(2);

    }glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(35,15,-10);
        glScalef(1,15,1);
        glColor3f(0.2,0,0);
        draw3dSquare(2);

    }glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(5,30,0);
        glScalef(1,1,10);
        glColor3f(0.2,0,0);
        draw3dSquare(2);

    }glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(35,30,0);
        glScalef(1,1,10);
        glColor3f(0.2,0,0);
        draw3dSquare(2);

    }glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(20,30,0);
        glScalef(15,1,1);
        glColor3f(0.2,0,0);
        draw3dSquare(2);

    }glPopMatrix();

}

void drawTree()
{
    glPushMatrix();
    {
        glTranslatef(-20,20,0);
    glRotatef(90,1,0,0);
    glColor3f(0.2,0,0);
    drawCircle(3,60);
    drawCone(5,15,5);


    }glPopMatrix();
    glPushMatrix();
    {
        glColor3f(0.2,0.4,0.1);
        glTranslatef(-20,20,0);
        draw3dSquare(15);
    }glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(-20,25,10);
        draw3dSquare(15);
    }glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(-20,25,-10);
        draw3dSquare(15);
    }glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(-20,30,0);
        draw3dSquare(15);
    }glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(-25,30,0);
        draw3dSquare(15);
    }glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(-15,30,0);
        draw3dSquare(15);
    }glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(-17,35,5);
        drawSphere(10,30,10);
    }glPopMatrix();


}
void drawTreeTwo()
{
    glPushMatrix();
    {
        glTranslatef(-40,20,30);
    glRotatef(90,1,0,0);
    glColor3f(0.2,0,0);
    drawCircle(3,60);
    drawCone(5,15,5);
    }glPopMatrix();
    glPushMatrix();
    {
        glColor3f(0.2,0.4,0.1);
        glTranslatef(-40,20,30);
        glRotatef(-90,1,0,0);
        drawCone(15,15,5);
    }glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(-40,30,30);
        glRotatef(-90,1,0,0);
        drawCone(10,15,5);
    }glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(-40,40,30);
        glRotatef(-90,1,0,0);
        drawCone(5,15,5);
    }glPopMatrix();


}

void drawBody()
{

    glPushMatrix(); //dolna
    {
        glTranslatef(20,40,-5);
        glRotatef(5*angle,1,0,0);
        glTranslatef(-20,-40,0);

    glPushMatrix();
    {
        glTranslatef(20,15,0);
        glScalef(4,3,.5);
        glColor3f(0.2,0,0);
        draw3dSquare(5);

    }glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(20,10,8);
        glScalef(4,.5,3);
        glColor3f(0.6,0.6,0.2);
        draw3dSquare(5);

    }glPopMatrix();

    glPushMatrix(); //upperbody
    {
        glTranslatef(20,18,10);
        glScalef(1.2,1.5,.2);
        glColor3f(1.6,1.6,0.2);
        draw3dSquare(5);

    }glPopMatrix();
    glPushMatrix(); //head
    {
        glTranslatef(20,23,10);
        glScalef(1,1.1,1);
        glColor3f(1.6,1.6,1.2);
        drawSphere(2,20,10);

    }glPopMatrix();
    glPushMatrix(); //lowerbody
    {
        glTranslatef(20,13,14);
        glScalef(1.2,.5,2);
        glColor3f(1.6,1.6,1.2);
        draw3dSquare(5);

    }glPopMatrix();

    glPushMatrix(); //leg
    {
        glTranslatef(18,11,20);
        glScalef(.2,1.5,.2);
        glColor3f(0.9,1.9,0.3);
        draw3dSquare(5);

    }glPopMatrix();
    glPushMatrix();//leg
    {
        glTranslatef(21,11,20);
        glScalef(.2,1.5,.2);
        glColor3f(0.9,1.9,0.3);
        draw3dSquare(5);

    }glPopMatrix();
    glPushMatrix(); //hand
    {
        glTranslatef(25,18,10);
        glRotatef(45,0,0,1);
        glScalef(.2,1.5,.2);
        glColor3f(0.9,1.9,0.3);
        draw3dSquare(5);

    }glPopMatrix();
    glPushMatrix(); //hand
    {
        glTranslatef(15,18,10);
        glRotatef(-45,0,0,1);
        glScalef(.2,1.5,.2);
        glColor3f(0.9,1.9,0.3);
        draw3dSquare(5);

    }glPopMatrix();



    glPushMatrix();
    {
        glTranslatef(11,15,8);
        glScalef(.5,.5,3);
        glColor3f(0.5,0.1,0);
        draw3dSquare(5);

    }glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(29,15,8);
        glScalef(.5,.5,3);
        glColor3f(0.5,0.1,0);
        draw3dSquare(5);

    }glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(11,23,10);
        glRotatef(55,1,0,0);

        glScalef(.15,.15,2);
        glColor3f(0.2,0.6,0.4);
        drawSphere(5,40,15);

    }glPopMatrix();
     glPushMatrix();
    {
        glTranslatef(29,23,10);
        glRotatef(55,1,0,0);

        glScalef(.15,.15,2);
        glColor3f(0.2,0.6,0.4);
        drawSphere(5,40,15);

    }glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(11,25,0);
        glRotatef(-55,1,0,0);

        glScalef(.15,.15,2);
        glColor3f(0.2,0.6,0.4);
        drawSphere(2.8,40,15);

    }glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(29,25,0);
        glRotatef(-55,1,0,0);

        glScalef(.15,.15,2);
        glColor3f(0.2,0.6,0.4);
        drawSphere(2.8,40,15);

    }glPopMatrix();

}glPopMatrix();
}

/*
void drawUpDown()
{
    glTranslatef(-30,5,40);
    glRotatef(45,0,1,0);
    drawCylinder(5,10,10);
    glPushMatrix();
    {
        //glRotatef(angle,0,0,1);
        glTranslatef(0,5,0);
        glColor3f(0.3,0.7,0.7);
        glScalef(3,.1,1);
        draw3dSquare(15);

    }glPopMatrix();

}
*/
/*
void test()
{
    glPushMatrix();
    {
        glTranslatef(0,20,100);
        glRotatef(angle,1,0,0);
    glColor3f(0.3,0.7,0.9);
    drawCircle(5,10);

    }glPopMatrix();


}*/
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

	//gluLookAt(0,50,50,	0,0,0,	0,1,0);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(posx,posy,posz,	posx+lx,posy+ly,posz+lz,	0,1,0);
	//gluLookAt(posx,posy,posz,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects
    //draw3dSquare(40);
	//drawAxes();
	drawGrid();

    glColor3f(1,0,0);
   //drawSquare(10);

    //drawSS();

    drawPark();
    drawBody();
    drawTree();
    drawTreeTwo();
    //drawUpDown();
   // test();
   //drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

int p=-1;

void animate(){

    angle-=p*0.00813;

    if(angle<-2.5)
    {
        p=-1;

    }
    if(angle>2.5)
    {
        p=1;

    }









/*

    if(angle>2)
    {
        angle-=0.0023;


    }

	if(tx>200)
    {
        tx=-180;
    }
	tx+=.05;
*/
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	//drawgrid=1;
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
