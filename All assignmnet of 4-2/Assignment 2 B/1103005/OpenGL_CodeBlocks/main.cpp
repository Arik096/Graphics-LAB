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

double a;
struct point
{
    double x,y,z;
};


void drawAxes()
{
    if(drawaxes==1)
        {
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_LINES);
            {
                glVertex3f( 100,0,0);
                glVertex3f(-100,0,0);

                glVertex3f(0,-100,0);
                glVertex3f(0, 100,0);

                glVertex3f(0,0, 100);
                glVertex3f(0,0,-100);
            }
            glEnd();
        }
}


void drawGrid()
{
    int i;
    if(drawgrid==1)
        {
            glColor3f(0.6, 0.6, 0.6);	//grey
            glBegin(GL_LINES);
            {
                for(i=-8; i<=8; i++)
                    {

                        if(i==0)
                            continue;	//SKIP the MAIN axes

                        //lines parallel to Y-axis
                        glVertex3f(i*10, -90, 0);
                        glVertex3f(i*10,  90, 0);

                        //lines parallel to X-axis
                        glVertex3f(-90, i*10, 0);
                        glVertex3f( 90, i*10, 0);
                    }
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

void drawCylinder(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0; i<=segments; i++)
        {
            points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
            points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
        }
    //draw quads using generated points
    for(i=0; i<segments; i++)
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

void drawCube(double a)
{
    glPushMatrix();
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
    }glPopMatrix();

}

void drawVillage()
{
    glPushMatrix();
    {
        glColor3f(0.6, 0.8 ,0.196078);
        glScalef(10,1.5,3);
        glTranslatef(0,0,7);
        drawCube(20); //road
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(2.0f, 0.5f, 1.0f);
        glScalef(1,1.1,1);
        glTranslatef(-120,40,-40);
        drawCube(20); //building 1 (leftmost)
    }glPopMatrix();

        glPushMatrix();
    {
        glColor3f(2.0f, 0.5f, 1.0f);
        glTranslatef(-120,80,-40);
        glRotatef(90,0,0,1);
        //glTranslatef(-100,80,0);
        drawSphere(25,3,10);
    }glPopMatrix();


    glPushMatrix();
    {
        glColor3f(0.0f, 0.5f, 0.5f);
        glScalef(2,1,1);
        glTranslatef(-20,48,-40);
        drawCube(20); //building 2 (middle)
    }glPopMatrix();

        glPushMatrix();
    {
        glColor3f(0.0f, 0.5f, 0.5f);
        glScalef(1.5,1,1);
        glTranslatef(-25,80,-40);
        glRotatef(90,0,0,1);
        drawSphere(30,3,10);
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0.658824, 0.658824 ,0.658824);
        glScalef(2,2,1);
        glTranslatef(70,35,-40);
        drawCube(20); //building 3 (right)
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0.658824, 0.658824 ,0.658824);
        glScalef(1.5,1,1);
        glTranslatef(95,125,-40);
        glRotatef(90,0,0,1);
        drawSphere(30,3,10);
    }glPopMatrix();

    glPushMatrix(); //sun
    {
        glColor3f(1,1,0);
        glTranslatef(220,190,-60);
        drawSphere(20,20,20);
    }glPopMatrix();


/////////////////////////////////
    glPushMatrix();
    {
        glScalef(.5,2.5,1);
        glColor3f(0.1f, 0.0f, 0.0f);
        glTranslatef(90,20,-40);
        drawCube(10);  //tree trunk
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0.184314  ,0.309804 ,0.184314);
        glTranslatef(45,85,-40);
        drawSphere(25,20,20); //tree
    }glPopMatrix();
/////////////////////////////////
        glPushMatrix();
    {
        glScalef(.5,2.5,1);
        glColor3f(0.1f, 0.0f, 0.0f);
        glTranslatef(100,20,90);
        drawCube(10);  //tree trunk
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0.184314  ,0.309804 ,0.184314);
        glTranslatef(50,85,90);
        drawSphere(25,20,20); //tree
    }glPopMatrix();
////////////////////////////////////

        glPushMatrix();
    {
        glScalef(.5,2.5,1);
        glColor3f(0.1f, 0.0f, 0.0f);
        glTranslatef(-100,20,90);
        drawCube(10);  //tree trunk
    }glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0.184314  ,0.309804 ,0.184314);
        glTranslatef(-50,85,90);
        drawSphere(25,20,20); //tree
    }glPopMatrix();



}



void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
        {

        case '1':
            drawgrid=1-drawgrid;
            break;

        default:
            break;
        }
}


void specialKeyListener(int key, int x,int y)
{
    switch(key)
        {
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


void mouseListener(int button, int state, int x, int y) 	//x, y is the x-y of the screen (2D)
{
    switch(button)
        {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN) 		// 2 times?? in ONE click? -- solution is checking DOWN or UP
                {
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



void display()
{

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
    //gluLookAt(300,50,00,	0,0,0,	0,1,0);
    ///gluLookAt(-50,300,300,	0,0,0,	0,1,0);     ///for upper view
    ///gluLookAt(400,100,200,	0,0,0,	0,1,0);     ///for side view
    gluLookAt(-50,100,300,	0,0,0,	0,1,0);         ///for vertical view


    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);


    /****************************
    / Add your objects from here
    ****************************/
    //add objects

   /// drawAxes();
    //drawGrid();


    glColor3f(1,0,0);

    //drawSquare(20);
    //drawCube(20);

    drawVillage();

    //drawCircle(30,24);

    //drawCone(20,50,24);

    //drawSphere(30,24,20);




    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}




void init()
{
    //codes for initialization
    drawgrid=1;
    drawaxes=1;
    cameraHeight=150.0;
    cameraAngle=1.0;
    angle=0;


    a=25;
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

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

    glutCreateWindow("My OpenGL Program");

    init();

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing

    glutDisplayFunc(display);	//display callback function


    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    glutMainLoop();		//The main loop of OpenGL

    return 0;
}
