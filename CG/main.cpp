#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <GL/glew.h>
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define NENDS 2 /* number of end "points" to draw */
GLdouble width, height; /* window width and height */
int wd; /* GLUT window handle */
int ends[NENDS][2];
int i=0; /* array of 2D points */
float x, y, r=15, g=9.8, u, theta, ch1=0, ch2 = 0;
float tof;
float X[100],Y[100];
void calc(void);
float posX = 0, posY = 0, posZ = 0;
#define PI 3.14159265
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
glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
// Lighting set up
glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);

// Set lighting intensity and color
GLfloat qaAmbientLight[]	= {100, 100, 100, 1.0};
GLfloat qaDiffuseLight[]	= {0.8, 0.8, 0.8, 1.0};
GLfloat qaSpecularLight[]	= {1.0, 1.0, 1.0, 1.0};
glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

// Set the light position
GLfloat qaLightPosition[]	= {200, 40, 0, 1.0};
glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
glEnable(GL_DEPTH_TEST);
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
X[i]=x-600;
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
glColor3f(1.0, 0.0, 0.0);
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

void container(){
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_POLYGON);
    glVertex2d(550,0);
    glVertex2d(500,70);
    glVertex2d(650, 70);
    glVertex2d(600, 0);
    glEnd();
}
/*void processSpecialKeys (int key, int mx, int my) {
    switch(key){
    case GLUT_KEY_LEFT :
        if(x_container<400)
        x_container = x_container-5;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT :
        x_container = x_container+5;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}*/
void wheel(int position)
{
int j;
glColor3f(0.0, 0.0, 0.0);
glBegin(GL_POLYGON);


 for( j=0;j<=360;++j)
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
 glClear(GL_COLOR_BUFFER_BIT);
if(i<100)
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glClearColor(0.0,0.0, 1.0, 1.0);
//sq();
repeated_draw();
//sq();
}
sq();
wheel(40);
wheel(200);
glPushMatrix();
glTranslatef(posX, posY, posZ);
container();
glPopMatrix();
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
void keyboardown(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_RIGHT:
        posX += 5;
        break;
    case GLUT_KEY_LEFT:
        posX -= 5;
        break;
    default:
        break;
    }
glutPostRedisplay();
}
int
main(int argc, char *argv[])
{

u=150;
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
//keyboardListener();
//light();
/* register function that draws in the window */
glutDisplayFunc(display);
glutSpecialFunc(keyboardown);
/* start the GLUT main loop */
glutTimerFunc(25, update, 0);
glutMainLoop();
return 0;
}
