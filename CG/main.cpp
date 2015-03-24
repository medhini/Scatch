#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define NENDS 2           /* number of end "points" to draw */
GLdouble width, height;   /* window width and height */
int wd;                   /* GLUT window handle */
int ends[NENDS][2];
int i=0;  /* array of 2D points */
float x, y, r=15, g=9.8, u, theta, ch1=0, ch2 = 0;
float tof;
float X[100],Y[100];
void calc(void);
#define PI 3.14159265
/* Program initialization NOT OpenGL/GLUT dependent,
   as we haven't created a GLUT window yet */
void init(void)
{
    width  = 1280.0;                 /* initial window width and height, */
    height = 800.0;                  /* within which we draw. */
    ends[0][0] = (int)(0.0*width);  /* (0,0) is the lower left corner */
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

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_POINTS);

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
    glTranslatef(X[i],Y[i],0);
    circle_draw();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();

}

void calc(void)
{
    int i;
    tof = 2*u*sin(theta)/g;
    float del_t = tof/100;
    float temp=0;
    for(i=0; i<100; i++)
    {
        x = u*cos(theta)*temp;
        y = u*sin(theta)*temp - ((g*temp*temp)/2);
        X[i]=x-100;
        Y[i]=y;
        temp += del_t;
    }
    for(i=0; i<100; i++)
        printf("%f %f\n",X[i],Y[i]);
}

void update(int l) //update function pushes the frames ahead. Calls GlutPostRedisplay
{
    i++;

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}
void sq()
{
    glColor3f(0.0, 0.0, 0.0);
        glLineWidth(3.0);
        glBegin(GL_LINE_LOOP);

        glVertex2d(0,0);
        glVertex2d(0,400);
        glVertex2d(400, 400);
        glVertex2d(400, 0);

        glEnd();
        glutSwapBuffers();
}
void
display(void) //This function redraws the scene by creating the frames
{
      if(i<100)
      {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(1.0, 1.0, 1.0, 0.0);

        //sq();

        repeated_draw();
        sq();
    }

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

int
main(int argc, char *argv[])
{
    u=100;
    theta = 4.5;
    calc();
    //scanf("%f %f", &u, &theta);


    init();
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
    glutTimerFunc(25, update, 0);
    glutMainLoop();

    return 0;
}
