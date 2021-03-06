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

void drawSS()
{
    //1
    glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(3,1,0.2);
      glTranslatef(-30,-80,0);
      drawCube(10);
    }glPopMatrix();
//2
  glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(1,3,0.2);
      glTranslatef(-70,-14,0);
      drawCube(10);
    }glPopMatrix();

//3
glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(1.5,1,0.2);
      glTranslatef(-30,-40,0);
      drawCube(10);
    }glPopMatrix();
    //4
 glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(1,4,0.2);
      glTranslatef(-20,-13,0);
      drawCube(10);
    }glPopMatrix();
    //5
 glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(1.5,1,0.2);
      glTranslatef(2,-22,0);
      drawCube(10);
    }glPopMatrix();
//6
 glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(1,5,0.2);
      glTranslatef(28,-8.5,0);
      drawCube(10);
    }glPopMatrix();
    //7
 glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(1.2,1,0.2);
      glTranslatef(42,-82.5,0);
      drawCube(10);
    }glPopMatrix();
    //8
 glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(1,4,0.2);
      glTranslatef(73,-13.1,0);
      drawCube(10);
    }glPopMatrix();
    //9
 glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(5.7,1,0.2);
      glTranslatef(4.5,17.5,0);
      drawCube(10);
    }glPopMatrix();
//10
 glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(1,1.2,0.2);
      glTranslatef(72.2,33,0);
      drawCube(10);
    }glPopMatrix();
    //11
 glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(3.1,1,0.2);
      glTranslatef(16.5,62,0);
      drawCube(10);
    }glPopMatrix();
    //12
 glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(1,2.2,0.2);
      glTranslatef(-21,22.5,0);
      drawCube(10);
    }glPopMatrix();
    //13
 glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(1,3.2,0.2);
      glTranslatef(-70,12.5,0);
      drawCube(10);
    }glPopMatrix();
//14
 glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(1.4,1,0.2);
      glTranslatef(-32.5,40,0);
      drawCube(10);
    }glPopMatrix();
 //15
    glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(2,1,0.2);
      glTranslatef(-50,61.5,0);
      drawCube(10);
    }glPopMatrix();
//16
    glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(2,1,0.2);
      glTranslatef(-50,18,0);
      drawCube(10);
    }glPopMatrix();
//17
    glPushMatrix();
    {
        glColor3f(1,0,0);
      //glRotatef(90,0,1,0);
      glScalef(1,2.5,0.2);
      glTranslatef(-110,-6,0);
      drawCube(10);
    }glPopMatrix();


//18
 glPushMatrix();
    {
        glColor3f(1,0,1);
      //glRotatef(90,0,1,0);
      glScalef(2,1.5,1);
      glTranslatef(-50,-36,0);
      drawCube(10);
    }glPopMatrix();

//19
 glPushMatrix();
    {
        glColor3f(1,1,0);
      //glRotatef(90,0,1,0);
      glScalef(.8,2.4,1);
      glTranslatef(-112,-6.5,0);
      drawCube(10);
    }glPopMatrix();

//20
 glPushMatrix();
    {
        glColor3f(0,1,0);
      //glRotatef(90,0,1,0);
      glScalef(1.4,1.1,1);
      glTranslatef(-32,17,0);
      drawCube(10);
    }glPopMatrix();

//21
 glPushMatrix();
    {
        glColor3f(0,1,0);
      //glRotatef(90,0,1,0);
      glScalef(1.4,.9,1);
      glTranslatef(-32,-23,0);
      drawCube(10);
    }glPopMatrix();

//22
 glPushMatrix();
    {
        glColor3f(1,1,0);
      //glRotatef(90,0,1,0);
      glScalef(5,1,1);
      glTranslatef(-6,-2,0);
      drawCube(10);
    }glPopMatrix();

//23
 glPushMatrix();
    {
        glColor3f(0,1,1);
      //glRotatef(90,0,1,0);
      glScalef(1.4,2,1);
      glTranslatef(-32,-35,0);
      drawCube(10);
    }glPopMatrix();
