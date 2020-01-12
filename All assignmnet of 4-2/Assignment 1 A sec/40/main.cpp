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
double tx;
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
            glColor3f(255, 255, 0);	//grey
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

void drawCube(double a) //Road
{
    glPushMatrix();
    {
       // glScalef(10,1.5,1);
        //glColor3f(0.0,0.1, 0.0);
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

void drawSS()
{
    glPushMatrix();//road
    {
        glTranslatef(0,22,0);
        glScalef(60,1,1);
        glColor3f(0, .1, .5);
        drawCube(10);
    }glPopMatrix();


    glTranslatef(tx,25,0);


    glPushMatrix();
    {
        glTranslatef(0,16,6);
        glRotatef(angle,0,0,-1);
        glColor3f(1, 0, 0);
        drawCylinder(7,5,70);
    }glPopMatrix();


    glPushMatrix();
    {
        glTranslatef(0,16,-6);
        glRotatef(angle,0,0,-1);
        glColor3f(1, 0, 0);
        drawCylinder(7,5,70);
    }glPopMatrix();


    glPushMatrix();//car
    {
        glTranslatef(0,30,0);
        glScalef(5,2,1);
        glColor3f(1, 1, 1);
        drawCube(5);
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
    gluLookAt(0,0,200,	0,0,0,	0,1,0);


    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);


    /****************************
    / Add your objects from here
    ****************************/
    //add objects

    //drawAxes();
    //drawGrid();


   // glColor3f(1,0,0);

    //drawSquare(20);


    drawSS();

    //drawCircle(30,24);

    //drawCone(20,50,24);

    //drawSphere(30,24,20);




    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}

void animate()
{
    angle+=1;
    tx=tx+((2*pi*7)/360)*1;
    if(tx>180)
    {
        tx=-180;
    }

    //codes for any changes in Models, Camera
    glutPostRedisplay();
}

void init()
{
    //codes for initialization
    drawgrid=1;
    drawaxes=1;
    cameraHeight=150.0;
    cameraAngle=1.0;
    angle=0;
    tx=0;

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
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    glutMainLoop();		//The main loop of OpenGL

    return 0;
}