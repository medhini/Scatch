#include <stdio.h>
//#include<GL/glew.h>
#include <stdlib.h>
#include <math.h>
#if defined(__APPLE__)
#include <GLUT/glut.h>

#else
#include <GL/glut.h>
#endif
#define NENDS 2 /* number of end "points" to draw */
#define b1 100
#define b2 150
GLdouble width, height; /* window width and height */
int wd; /* GLUT window handle */
int ends[NENDS][2];
int i=0; /* array of 2D points */
float x, y, r=15, g=9.8, u, ch1=0, ch2 = 0;
int theta;
float tof;
float X1[500],Y1[500],X2[500],Y2[500];
void calc1(int,float);
void calc2(int,float);
#define PI 3.14
/* Program initialization NOT OpenGL/GLUT dependent,
as we haven't created a GLUT window yet */
void init(void)
{
    width = 1280.0; /* initial window width and height, */
    height = 800.0; /* within which we draw. */
    ends[0][0] = (int)(0.0*width); /* (0,0) is the lower left corner */
    ends[0][1] = (int)(1.0*height);
    ends[1][0] = (int)(1.0*width);
    ends[1][1] = (int)(0.0*height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}
/* Callback functions for GLUT */
/* Draw the window - this is where all the GL actions are */
void circle_draw()
{
  //  glColor3f(1.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_POLYGON);
    int h = 1-r;
    int x0 = 0, y0 = r;
    double end = r/(sqrt(2));
    while(x0<=end)
    {
        if(h<=0)
        {
            h += 2*x0 + 3;
        }
        else
        {
            h += 2*x0 - 2*y0 + 5;
            y0--;
        }
        x0++;
        glVertex2d(x + x0, y + y0);
        glVertex2d(x + x0, y - y0);
        glVertex2d(x - x0, y - y0);
        glVertex2d(x - x0, y + y0);
        glVertex2d(x + y0, y + x0);
        glVertex2d(x + y0, y - x0);
        glVertex2d(x - y0, y - x0);
        glVertex2d(x - y0, y + x0);
    }
    glEnd();
    glutSwapBuffers();
}

void repeated_draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(X1[i],Y1[i],0);
    glColor3f(1.0, 0.0, 0.0);
    circle_draw();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
    
    
    
     glColor3f(0.0, 0.0, 0.0);
     glPushMatrix();
    glTranslatef(X2[i],Y2[i],0);
    circle_draw();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
    
    
}
void calc1(int u, float theta)
{
    int i;
    theta = (theta*PI)/180;
    tof = 2*u*sin(theta)/g;
    float del_t = tof/b1;
    float temp=0;
    for(i=0; i<b1; i++)
    {
        x = u*cos(theta)*temp;
        y = u*sin(theta)*temp - ((g*temp*temp)/2);
        X1[i]=x-900;
        Y1[i]=y;
        temp += del_t;
    }
    for(i=0; i<b1; i++)
        printf("%f %f\n",X1[i],Y1[i]);
}
void calc2(int u, float theta)
{
    int i;
    theta = (theta*PI)/180;
    tof = 2*u*sin(theta)/g;
    float del_t = tof/b2;
    float temp=0;
    for(i=0; i<b2; i++)
    {
        x = u*cos(theta)*temp;
        y = u*sin(theta)*temp - ((g*temp*temp)/2);
        X2[i]=x-400;
        Y2[i]=y;
        temp += del_t;
    }
    for(i=0; i<b2; i++)
        printf("%f %f\n",X2[i],Y2[i]);
}
void update(int l) //update function pushes the frames ahead. Calls GlutPostRedisplay
{
    i++;
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}
void sq()
{
    glColor3f(0.0, 0.0, 1.0);
    glLineWidth(3.0);
    glBegin(GL_POLYGON);
    glVertex2d(0,50);
    glVertex2d(0,400);
    glVertex2d(400, 400);
    glVertex2d(200, 50);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_POLYGON);
    glVertex2d(243,128);
    glVertex2d(300,128);
    glVertex2d(250, 138);
    glVertex2d(300, 138);
    glEnd();

//glutSwapBuffers();
}


void wheel(int position)
{
    int j;
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);


    for( j=0; j<=360; ++j)
    {
        float deg=j*3.14/180;
        glVertex2f(position+cos(deg)*50,40+sin(deg)*50);
    }

    glEnd();
    glFlush();
//glutSwapBuffers();
}
void
display(void) //This function redraws the scene by creating the frames
{

    if(i<500)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 0.0);
        //calc(100,45);
//sq();
        repeated_draw();
        //calc(100,40);
        repeated_draw();
//sq();
    }
   // sq();
   // wheel(40);
   // wheel(200);
    glFlush();
    //man();
    glutSwapBuffers();

}
/* Called when window is resized,
also when window is first created,
before the first call to display(). */
void
reshape(int w, int h)
{
    /* save new screen dimensions */
    width = (GLdouble) w;
    height = (GLdouble) h;
    /* tell OpenGL to use the whole window for drawing */
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    /* do an orthographic parallel projection with the coordinate
    system set to first quadrant, limited by screen/window size */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, width, 0.0, height);
}
int main(int argc, char *argv[])
{
    u=90;
   // theta = (theta*PI)/180.00;
    calc1(100,45);
    calc2(100,45);
//scanf("%f %f", &u, &theta);
    init();
    //calc(100,45);
    glutInit(&argc, argv);
    /* specify the display to be single
    buffered and color as RGBA values */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    /* set the initial window size */
    glutInitWindowSize((int) width, (int) height);
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Club Penguin" /* title */ );
    /* --- register callbacks with GLUT --- */
    /* register function to handle window resizes */
    glutReshapeFunc(reshape);
    /* register function that draws in the window */
    glutDisplayFunc(display);
    /* start the GLUT main loop */
    glutTimerFunc(2, update, 0);
    glutMainLoop();
    return 0;
}
