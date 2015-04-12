#include <GL/glut.h>

GLfloat xRotated=33.0, yRotated=40.0, zRotated=30.0, yTranslate=1.5, xTranslate = -1.5;
GLdouble size=0.2;


void createTeaPot(void)
{

    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(0.0, yTranslate, -4);
    // Red color used to draw.
    glColor3f(0.8, 0.2, 0.1);
    // changing in transformation matrix.
    // rotation about X axis
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);
    // scaling transfomation
    glScalef(1.0,1.0,1.0);
    // built-in (glut library) function , draw you a Teapot
    glutSolidTeapot(size);
    // Flush buffers to screen

    glFlush();
    // sawp buffers called because we are using double buffering
   // glutSwapBuffers();
}