//24
 glPushMatrix();
    {
        glColor3f(1,0,1);
      //glRotatef(90,0,1,0);
      glScalef(1.4,1,1);
      glTranslatef(-32.5,61,0);
      drawCube(10);
    }glPopMatrix();
//25
 glPushMatrix();
    {
        glColor3f(0,1,1);
      //glRotatef(90,0,1,0);
      glScalef(1.4,3,1);
      glTranslatef(3,-20.5,0);
      drawCube(10);
    }glPopMatrix();
//26
 glPushMatrix();
    {
        glColor3f(1,1,1);
      //glRotatef(90,0,1,0);
      glScalef(1.2,4,1);
      glTranslatef(42,-8,0);
      drawCube(10);
    }glPopMatrix();
//27
 glPushMatrix();
    {
        glColor3f(0,1,1);
      //glRotatef(90,0,1,0);
      glScalef(3.9,1.2,1);
      glTranslatef(6,33,0);
      drawCube(10);
    }glPopMatrix();
//28
 glPushMatrix();
    {
        glColor3f(0,1,1);
      //glRotatef(90,0,1,0);
      glScalef(1.6,1,1);
      glTranslatef(3,61,0);
      drawCube(10);
    }glPopMatrix();
//29
 glPushMatrix();
    {
        glColor3f(1,1,1);
      //glRotatef(90,0,1,0);
      glScalef(1,1,1);
      glTranslatef(72.5,-3,0);
      drawCube(10);
    }glPopMatrix();
//30
 glPushMatrix();
    {
        glColor3f(0,1,0);
      //glRotatef(90,0,1,0);
      glScalef(2,1.2,1);
      glTranslatef(-50,34,0);
      drawCube(10);
    }glPopMatrix();




glPushMatrix();
{
  glTranslatef(-64,-70,10);
  glPushMatrix(); //head (sphere)
    {
        glTranslatef(0,34,0);
        drawSphere(6,6,6);
    }glPopMatrix();

    glPushMatrix(); // head (cyl)
    {

        glTranslatef(0,27,0);
        glRotatef(90,1,0,0);
        drawCylinder(4,5,8);
    }glPopMatrix();

    glPushMatrix(); //body
    {
        glScalef(.2,.15,1);
        glTranslatef(0,128,0);
        drawCube(20);

    }glPopMatrix();

    glPushMatrix(); //left leg
    {
        glTranslatef(-6,15,0);
        glScalef(.2,.3,1);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix(); // right leg
    {
        glTranslatef(6,15,0);
        glScalef(.2,.3,1);
        drawCube(10);
    }glPopMatrix();

     glPushMatrix(); // right hand
    {
        glTranslatef(-7,22.5,0);
        glScalef(.3,.1,1);
        drawCube(10);
    }glPopMatrix();

    glPushMatrix(); // left hand
    {
        glTranslatef(7,22.5,0);
        glScalef(.3,.1,1);
        drawCube(10);
    }glPopMatrix();

}glPopMatrix();

















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
//    glTranslatef(40,0,0);
//    glRotatef(4*angle,0,0,1);
//    glColor3f(1,1,0);
    drawSquare(5);*/

  /*  glPushMatrix();
    {
     glScalef(25,.22,1);
     glTranslatef(0,-220,0);
     drawSquare(250);
    }
    glPopMatrix();


    glTranslatef(tx,0,0);
    glPushMatrix();
    {
        glTranslatef(0,30,0);
        glScalef(2,1,1);
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
    glPopMatrix();

    glRotatef(2*angle,0,0,1);
    glPushMatrix();
    {
        glTranslatef(0,0,25);
        drawCylinder(25,10,10);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,0,-25);
        drawCylinder(25,10,10);
    }
    glPopMatrix();
*/
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

    //drawCone(20,50,24);

    //drawSphere(30,24,20);




    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}


void animate()
{
    angle+=.3;
    tx=tx-((2*pi*25)/360)*.3;
    if(tx<-200)
        tx=200;
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

    a=30;
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
