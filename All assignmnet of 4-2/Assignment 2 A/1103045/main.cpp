#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include<glut.h>

#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
double tx,a;

struct point
{
    double x,y,z;
};


void drawAxes()
{
    if(drawaxes==1)
        {
            glColor3f(1, 0, 4);
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
            glColor3f(6, 6, 6);	//grey
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

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    {
        glVertex3f( a/2, a/2,2);
        glVertex3f( a/2,-a/2,2);
        glVertex3f(-a/2,-a/2,2);
        glVertex3f(-a/2, a/2,2);
    }
    glEnd();
}


void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0; i<=segments; i++)
        {
            points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
            points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
        }
    //draw segments using generated points
    for(i=0; i<segments; i++)
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
    for(i=0; i<=segments; i++)
        {
            points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
            points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
        }
    //draw triangles using generated points
    for(i=0; i<segments; i++)
        {
            //create shading effect
            if(i<segments/2)
                shade=2*(double)i/(double)segments;
            else
                shade=2*(1.0-(double)i/(double)segments);
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
            glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
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
 }       }

void drawQuads(double a)
{

 glBegin(GL_QUADS);
        {


            glVertex3f( a,-a,-a);
            glVertex3f( a,-a, a);
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
        }
        glEnd();
    }






void drawSs()
{

    glTranslatef(tx,0,0);
    glPushMatrix();




    {

        glTranslatef(0,45,0);
        glColor3f(1,3,5);
         glScalef(5,3,2);
    }



 glPushMatrix();
     {
         glScalef(1.2,1.4,2);
         glTranslatef(-14,7,0);

         drawQuads(3);
     }
     glPopMatrix();


glPushMatrix();
     {

         glScalef(2.9,2,2);
         glColor3f(0,1,2);
         glTranslatef(-14,40,5);

         drawQuads(3.6);
     }
     glPopMatrix();



glPushMatrix();
     {
         glScalef(9,7,6);
         glColor3f(1,2,3);
         glTranslatef(-1.2,9.6,0);

         drawQuads(3);
     }
     glPopMatrix();

glPushMatrix();
     {
         glScalef(9,9,6);
         glColor3f(1,2,3);
         glTranslatef(11,8,0);

         drawQuads(3);
     }
     glPopMatrix();




   glPushMatrix();
   {
     glScalef(8,2,2);
     glTranslatef(5,40,4);
     drawCylinder(2,5,2);


   }
   glPopMatrix();


 glPushMatrix();
   {

     glTranslatef(97,8,14);
     drawCylinder(15,15,15);


   }
   glPopMatrix();


 glPushMatrix();
   {
glColor3f(0,1,2);
     glTranslatef(97,8,-20);
     drawCylinder(15,15,15);


   }
   glPopMatrix();


glPushMatrix();
   {

      glColor3f(0,0,1);
     glTranslatef(-60,70,0);
     drawCylinder(15,40,5);

   }
   glPopMatrix();


glPushMatrix();
     {

         glScalef(1,-20,2);
         glColor3f(0,1,2);
         glTranslatef(-177,10,-40);

         drawQuads(3.6);
     }
     glPopMatrix();

glPushMatrix();
     {

         glScalef(1,-20,2);
         glColor3f(0,1,2);
         glTranslatef(-177,10,-69);

         drawQuads(3.6);
     }
     glPopMatrix();

glPushMatrix();
     {

         glScalef(1,-20,2);
         glColor3f(0,1,2);
         glTranslatef(-100,10,-38);

         drawQuads(3.6);
     }
     glPopMatrix();
glPushMatrix();
     {

         glScalef(1,20,2);
         glColor3f(0,1,2);
         glTranslatef(-100,10,-70);

         drawQuads(3.6);
     }
     glPopMatrix();



 glPushMatrix();
   {
       glColor3f(0,0,1);
     glScalef(28,2,2);
     glTranslatef(0.9,55,7);
     drawCylinder(2,1.1,2);

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
    gluLookAt(100,200,100,	1,1,1,	0,1,0);


    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);


    /****************************
    / Add your objects from here
    ****************************/
    //add objects

    drawAxes();
    //drawGrid();


    //glColor3f(1,0,0);
    //drawSquare(10);

    drawSs();

    //drawCircle(30,24);

    //drawCone(20,50,24);

    //drawSphere(30,24,20);



    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}


void animate()
{
    angle+=0;
    tx=tx+((2*pi*1)/360)*0;

    if(tx>200)
        tx=0;


    //codes for any changes in Models, Camera
    glutPostRedisplay();
}

void init()
{
    //codes for initialization
    a=15;
    drawgrid=1;
    drawaxes=1;
    cameraHeight=150.0;
    cameraAngle=1.0;
    angle=0;
    tx=0;


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

