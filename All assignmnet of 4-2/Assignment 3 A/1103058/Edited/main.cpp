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
                //lines parallal to z axis

                //glVertex3f( 0, 90, i*10);
                //glVertex3f(0, -90, i*10);


            }
        }
        glEnd();
    }
}
void drawCube(double a)
{
    glBegin(GL_QUADS);
    {

        glVertex3f( a, a, a);
        glVertex3f( a,-a, a);
        glVertex3f(-a,-a, a);
        glVertex3f(-a, a, a);

        glVertex3f( a, a,-a);
        glVertex3f( a,-a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a, a,-a);

        glColor3f(0,1,1);
        glVertex3f( a, a, a);
        glVertex3f( a, a,-a);
        glVertex3f( a,-a,-a);
        glVertex3f( a,-a, a);

        glVertex3f(-a, a, a);
        glVertex3f(-a, a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a,-a, a);

        glColor3f(0,1,0);
        glVertex3f( a, a, a);
        glVertex3f( a, a,-a);
        glVertex3f(-a, a,-a);
        glVertex3f(-a, a, a);

        glVertex3f( a,-a, a);
        glVertex3f( a,-a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a,-a, a);
    }
    glEnd();
}
//draws a cylinder of given radius and height
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
void drawCone(double radius,double height,int segments)
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
    //draw triangles using generated points
    for(i=0; i<segments; i++)
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
    for(i=0; i<=stacks; i++)
    {
        h=radius*sin(((double)i/(double)stacks)*(pi/2));
        r=radius*cos(((double)i/(double)stacks)*(pi/2));
        for(j=0; j<=slices; j++)
        {
            points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
            points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
            points[i][j].z=h;
        }
    }
    //draw quads using generated points
    for(i=0; i<stacks; i++)
    {
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
        for(j=0; j<slices; j++)
        {
            glBegin(GL_QUADS);
            {
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
            }
            glEnd();
        }
    }
}
double m= 0;
double n= 0;
void rocket()
{
    glPushMatrix();
    {
    glTranslatef(0,n,0);
    //glTranslatef(1,angle,1);
        glPushMatrix();
        {
            glTranslatef(1,-50,1);
            glColor3f(1,1,1);
            glRotatef(90,1,0,0);
            drawCylinder(25,150,25);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(1,-50,1);
            glTranslatef(1,75,1);
            glRotatef(270,1,0,0);
            drawCone(30,40,20);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glColor3f(1,0,0);
            glTranslatef(1,-40,1);
            glTranslatef(-20,-100,1);
            drawSphere(15,15,15);
        }
        glPopMatrix();
        glPushMatrix();
        {
            glColor3f(1,0,0);
            glTranslatef(1,-40,1);
            glTranslatef(1,-100,1);
            drawSphere(15,15,15);
        }
        glPopMatrix();
        glPushMatrix();
        {
            glColor3f(1,0,0);
            glTranslatef(1,-40,1);
            glTranslatef(20,-100,1);
            drawSphere(15,15,15);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glColor3f(1,0,0);
            glTranslatef(1,-60,1);
            glTranslatef(-20,-100,1);
            drawSphere(15,15,15);
        }
        glPopMatrix();
        glPushMatrix();
        {
            glColor3f(1,0,0);
            glTranslatef(1,-60,1);
            glTranslatef(1,-100,1);
            drawSphere(15,15,15);
        }
        glPopMatrix();
        glPushMatrix();
        {
            glColor3f(1,0,0);
            glTranslatef(1,-60,1);
            glTranslatef(20,-100,1);
            drawSphere(15,15,15);
        }
        glPopMatrix();
    }

    glPopMatrix();
}
void ground()
{
      glPushMatrix();
  {
      glTranslatef(0,-325,0);
       drawCube(200);
  }
  glPopMatrix();
}
void switchbox()
{
    glPushMatrix();
    {
        glScalef(1,.5,.5);
        glColor3f(1,0,0);
        glTranslatef(-100,-100,50);
        drawCube(25);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-110,-50,40);
        drawSphere(8,10,10);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-90,-50,40);
        drawSphere(8,10,10);
    }
    glPopMatrix();
}
void man()
{
    glTranslatef(-100,-120,120);
    glPushMatrix();
    {

        glPushMatrix();//head
        {
            glColor3f(.5,.5,.5);
            glTranslatef(0,75,0);
            glScalef(1,1,1);
            drawSphere(10,15,5);

        }
        glPopMatrix();

        glPushMatrix();////Body////
        {
            glColor3f(0,.5,0);
            glTranslatef(0,48,0);
            glScalef(1.5,2,1);
            drawCube(8);

        }
        glPopMatrix();

        glPushMatrix(); /////// Right Leg///////
        {
            glColor3f(1,0,.5);
            glTranslatef(5,20,0);
            glScalef(.5,1.5,1);
            drawCube(8);

        }
        glPopMatrix();

        glPushMatrix();  //left leg//
        {
            glColor3f(1,0,.5);
            glTranslatef(-5,20,0);
            glScalef(.5,1.5,1);
            drawCube(8);

        }
        glPopMatrix();
        glPushMatrix();//handright
        {
            glColor3f(.5,0,1);
            glTranslatef(12,50,0);
            glScalef(.4,1.5,.3);
            drawCube(8);

        }
        glPopMatrix();

        glPushMatrix();//handleft
        {
            glColor3f(.5,0,1);
            glTranslatef(-12,50,0);
            glScalef(.4,1.5,.3);
            drawCube(8);

        }
        glPopMatrix();

    }
    glPopMatrix();

}

void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {

    case '1':
        drawgrid=1-drawgrid;
        break;
    case 't':
        n+=10;
        break;
    case 'g':
        n-=10;
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
    //gluLookAt(200,200,300,	1,0,0,	0,1,0);
    gluLookAt(0,0,400,	1,0,0,	0,1,0);

    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);


    /****************************
    / Add your objects from here
    ****************************/
    //add objects

    drawAxes();
    drawGrid();
    rocket();
    ground();
    switchbox();
    man();
    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}
void animate()
{

    angle+=0.04;
    glutPostRedisplay();
}
void init()
{
    //codes for initialization
    //drawgrid=1;
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

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(1000, 1000);
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
