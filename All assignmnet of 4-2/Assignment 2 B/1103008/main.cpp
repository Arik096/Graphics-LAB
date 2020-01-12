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
double tx,a;

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

                glVertex3f(0,100,0);
                glVertex3f(0,-100,0);

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
        }
        glEnd();
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
void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    {
        glVertex3f( a, a,a);
        glVertex3f( a,-a,a);
        glVertex3f(-a,-a,a);
        glVertex3f(-a, a,a);
    }
    glEnd();
}


void drawSS()
{


     glPushMatrix();
    {
        glTranslatef(0,0,-70);
        glColor3f(0,1,1);
        drawSquare(70);
    } glPopMatrix();

    //glColor3f(1,0,0);
      glPushMatrix();
      {
        glColor3f(1,1,1);
        glTranslatef(0,0,-10);
        drawSquare(12.5);
      } glPopMatrix();
//positive y
 //1y.
        glPushMatrix();
    {

           glColor3f(1,1,0);
           glTranslatef(0,18,0);
           drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {
        glColor3f(1,1,0);
         glTranslatef(0,27,0);
            drawSquare(4);
    } glPopMatrix();
    glPushMatrix();
    {
        glColor3f(1,1,0);
         glTranslatef(0,36,0);
         drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {
        glColor3f(1,1,0);
         glTranslatef(0,45,0);
            drawSquare(4);
    } glPopMatrix();


       glPushMatrix();
    {
        glColor3f(1,1,0);
         glTranslatef(0,54,0);
            drawSquare(4);
    } glPopMatrix();
       glPushMatrix();
    {
        glColor3f(1,0,1);
         glTranslatef(0,63,0);
            drawSquare(4);
    } glPopMatrix();
//2y.
    glPushMatrix();
    {
           glColor3f(1,0,1);
           glTranslatef(9,18,0);
           drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {

         glTranslatef(9,27,0);
            drawSquare(4);
    } glPopMatrix();
    glPushMatrix();
    {

         glTranslatef(9,36,0);
         drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {

         glTranslatef(9,45,0);
            drawSquare(4);
    } glPopMatrix();


       glPushMatrix();
    {

         glTranslatef(9,54,0);
            drawSquare(4);
    } glPopMatrix();
       glPushMatrix();
    {

         glTranslatef(9,63,0);
            drawSquare(4);
    } glPopMatrix();

//3y.
      glPushMatrix();
    {

           glTranslatef(-9,18,0);
           drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {

         glTranslatef(-9,27,0);
            drawSquare(4);
    } glPopMatrix();
    glPushMatrix();
    {

         glTranslatef(-9,36,0);
         drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {

         glTranslatef(-9,45,0);
            drawSquare(4);
    } glPopMatrix();


       glPushMatrix();
    {

         glTranslatef(-9,54,0);
            drawSquare(4);
    } glPopMatrix();
       glPushMatrix();
    {

         glTranslatef(-9,63,0);
            drawSquare(4);
    } glPopMatrix();

//negative y

 //n-1y.
        glPushMatrix();
    {
        glColor3f(1,0,0);
           glTranslatef(0,-18,0);
           drawSquare(4);
    } glPopMatrix();

    glPushMatrix();
    {
        glColor3f(1,0,0);
         glTranslatef(0,-27,0);
            drawSquare(4);
    } glPopMatrix();
    glPushMatrix();
    {
        glColor3f(1,0,0);
         glTranslatef(0,-36,0);
         drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {
        glColor3f(1,0,0);
         glTranslatef(0,-45,0);
            drawSquare(4);
    } glPopMatrix();


       glPushMatrix();
    {
        glColor3f(1,0,0);
         glTranslatef(0,-54,0);
            drawSquare(4);
    } glPopMatrix();
       glPushMatrix();
    {
        glColor3f(1,0,1);
         glTranslatef(0,-63,0);
            drawSquare(4);
    } glPopMatrix();
//n-2y.
    glPushMatrix();
    {
           glColor3f(1,0,1);

           glTranslatef(9,-18,0);
           drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {

         glTranslatef(9,-27,0);
            drawSquare(4);
    } glPopMatrix();
    glPushMatrix();
    {

         glTranslatef(9,-36,0);
         drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {

         glTranslatef(9,-45,0);
            drawSquare(4);
    } glPopMatrix();


       glPushMatrix();
    {

         glTranslatef(9,-54,0);
            drawSquare(4);
    } glPopMatrix();
       glPushMatrix();
    {

         glTranslatef(9,-63,0);
            drawSquare(4);
    } glPopMatrix();

//n-3y.
      glPushMatrix();
    {

           glTranslatef(-9,-18,0);
           drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {

         glTranslatef(-9,-27,0);
            drawSquare(4);
    } glPopMatrix();
    glPushMatrix();
    {

         glTranslatef(-9,-36,0);
         drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {

         glTranslatef(-9,-45,0);
            drawSquare(4);
    } glPopMatrix();


       glPushMatrix();
    {

         glTranslatef(-9,-54,0);
            drawSquare(4);
    } glPopMatrix();
       glPushMatrix();
    {

         glTranslatef(-9,-63,0);
            drawSquare(4);
    } glPopMatrix();
//positive x

     //p-1x.

        glPushMatrix();
    {
        glColor3f(0,1,0);
           glTranslatef(18,0,0);
           drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {
        glColor3f(0,1,0);
         glTranslatef(27,0,0);
            drawSquare(4);
    } glPopMatrix();
    glPushMatrix();
    {
        glColor3f(0,1,0);
         glTranslatef(36,0,0);
         drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {
        glColor3f(0,1,0);
         glTranslatef(45,0,0);
            drawSquare(4);
    } glPopMatrix();


       glPushMatrix();
    {
        glColor3f(0,1,0);
         glTranslatef(54,0,0);
            drawSquare(4);
    } glPopMatrix();
       glPushMatrix();
    {
        glColor3f(1,0,1);
         glTranslatef(63,0,0);
            drawSquare(4);
    } glPopMatrix();
//p-2x.
    glPushMatrix();
    {
           glColor3f(1,0,1);

           glTranslatef(18,9,0);
           drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {

         glTranslatef(27,9,0);
            drawSquare(4);
    } glPopMatrix();
    glPushMatrix();
    {

         glTranslatef(36,9,0);
         drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {

         glTranslatef(45,9,0);
            drawSquare(4);
    } glPopMatrix();


       glPushMatrix();
    {

         glTranslatef(54,9,0);
            drawSquare(4);
    } glPopMatrix();
       glPushMatrix();
    {

         glTranslatef(63,9,0);
            drawSquare(4);
    } glPopMatrix();

//p-3x.
      glPushMatrix();
    {

           glTranslatef(18,-9,0);
           drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {

         glTranslatef(27,-9,0);
            drawSquare(4);
    } glPopMatrix();
    glPushMatrix();
    {

         glTranslatef(36,-9,0);
         drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {

         glTranslatef(45,-9,0);
            drawSquare(4);
    } glPopMatrix();


       glPushMatrix();
    {

         glTranslatef(54,-9,0);
            drawSquare(4);
    } glPopMatrix();
       glPushMatrix();
    {


         glTranslatef(63,-9,0);
            drawSquare(4);
    } glPopMatrix();


//negative x


     //n-1x.
        glPushMatrix();
    {
        glColor3f(0,0,1);
           glTranslatef(-18,0,0);
           drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {
         glColor3f(0,0,1);
         glTranslatef(-27,0,0);
            drawSquare(4);
    } glPopMatrix();
    glPushMatrix();
    {
         glColor3f(0,0,1);
         glTranslatef(-36,0,0);
         drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {
         glColor3f(0,0,1);
         glTranslatef(-45,0,0);
            drawSquare(4);
    } glPopMatrix();


       glPushMatrix();
    {
         glColor3f(0,0,1);
         glTranslatef(-54,0,0);
            drawSquare(4);
    } glPopMatrix();
       glPushMatrix();
    {
          glColor3f(1,0,1);
         glTranslatef(-63,0,0);
            drawSquare(4);
    } glPopMatrix();
//n-2x.
    glPushMatrix();
    {
           glColor3f(1,0,1);

           glTranslatef(-18,9,0);
           drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {

         glTranslatef(-27,9,0);
            drawSquare(4);
    } glPopMatrix();
    glPushMatrix();
    {

         glTranslatef(-36,9,0);
         drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {

         glTranslatef(-45,9,0);
            drawSquare(4);
    } glPopMatrix();


       glPushMatrix();
    {

         glTranslatef(-54,9,0);
            drawSquare(4);
    } glPopMatrix();
       glPushMatrix();
    {

         glTranslatef(-63,9,0);
            drawSquare(4);
    } glPopMatrix();

//n-3x.
      glPushMatrix();
    {

           glTranslatef(-18,-9,0);
           drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {

         glTranslatef(-27,-9,0);
            drawSquare(4);
    } glPopMatrix();
    glPushMatrix();
    {

         glTranslatef(-36,-9,0);
         drawSquare(4);
    } glPopMatrix();

           glPushMatrix();
    {

         glTranslatef(-45,-9,0);
            drawSquare(4);
    } glPopMatrix();


       glPushMatrix();
    {

         glTranslatef(-54,-9,0);
            drawSquare(4);
    } glPopMatrix();
       glPushMatrix();
    {

         glTranslatef(-63,-9,0);
            drawSquare(4);
    } glPopMatrix();

//p-x

    glPushMatrix();
     {
         glColor3f(1,1,0);
        glTranslatef(40,40,-19);
        drawSquare(25.5);

    } glPopMatrix();

//n-x

    glPushMatrix();
    {
        glColor3f(0,0,1);
        glTranslatef(-40,40,-19);
        drawSquare(25.5);

    } glPopMatrix();
//p-y
     glPushMatrix();
    {
        glColor3f(0,1,0);
        glTranslatef(40,-40,-19);
        drawSquare(25.5);

    } glPopMatrix();
//n-y
     glPushMatrix();
    {
        glColor3f(1,0,0);
        glTranslatef(-40,-40,-19);
        drawSquare(25.5);

    } glPopMatrix();

















/*
    int py=16;
    int ny=-16;
    int px=16;
    int nx=-16;
    int pxy=8;

    drawSquare(12);
      glPushMatrix();
    {
        for(int i=1;i<=6;i++)
        {

            //glColor3f(0,0,1);
            glTranslatef(0,py,0);
            drawSquare(4);
        }
    } glPopMatrix();

    glPushMatrix();
    {
        for(int i=1;i<=6;i++)
        {
            glColor3f(0,0,1);
            glTranslatef(0,ny,0);
            drawSquare(4);
        }
    } glPopMatrix();

    glPushMatrix();
    {
        for(int i=1;i<=6;i++)
        {

            glColor3f(1,0,0);
            glTranslatef(px,0,0);
            drawSquare(4);
        }
    } glPopMatrix();

          glPushMatrix();
    {
        for(int i=1;i<=6;i++)
        {

            glColor3f(0,1,0);
            glTranslatef(nx,0,0);
            drawSquare(4);
        }
    } glPopMatrix();























/*

      glPushMatrix();
    {

    } glPopMatrix();

    */


    /*glTranslatef(tx,0,0);
   glPushMatrix();
    {
        glTranslatef(0,25,0);
        glScalef(2,1,1);
        drawCube(a);

    }
    glPopMatrix();

    glRotatef(2*angle,0,0,1);
    glPushMatrix();
    {

        glTranslatef(0,0,20);
        drawCylinder(10,5,15);
    }
    glPopMatrix();

      glPushMatrix();
    {

        glTranslatef(0,0,-20);
        drawCylinder(10,5,15);
    }
    glPopMatrix();*/





/*    glPushMatrix();
//    {
//        glTranslatef(50,0,0);
//        glPushMatrix();
//        {
//            glColor3f(1,0,0);
//            //glRotatef(60,0,0,1);
//            //glTranslatef(60,0,0);
//            glTranslatef(0,100,0);
//            glScalef(6,1,1);
//            drawSquare(20);
//        }
//        glPopMatrix();
//
//        glColor3f(0,1,0);
//        glTranslatef(0,50,0);
//        glRotatef(90,0,0,1);
//        glScalef(4,1,1);
//        drawSquare(20);
//    }
//    glPopMatrix();
//
//    glPushMatrix();
//    {
//
//        glTranslatef(tx,0,0);
//        drawSquare(40);
//
//    }
//    glPopMatrix();
//
//        drawSquare(40);
//
//    glRotatef(angle,0,0,1);
//    glTranslatef(110,0,0);
//    glRotatef(2*angle,0,0,1);
//    glColor3f(0,1,0);
//    drawSquare(15);
//
//    glPushMatrix();
//    {
//        glRotatef(angle,0,0,1);
//        glTranslatef(60,0,0);
//        glRotatef(2*angle,0,0,1);
//        glColor3f(0,0,1);
//        drawSquare(30);
//    }
//    glPopMatrix();
//
//    glRotatef(3*angle,0,0,1);
//    glTranslatef(40,0,0);glTranslatef(0,0,-70);
//    glRotatef(4*angle,0,0,1);
//    glColor3f(1,1,0);
    drawSquare(5);*/


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
    gluLookAt(00,00,200,	0,0,0,	0,1,0);


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

    drawSS();

    //drawCircle(30,24);

   // drawCone(20,50,24);

    //drawSphere(30,24,20);




    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}


void animate()
{
    angle+=.5;
    tx=tx+((2*pi*10)/360)*.5;
    if(tx>200)
        tx=-200;
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

    //a=20;
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
