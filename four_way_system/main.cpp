#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <glut.h>
#define pi (2*acos(0.0))
double cameraHeight;
double cameraAngle;
int drawaxes;
double posx=700;
double posy=200;
double posz=50;
double lx=-1/sqrt(2);
double ly=-1/sqrt(2);
double lz=0;
double rx=-1/sqrt(2);
double ry=1/sqrt(2);
double rz=0;
double ux=0;
double uy=0;
double uz=1;
double angle=0;
double theta1=0;
double theta2=0;
double theta3=0;
double theta4=0;
double car1=0;
double car2=0;
double forwardmove1=0;
double forwardmove2=0;
double man1_x=0;
double man1_y=0;
double man2_x=0;
double man2_y=0;
double man3=0;
double man4=0;
double man5=0;
struct point
{
    double x,y,z;
};
void drawAxes()
{
    if(drawaxes==1)
    {
        glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
        glBegin(GL_LINES);
        {
            glVertex3f( 700,0,0);
            glVertex3f(-700,0,0);
            glVertex3f(0,-700,0);
            glVertex3f(0, 700,0);
            glVertex3f(0,0, 700);
            glVertex3f(0,0,-700);
        }
        glEnd();
    }
}
void drawCube(double a)
{
    glBegin(GL_QUADS);
    {
        glVertex3f( a, a, a);
        glVertex3f( a,-a,a);
        glVertex3f(-a,-a,a);
        glVertex3f(-a, a,a);
        glVertex3f( a, a, -a);
        glVertex3f( a,-a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a, a,-a);
        glVertex3f( a, a, a);
        glVertex3f(a, a,-a);
        glVertex3f(a,-a,-a);
        glVertex3f(a,-a, a);
        glVertex3f( -a, a, a);
        glVertex3f(-a, a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a,-a, a);
        glVertex3f( a,a, a);
        glVertex3f( a,a,-a);
        glVertex3f(-a,a,-a);
        glVertex3f(-a,a, a);
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
    for(i=0; i<=segments; i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
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
void drawSphere(double radius,int slices,int stacks)
{
    struct point points[100][100];
    int i,j;
    double h,r;
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
    for(i=0; i<stacks; i++)
    {
        glColor4f(1.0f, 1.0f, 0.0f, 0.0f);//yellow
        for(j=0; j<slices; j++)
        {
            glBegin(GL_QUADS);
            {
                glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
                glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
                glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
                glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
            }
            glEnd();
        }
    }
}
drawJeep(double js)
{
    //main box
    glPushMatrix();
    {
        glTranslatef(0,35,0);
        glScalef(1.5,1,1);
        glColor3f(0.0f, 0.5f, 1.0f);//baby Blue
        drawCube(js);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,45,0);
        glScalef(1.6,.4,.8);
        glColor3f(0.0f, 0.0f, 0.0f);//Black
        drawCube(js);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,45,0);
        glScalef(1.3,.3,1.1);
        glColor3f(0.0f, 0.0f, 0.0f);//Black
        drawCube(js);
    }
    glPopMatrix();
    //front box
    glPushMatrix();
    {
        glTranslatef(40,25,0);
        glScalef(1,.5,1);
        glColor3f(0.0f, 0.5f, 1.0f);//baby Blue
        drawCube(js);
    }
    glPopMatrix();
}
void drawWheel()
{
    // 1st tire
    glPushMatrix();
    {
        glTranslatef(-10,0,18);
        glColor3f(0.0f, 0.0f, 1.0f);//Blue
        glRotatef(theta1,0,0,1);
        drawCylinder(15,4,15);
    }
    glPopMatrix();
    //2nd tire
    glPushMatrix();
    {
        glTranslatef(-10,0,-18);
        glColor3f(0.0f, 0.0f, 1.0f);//Blue
        glRotatef(theta1,0,0,1);
        drawCylinder(15,4,15);
    }
    glPopMatrix();
    //3rd tire
    glPushMatrix();
    {
        glTranslatef(40,0,18);
        glColor3f(0.0f, 0.0f, 1.0f);//Blue
        glRotatef(theta1,0,0,1);
        drawCylinder(15,4,15);
    }
    glPopMatrix();
    //4th tire
    glPushMatrix();
    {
        glTranslatef(40,0,-18);
        glColor3f(0.0f, 0.0f, 1.0f);//Blue
        glRotatef(theta1,0,0,1);
        drawCylinder(15,4,15);
    }
    glPopMatrix();
}
void drawWheelStop()
{
    // 1st tire
    glPushMatrix();
    {
        glTranslatef(-10,0,18);
        glColor3f(0.0f, 0.0f, 1.0f);//Blue
        drawCylinder(15,4,15);
    }
    glPopMatrix();
    //2nd tire
    glPushMatrix();
    {
        glTranslatef(-10,0,-18);
        glColor3f(0.0f, 0.0f, 1.0f);//Blue
        drawCylinder(15,4,15);
    }
    glPopMatrix();
    //3rd tire
    glPushMatrix();
    {
        glTranslatef(40,0,18);
        glColor3f(0.0f, 0.0f, 1.0f);//Blue
        drawCylinder(15,4,15);
    }
    glPopMatrix();
    //4th tire
    glPushMatrix();
    {
        glTranslatef(40,0,-18);
        glColor3f(0.0f, 0.0f, 1.0f);//Blue
        drawCylinder(15,4,15);
    }
    glPopMatrix();
}
void drawHuman1()
{
    glPushMatrix();
    {
        glTranslatef(-80,0,130);
        glScalef(.4,.4,.4);
        glPushMatrix(); //1st feet
        {
            glTranslatef(-20,-30,0);
            glScalef(.5,.2,.7);
            glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); //2nd feet
        {
            glTranslatef(20,-30,0);
            glScalef(.5,.2,.7);
            glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // 1st leg
        {
            glTranslatef(20,0,-10);
            glRotatef(90,1,0,0);
            glColor3f(1.0f, 0.0f, 1.0f);//Purple
            drawCylinder(8,60,20);
        }
        glPopMatrix();
        glPushMatrix(); // 2nd leg
        {
            glTranslatef(-20,0,-10);
            glRotatef(90,1,0,0);
            glColor3f(1.0f, 0.0f, 1.0f);//Purple
            drawCylinder(8,60,20);
        }
        glPopMatrix();
        glPushMatrix(); // body
        {
            glTranslatef(0,60,-5);
            glScalef(1.5,1.6,.7);
            glColor3f(0.1f, 0.0f, 0.1f);//Dark Purple
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); //1st hand 1st part
        {
            glTranslatef(40,80,-10);
            glRotatef(90,0,0,1);
            glRotatef(90,1,0,0);
            glColor3f(1.0f, 0.0f, 1.0f);//Purple
            drawCylinder(8,40,20);
        }
        glPopMatrix();
        glPushMatrix(); //1st hand 2nd part
        {
            glTranslatef(55,95,-10);
            glRotatef(90,1,0,0);
            glColor3f(1.0f, 0.0f, 1.0f);//Purple
            drawCylinder(8,40,20);
        }
        glPopMatrix();
        glPushMatrix(); // 2nd hand 1st part
        {
            glTranslatef(-50,80,-10);
            glRotatef(90,0,0,1);
            glRotatef(90,1,0,0);
            glColor3f(1.0f, 0.0f, 1.0f);//Purple
            drawCylinder(8,40,20);
        }
        glPopMatrix();
        glPushMatrix(); // 2nd hand 2nd part
        {
            glTranslatef(-70,80,-10);
            glRotatef(90,0,0,1);
            glRotatef(90,1,0,0);
            glColor3f(1.0f, 0.0f, 1.0f);//Purple
            drawCylinder(8,40,20);
        }
        glPopMatrix();
        glPushMatrix(); // head
        {
            glTranslatef(0,110,-10);
            drawSphere(20,20,20);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
void drawHuman2()
{
    glPushMatrix(); //1st feet
    {
        glTranslatef(-20,-30,0);
        glScalef(.5,.2,.7);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); //2nd feet
    {
        glTranslatef(20,-30,0);
        glScalef(.5,.2,.7);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // 1st leg
    {
        glTranslatef(20,0,-10);
        glRotatef(90,1,0,0);
        glColor3f(1.0f, 0.0f, 1.0f);//Purple
        drawCylinder(8,60,20);
    }
    glPopMatrix();
    glPushMatrix(); // 2nd leg
    {
        glTranslatef(-20,0,-10);
        glRotatef(90,1,0,0);
        glColor3f(1.0f, 0.0f, 1.0f);//Purple
        drawCylinder(8,60,20);
    }
    glPopMatrix();
    glPushMatrix(); // body
    {
        glTranslatef(0,60,-5);
        glScalef(1.5,1.6,.7);
        glColor3f(0.0f, 0.5f, 0.5f);//Blue-Green
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); //1st hand
    {
        glTranslatef(40,70,-10);
        glRotatef(90,1,0,0);
        glColor3f(1.0f, 0.0f, 1.0f);//Purple
        drawCylinder(8,40,20);
    }
    glPopMatrix();
    glPushMatrix(); // 2nd hand
    {
        glTranslatef(-40,70,-10);
        glRotatef(90,1,0,0);
        glColor3f(1.0f, 0.0f, 1.0f);//Purple
        drawCylinder(8,40,20);
    }
    glPopMatrix();
    glPushMatrix(); // head
    {
        glTranslatef(0,110,-10);
        drawSphere(20,20,20);
    }
    glPopMatrix();
}
void drawMall()
{
    glPushMatrix(); // main body
    {
        glScalef(3,2,1);
        glColor4f(0.0f, 1.0f, 1.0f, 1.0f);//light blue
        drawCube(40);
    }
    glPopMatrix();
    glPushMatrix(); // main body door
    {
        glTranslatef(0,-55,0);
        glScalef(.6,.7,1.1);
        glColor3f(0.0f, 0.0f, 0.0f);//Black
        drawCube(40);
    }
    glPopMatrix();
    glPushMatrix(); // main body 1st bar
    {
        glTranslatef(0,-25,0);
        glScalef(3.1,.1,1.1);
        glColor3f(0.5f, 0.5f, 0.5f);//Violet
        drawCube(40);
    }
    glPopMatrix();
    glPushMatrix(); //main body 2nd bar
    {
        glTranslatef(0,25,0);
        glScalef(3.1,.1,1.1);
        glColor3f(0.5f, 0.5f, 0.5f);//Violet
        drawCube(40);
    }
    glPopMatrix();
    glPushMatrix(); //main body 3rd bar
    {
        glTranslatef(0,80,0);
        glScalef(3.1,.1,1.1);
        glColor3f(0.5f, 0.5f, 0.5f);//Violet
        drawCube(40);
    }
    glPopMatrix();
    glPushMatrix(); // right body
    {
        glTranslatef(160,0,60);
        glScalef(1,2,2.5);
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange/brown
        drawCube(40);
    }
    glPopMatrix();
    glPushMatrix(); //right body 1st bar
    {
        glColor3f(0.5f, 0.5f, 0.5f);//Violet
        glTranslatef(160,-25,60);
        glScalef(1.1,.1,2.6);
        drawCube(40);
    }
    glPopMatrix();
    glPushMatrix(); //right body 2nd bar
    {
        glColor3f(0.5f, 0.5f, 0.5f);//Violet
        glTranslatef(160,25,60);
        glScalef(1.1,.1,2.6);
        drawCube(40);
    }
    glPopMatrix();
    glPushMatrix(); //right body 3rd bar
    {
        glColor3f(0.5f, 0.5f, 0.5f);//Violet
        glTranslatef(160,80,60);
        glScalef(1.1,.1,2.6);
        drawCube(40);
    }
    glPopMatrix();
    glPushMatrix(); // left body
    {
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange/brown
        glTranslatef(-160,0,60);
        glScalef(1,2,2.5);
        drawCube(40);
    }
    glPopMatrix();
    glPushMatrix(); //left body 1st bar
    {
        glColor3f(0.5f, 0.5f, 0.5f);//Violet
        glTranslatef(-160,-25,60);
        glScalef(1.1,.1,2.6);
        drawCube(40);
    }
    glPopMatrix();
    glPushMatrix(); //left body 2nd bar
    {
        glColor3f(0.5f, 0.5f, 0.5f);//Violet
        glTranslatef(-160,25,60);
        glScalef(1.1,.1,2.6);
        drawCube(40);
    }
    glPopMatrix();
    glPushMatrix(); //left body 3rd bar
    {
        glColor3f(0.5f, 0.5f, 0.5f);//Violet
        glTranslatef(-160,80,60);
        glScalef(1.1,.1,2.6);
        drawCube(40);
    }
    glPopMatrix();
}
void drawRoad()
{
    glRotatef(90,0,1,0);
    glPushMatrix(); // Draw the main ground
    {
        glTranslatef(0,-100,0);
        glScalef(22,.001,17);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the road of over-bridge on the ground
    {
        glTranslatef(0,-99,0);
        glScalef(22,.001,7);
        glColor3f(1,0,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the road of over-bridge on the ground divider
    {
        glTranslatef(0,-98,0);
        glScalef(22,.001,.2);
        glColor3f(0,0,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the road on the ground
    {
        glTranslatef(-100,-99,0);
        glScalef(5,.001,17);
        glColor3f(1,0,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the road on the ground divider
    {
        glTranslatef(-100,-98,0);
        glScalef(.2,.001,17);
        glColor3f(0,0,0);
        drawCube(20);
    }
    glPopMatrix();

}
void drawFootpath()
{
    glPushMatrix(); // Draw front left footpath 1
    {
        glTranslatef(-220,-99,240);
        glScalef(1,.001,5);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw front left footpath 2
    {
        glTranslatef(-340,-99,160);
        glScalef(5,.001,1);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw front right footpath 1
    {
        glTranslatef(20,-99,240);
        glScalef(1,.001,5);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw front right footpath 2
    {
        glTranslatef(240,-99,170);
        glScalef(10,.001,1.5);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back left footpath 1
    {
        glTranslatef(-220,-99,-240);
        glScalef(1,.001,5);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back left footpath 2
    {
        glTranslatef(-340,-99,-160);
        glScalef(5,.001,1);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back right footpath 1
    {
        glTranslatef(20,-99,-240);
        glScalef(1,.001,5);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back right footpath 2
    {
        glTranslatef(240,-99,-170);
        glScalef(10,.001,1.5);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
}
void drawPolicebox()
{
    glPushMatrix(); // Draw the base of the police box
    {
        glTranslatef(-100,-85,0);
        glScalef(1,.3,1);
        glColor3f(1,.5,0);
        drawCube(50);
    }
    glPopMatrix();
    glPushMatrix(); // Draw front left pole
    {
        glTranslatef(-140,-40,45);
        glRotatef(90,1,0,0);
        glColor3f(1,0,1);
        drawCylinder(5,140,10);
    }
    glPopMatrix();
    glPushMatrix(); // Draw front right pole
    {
        glTranslatef(-55,-40,45);
        glRotatef(90,1,0,0);
        glColor3f(1,0,1);
        drawCylinder(5,140,10);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back left pole
    {
        glTranslatef(-140,-40,-45);
        glRotatef(90,1,0,0);
        glColor3f(1,0,1);
        drawCylinder(5,140,10);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back right pole
    {
        glTranslatef(-55,-40,-45);
        glRotatef(90,1,0,0);
        glColor3f(1,0,1);
        drawCylinder(5,140,10);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the roof of the police box
    {
        glTranslatef(-100,25,0);
        glScalef(1,.3,1);
        glColor3f(1,.5,0);
        drawCube(50);
    }
    glPopMatrix();
}
void drawOverbridge()
{
    glPushMatrix();
    {
        glTranslatef(75,0,0);
        glPushMatrix(); // draw the main box of over-bridge
        {
            glTranslatef(130,50,0);
            glScalef(2,.2,7);
            glColor3f(1,1,0);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side of main box of over-bridge 1
        {
            glTranslatef(95,90,0);
            glScalef(.1,.1,7.2);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side of main box of over-bridge 2
        {
            glTranslatef(95,70,0);
            glScalef(.1,.1,7.2);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side of main box of over-bridge 1
        {
            glTranslatef(165,90,0);
            glScalef(.1,.1,7.2);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side of main box of over-bridge 2
        {
            glTranslatef(165,70,0);
            glScalef(.1,.1,7.2);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side front edge of main box of over-bridge
        {
            glTranslatef(100,70,138);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side middle edge of main box of over-bridge
        {
            glTranslatef(100,70,0);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back edge of main box of over-bridge
        {
            glTranslatef(100,70,-138);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side front edge of main box of over-bridge
        {
            glTranslatef(160,70,138);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side middle edge of main box of over-bridge
        {
            glTranslatef(160,70,0);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back edge of main box of over-bridge
        {
            glTranslatef(160,70,-138);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the front pillar
        {
            glTranslatef(130,-30,170);
            glRotatef(90,1,0,0);
            glColor3f(1,0,1);
            drawCylinder(20,150,10);
        }
        glPopMatrix();
        glPushMatrix(); // draw the back pillar
        {
            glTranslatef(130,-30,-170);
            glRotatef(90,1,0,0);
            glColor3f(1,0,1);
            drawCylinder(20,150,10);
        }
        glPopMatrix();
        glPushMatrix(); // draw the front box of over-bridge
        {
            glTranslatef(130,50,160);
            glScalef(2,.2,1);
            glColor3f(1,1,0);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the back box of over-bridge
        {
            glTranslatef(130,50,-160);
            glScalef(2,.2,1);
            glColor3f(1,1,0);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the side of front box
        {
            glTranslatef(130,0,270);
            glScalef(.28,1,1);
            glRotatef(90,0,1,0);
            glPushMatrix();
            {
                glTranslatef(95,90,0);
                glScalef(.1,.1,7);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,0);
                glScalef(.1,.1,7);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,138);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,0);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,-138);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
        }
        glPopMatrix();
        glPushMatrix(); // draw the side of back box
        {
            glTranslatef(130,0,-80);
            glScalef(.28,1,1);
            glRotatef(90,0,1,0);
            glPushMatrix();
            {
                glTranslatef(95,90,0);
                glScalef(.1,.1,7);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,0);
                glScalef(.1,.1,7);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,138);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,0);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,-138);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix(); // Draw the slide of front left
    {
        glTranslatef(105,-25,160);
        glRotatef(50,0,0,1);
        glScalef(5,.2,1);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the slide of front right
    {
        glTranslatef(305,-25,160);
        glRotatef(310,0,0,1);
        glScalef(5,.2,1);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the slide of back left
    {
        glTranslatef(105,-25,-160);
        glRotatef(50,0,0,1);
        glScalef(5,.2,1);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the slide of back right
    {
        glTranslatef(305,-25,-160);
        glRotatef(310,0,0,1);
        glScalef(5,.2,1);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front lower edge 1
    {
        glTranslatef(40,-80,175);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front lower edge 2
    {
        glTranslatef(40,-80,145);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front slider hand 1
    {
        glTranslatef(103,15,175);
        glRotatef(50,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front slider hand 2
    {
        glTranslatef(105,-5,175);
        glRotatef(50,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front slider hand 3
    {
        glTranslatef(103,15,145);
        glRotatef(50,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front slider hand 4
    {
        glTranslatef(105,-5,145);
        glRotatef(50,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,0,-320);
        glPushMatrix(); // draw the left side back lower edge 1
        {
            glTranslatef(40,-80,175);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back lower edge 2
        {
            glTranslatef(40,-80,145);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back slider hand 1
        {
            glTranslatef(103,15,175);
            glRotatef(50,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back slider hand 2
        {
            glTranslatef(105,-5,175);
            glRotatef(50,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back slider hand 3
        {
            glTranslatef(103,15,145);
            glRotatef(50,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back slider hand 4
        {
            glTranslatef(105,-5,145);
            glRotatef(50,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front lower edge 1
    {
        glTranslatef(370,-80,175);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front lower edge 2
    {
        glTranslatef(370,-80,145);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front lower edge 1
    {
        glTranslatef(370,-80,175);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front lower edge 2
    {
        glTranslatef(370,-80,145);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front slider hand 1
    {
        glTranslatef(305,15,175);
        glRotatef(310,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front slider hand 2
    {
        glTranslatef(305,15,145);
        glRotatef(310,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front slider hand 3
    {
        glTranslatef(300,3,175);
        glRotatef(310,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front slider hand 4
    {
        glTranslatef(303,0,145);
        glRotatef(310,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,0,-320);
        glPushMatrix(); // draw the right side back lower edge 1
        {
            glTranslatef(370,-80,175);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back lower edge 2
        {
            glTranslatef(370,-80,145);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back slider hand 1
        {
            glTranslatef(305,15,175);
            glRotatef(310,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back slider hand 2
        {
            glTranslatef(305,15,145);
            glRotatef(310,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back slider hand 3
        {
            glTranslatef(303,3,175);
            glRotatef(310,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back slider hand 4
        {
            glTranslatef(300,0,145);
            glRotatef(310,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
void drawCars()
{
    glPushMatrix();
    {
        glScalef(.8,.8,.8);
        glPushMatrix(); //car 1
        {
            //glTranslatef(car1,0,0);
            glTranslatef(450,-100,170);
            glRotatef(180,0,1,0);
            glPushMatrix();
            {
                glColor3f(0,1,1);
                drawJeep(20);
                drawWheel();
            }
            glPopMatrix();
        }
        glPopMatrix();
        glPushMatrix(); //car 2
        {
            //glTranslatef(0,0,car2);
            glTranslatef(-30,-100,-200);
            glRotatef(270,0,1,0);
            glPushMatrix();
            {
                glColor3f(0,1,1);
                drawJeep(20);
                drawWheel();
            }
            glPopMatrix();
        }
        glPopMatrix();
        glPushMatrix(); // left parked car 1
        {
            glTranslatef(80,-80,370);
            glRotatef(270,0,1,0);
            glPushMatrix();
            {
                glColor3f(0,1,1);
                drawJeep(20);
                drawWheelStop();
            }
            glPopMatrix();
        }
        glPopMatrix();
        glPushMatrix(); // left parked car 2
        {
            glTranslatef(180,-80,400);
            glRotatef(90,0,1,0);
            glPushMatrix();
            {
                glColor3f(0,1,1);
                drawJeep(20);
                drawWheelStop();
            }
            glPopMatrix();
        }
        glPopMatrix();
        glPushMatrix(); // left parked car 3
        {
            glTranslatef(265,-80,400);
            glRotatef(90,0,1,0);
            glPushMatrix();
            {
                glColor3f(0,1,1);
                drawJeep(20);
                drawWheelStop();
            }
            glPopMatrix();
        }
        glPopMatrix();
        glPushMatrix(); // right parked car 1
        {
            glTranslatef(-320,-80,370);
            glRotatef(270,0,1,0);
            glPushMatrix();
            {
                glColor3f(0,1,1);
                drawJeep(20);
                drawWheelStop();
            }
            glPopMatrix();
        }
        glPopMatrix();
        glPushMatrix(); // right parked car 2
        {
            glTranslatef(-420,-80,400);
            glRotatef(90,0,1,0);
            glPushMatrix();
            {
                glColor3f(0,1,1);
                drawJeep(20);
                drawWheelStop();
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
}
void drawPoliceman()
{
    glPushMatrix();
    {
        glTranslatef(-10,-50,-110);
        drawHuman1();
    }
    glPopMatrix();
}
void drawBuildings()
{
    glPushMatrix(); // building 1
    {
        glTranslatef(-340,-40,-280);
        glScalef(.5,.8,.7);
        drawMall();
    }
    glPopMatrix();
    glPushMatrix(); // building 2
    {
        glTranslatef(240,10,-310);
        glScalef(1,1.5,.7);
        drawMall();
    }
    glPopMatrix();
}
void drawPedestarians()
{
    glPushMatrix(); //man 1
    {
        //glTranslatef(man1_x,man1_y,0);
        glTranslatef(30,-85,150);
        glScalef(.4,.4,.4);
        glRotatef(90,0,1,0);
        glColor3f(2.0f, 0.5f, 1.0f);
        drawHuman2();
    }
    glPopMatrix();
    glPushMatrix(); //man 2
    {
        //glTranslatef(man2_x,man2_y,0);
        glTranslatef(240,65,150);
        glScalef(.4,.4,.4);
        glRotatef(90,0,1,0);
        glColor3f(2.0f, 0.5f, 1.0f);
        //drawHuman2();
    }
    glPopMatrix();
    glPushMatrix(); //man 3
    {
        //glTranslatef(man3,0,0);
        glTranslatef(-220,-85,150);
        glRotatef(270,0,1,0);
        glScalef(.4,.4,.4);
        glColor3f(2.0f, 0.5f, 1.0f);
        drawHuman2();
    }
    glPopMatrix();
    glPushMatrix(); //man 4
    {
        //glTranslatef(0,0,man4);
        glTranslatef(20,-85,180);
        glScalef(.4,.4,.4);
        glColor3f(2.0f, 0.5f, 1.0f);
        drawHuman2();
    }
    glPopMatrix();
    glPushMatrix(); //man 5
    {
        //glTranslatef(0,0,man5);
        glTranslatef(200,60,150);
        glScalef(.4,.4,.4);
        glColor3f(2.0f, 0.5f, 1.0f);
        //drawHuman2();
    }
    glPopMatrix();
}
void drawParkingLot()
{
    glPushMatrix(); // Draw the left section 1
    {
        glTranslatef(120,-99,240);
        glScalef(.1,.001,3);
        glColor3f(0,0,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the left section 2
    {
        glTranslatef(200,-99,240);
        glScalef(.1,.001,3);
        glColor3f(0,0,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the left section 3
    {
        glTranslatef(280,-99,240);
        glScalef(.1,.001,3);
        glColor3f(0,0,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the left section 4
    {
        glTranslatef(360,-99,240);
        glScalef(.1,.001,3);
        glColor3f(0,0,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the right section 1
    {
        glTranslatef(-340,-99,240);
        glScalef(.1,.001,3);
        glColor3f(0,0,0);
        drawCube(20);
    }
    glPopMatrix();
}
void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {

    case 'd':
        posx=posx+lx;
        posy=posy+ly;
        posz=posz+lz;
        break;
    case 'u':
        posx=posx-lx;
        posy=posy-ly;
        posz=posz-lz;
        break;
    case 'f':
        posx=posx+rx;
        posy=posy+ry;
        posz=posz+rz;
        break;
    case 'b':
        posx=posx-rx;
        posy=posy-ry;
        posz=posz-rz;
        break;
    case 'r':
        posx=posx+ux;
        posy=posy+uy;
        posz=posz+uz;
        break;
    case 'l':
        posx=posx-ux;
        posy=posy-uy;
        posz=posz-uz;
        break;

    default:
        break;
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posx,posy,posz,	posx+lx,posy+lz,posz+lz,	0,1,0);
    glMatrixMode(GL_MODELVIEW);
    drawAxes();
    drawRoad();
    drawFootpath();
    //drawPolicebox();
    //drawOverbridge();
    drawCars();
    //drawPoliceman();
    drawBuildings();
    drawPedestarians();
    drawParkingLot();
    glutSwapBuffers();
}
void animate()
{
    // theta for tire rotating angle
    theta1=theta1-0.5;
    theta2=theta2+0.2;
    // forward move for calculating how much card will move forward
    forwardmove1=((2*pi*15)/360)*0.5;
    forwardmove2=((2*pi*15)/360)*0.2;
    car1=car1-forwardmove1;
    if(car1<-850)
    {
        car1=0;
    }
    car2=car2+forwardmove2;
    if(car2>520)
    {
        car2=0;
    }
    // for controlling man 1
    man1_x=man1_x+.08;
    man1_y=man1_y+.08;
    if(man1_x>140&&man1_y>140)
    {
        man1_x=0;
        man1_y=0;
    }
    // for controlling man 2
    man2_x=man2_x+.08;
    man2_y=man2_y-.08;
    if(man2_x>150&&man2_y<-150)
    {
        man2_x=0;
        man2_y=0;
    }
    // for controlling man 3
    man3=man3-.05;
    if(man3<-200)
    {
        man3=0;
    }
    // for controlling man 4
    man4=man4+.05;
    if(man4>200)
    {
        man4=0;
    }
    // for controlling man 5
    man5=man5-.05;
    if(man5<-250)
    {
        man5=0;
    }
    glutPostRedisplay();
}
void init()
{
    drawaxes=0;
    cameraHeight=150.0;
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80,	1,	1,	1000.0);
}
int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(1300, 900);
    glutInitWindowPosition(0,100);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Cross Road Project");
    init();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutKeyboardFunc(keyboardListener);
    glutMainLoop();
    return 0;
}
