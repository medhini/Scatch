#include <GL/glut.h>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>

using namespace std;


GLfloat xRotated, yRotated, zRotated, yTranslate, xTranslate,zTranslate=-2.0;
int flag=1;
GLdouble size=0.2;
GLdouble mov=0.005;
int windowWidth=800,windowHeight=800;

void onMouse(int button, int state, int x, int y);

void initSurface()
{
    GLfloat material_ambient[] = {0.25f, 0.25f, 0.25f};
    GLfloat material_diffuse[] = {0.90f, 0.90f, 0.90f};
    GLfloat material_specular[] = {0.90f, 0.90f, 0.90f};
    GLfloat material_shininess = 25.0f;

    /* load material properties */
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);
}
void initLights()
{
    /* define light properties */
    GLfloat light0_diffuse[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat light0_position[] = {0.0, 1.0, 0.0, 0.0};
    GLfloat light1_diffuse[] = {0.0, 0.0, 1.0, 1.0};
    GLfloat light1_position[] = {-0.866,-0.5, 0.0, 0.0};
    GLfloat light2_diffuse[]= {0.0,1.0,0.0,1.0};
    GLfloat light2_position[]={0.866,-0.5,0.0,0.0};

    /* enable lights 0 and 1*/
    glEnable(GL_LIGHTING);


// glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, 15.0f);
   // glEnable(GL_LIGHT0);
   // glEnable(GL_LIGHT1);
//glLightf (GL_LIGHT1, 10, 5.0f);

    /* load light properties */
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
     glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

}

void init()
{

    /* set the clear colour (R, G, B, A) */
    glClearColor(0.0, 0.0, 1.0, 1.0f);

    /* enable depth testing */
    glEnable(GL_DEPTH_TEST);

    /* enabled lighting */
    glEnable(GL_LIGHTING);

    /* initialise materials */
    initSurface();

    /* initialise lights */
    initLights();

    /* position and orient the camera */
    gluLookAt(0.0, 0.0, 10.0, /* eye point */
              0.0, 0.0, 0.0,  /* reference point */
              0.0, 1.0, 0.0); /* up vector */
}



void display(void)
{



    // glutSwapBuffers();

    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    // glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    // glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    // glEnable(GL_LIGHT1);
    glutMouseFunc(onMouse);
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(xTranslate,yTranslate,zTranslate);
    // Red color used to draw.
    glColor3f(0.0, 0.0, 1.0);
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
    glutSwapBuffers();
}

void reshapeFunc(int x, int y)
{

    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0


    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);

    glViewport(0,0,x,y);  //Use the whole window for rendering
}

void onMouse(int button, int state, int x, int y)
{

    if ((state != GLUT_DOWN) && ((button!=GLUT_LEFT_BUTTON)||(button!=GLUT_RIGHT_BUTTON)))
            return;

    if(state==GLUT_DOWN)
                if(button==GLUT_LEFT_BUTTON)
                            yTranslate+=0.05;
                else if(button==GLUT_RIGHT_BUTTON)
                        yTranslate-=0.05;


   // GLbyte color[4];

  //  glReadPixels(x, windowHeight - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    // glReadPixels(x, windowHeight + y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    //glReadPixels(x, windowHeight + y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    //cout<<"Clicked on pixel "<<x<<"\t"<<y<<"\nColor R = "<<(int)color[0]<<"\tG = "<< (int)color[1]<<"\tB = "<< (int)color[2]<<"\tA = "<< (int)color[3]<<endl;
    // move();
}
void idleFunc(void)
{

  //  xRotated+=0.5;
    //zRotated += 0.5;
    //yRotated+=0;

    //  yTranslate -=mov;
//



    display();
}

void specialin(int arkey,int x, int y)
{

    switch (arkey)
    {
            case GLUT_KEY_UP:
                                xRotated-=1.0;
                                break;

            case GLUT_KEY_DOWN:
                                xRotated+=1.0;
                                break;

            case GLUT_KEY_LEFT:
                                zRotated+=1.0;
                                break;

            case GLUT_KEY_RIGHT:
                                zRotated-=1.0;
                                break;


    }
}

int main (int argc, char **argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);


    //double buffering used to avoid flickering problem in animation
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH | GLUT_RGBA);
    // window size
    glutInitWindowSize(windowWidth,windowHeight);
    // create the window
    glutCreateWindow("Teapot Rotating Animation");
    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);

    init();
    //xRotated = 90.0;
    // zRotated =30;
    //zRotated = 0.0;
    /*xRotated=33;
     yRotated=40;
    */
    yTranslate = 0.0;
    xTranslate = 0.0;

    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_SMOOTH);
    //glEnable(GL_COLOR_MATERIAL);
    //Assign  the function used in events
    glutSpecialFunc(specialin);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFunc);
    glutIdleFunc(idleFunc);
    //Let start glut loop
    glutMainLoop();
    return 0;
}

