#include <GL/glut.h>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>

using namespace std;


GLfloat xRotated, yRotated, zRotated, yTranslate, xTranslate,zTranslate=-10.0;
//Variables used to track rotation about the coordinate axes, and translation along the axes from the origin


int flag=1,rflag=0,bflag=0,gflag=0;  //flags for turning lights and rotation on an off

int windowWidth=1000,windowHeight=1000;

void onMouse(int button, int state, int x_clicked, int y_clicked); //Registering Mouse Function

void initSurface()
{
    GLfloat material_ambient[] = {0.25f, 0.25f, 0.25f};
    GLfloat material_diffuse[] = {0.90f, 0.90f, 0.90f};
    GLfloat material_specular[] = {0.90f, 0.90f, 0.90f};
    GLfloat material_shininess = 25.0f;

   glShadeModel(GL_SMOOTH);     //Set shading

    /* load material properties */
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);
}
void initLights()
{
     /* define light properties : Diffuse to se the RGBA values of the lights
                                : Position to assign the xyz coordinates of the lights */
    GLfloat light0_diffuse[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat light0_position[] = {0.0, 1.0, 0.0, 0.0};
    GLfloat light1_diffuse[] = {0.0, 0.0, 1.0, 1.0};
    GLfloat light1_position[] = {-0.866,-0.5, 0.0, 0.0};
    GLfloat light2_diffuse[]= {0.0,1.0,0.0,1.0};
    GLfloat light2_position[]={0.866,-0.5,0.0,0.0};

    /* enable lights 0 and 1*/
    glEnable(GL_LIGHTING);

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


void drawText(const char *text, int length,int x_position,int y_position,int type_of_data)
//Function to Draw text on the screen

{
glMatrixMode(GL_PROJECTION);
double *matrix=new double[16];
glGetDoublev(GL_PROJECTION_MATRIX,matrix);
glLoadIdentity();
glOrtho(0,500,0,600,-5,5);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glPushMatrix();
glLoadIdentity();
glRasterPos2i(x_position,y_position);

if(type_of_data==1)
{
    for(int i=0;i<length;i++)
    {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,(int)text[i]);
    }


}

else
{
    for(int i=0;i<length;i++)
    {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,(int)text[i]);
    }


}


glPopMatrix();
glMatrixMode(GL_PROJECTION);
glLoadMatrixd(matrix);
glMatrixMode(GL_MODELVIEW);

}
void display(void)   //The main display fumction
{

    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear buffers

    glLoadIdentity();  // clear the identity matrix.

    glutMouseFunc(onMouse);

    glTranslatef(xTranslate,yTranslate,zTranslate); // traslate the 3d object by x,y and z

    glColor3f(0.0, 0.0, 1.0);


    glRotatef(xRotated,1.0,0.0,0.0);  // rotation about X axis

    glRotatef(yRotated,0.0,1.0,0.0);// rotation about Y axis

    glRotatef(zRotated,0.0,0.0,1.0);  // rotation about Z axis

    glScalef(1.0,1.0,1.0);       // scaling transfomation

   glutSolidDodecahedron(); // built-in (glut library) function , draws a Dodecahedron



     string text1="TEAPOT ANIMATION";
     string text2="Use W A S D for Horizontal movement";
     string text3="Use R G B to switch lights on and off";
     string text4 ="Use Arrow keys to rotate about X and Z axes";
     string text5="Press Y to turn rotation about Y-axis on and off";
     string text6="Use right and left clicks for vertical movement";

        drawText(text1.data(),text1.size(),190,500,1);
        drawText(text2.data(),text2.size(),10,100,0);
        drawText(text3.data(),text3.size(),10,90,0);
        drawText(text4.data(),text4.size(),10,80,0);		//Instructions to be printed on screen
        drawText(text5.data(),text5.size(),10,70,0);
        drawText(text6.data(),text6.size(),10,60,0);



            glFlush(); 						// Flush buffers to screen

            glutSwapBuffers();           			 // swap buffers called because we are using double buffering
        }

void reshapeFunc(int x, int y)
{

    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);

    glViewport(0,0,x,y);  //Use the whole window for rendering
}

void onMouse(int button, int state, int x, int y)
{

    if ((state != GLUT_DOWN) && ((button!=GLUT_LEFT_BUTTON)||(button!=GLUT_RIGHT_BUTTON)))
            return;  //Returns if function is called when mouse click has not occured

    if(state==GLUT_DOWN)
                if(button==GLUT_LEFT_BUTTON)
                            yTranslate+=0.05;  		 //Move vertically up on left click
                else if(button==GLUT_RIGHT_BUTTON)
                        yTranslate-=0.05;     		//Move vertically down on right click





}
void idleFunc(void)
{



    if(flag)
            yRotated+=1.5;		 //Rotate about y-axis if flag is true
    if(rflag)
            glEnable(GL_LIGHT0);         //Enable red lights
    else
            glDisable(GL_LIGHT0);      //Disable red lights
    if(bflag)
            glEnable(GL_LIGHT1);       //Enable blue lights
    else
            glDisable(GL_LIGHT1);     //Disable blue lights
    if(gflag)
            glEnable(GL_LIGHT2);     //Enable green lights
    else
            glDisable(GL_LIGHT2);    //Disable green lights




    display();
}
void keyboard(unsigned char k, int x, int y)
{
    switch (k)
    {

             case 'w': zTranslate-=0.05;
                            break;         //Move forwards

            case 'a':   xTranslate-=0.05;
                        break;   	   //Move left

            case 's':   zTranslate+=0.05;
	                 break;		   //Move backwards

            case 'd':   xTranslate+=0.05;
                            break; 	   //Move right

            case 'r':
                        if(rflag==1)
                            rflag=0;
                        else
                            rflag=1;

                        break;
            case 'b':
                         if(bflag==1)
                            bflag=0;
                        else		    //Switching lights on and off
                            bflag=1;
                        break;

            case 'g':
                       if(gflag==1)
                            gflag=0;
                        else
                            gflag=1;
                        break;

            case 'y':
                        if(flag==1)
                                flag=0;
                        else flag=1;	  //Switching rotation about y axix on and off
                        break;
            default : break;


    }

}

void arrow_key(int arkey,int x, int y)
{

    switch (arkey)
    {
            case GLUT_KEY_UP:
                                xRotated-=1.0;
                                break;

            case GLUT_KEY_DOWN:				 //Rotate about x axis
                                xRotated+=1.0;
                                break;

            case GLUT_KEY_LEFT:
                                zRotated+=1.0;
                                break;

            case GLUT_KEY_RIGHT:			//Rotate about z axis

                                zRotated-=1.0;
                                break;


    }
}


int main (int argc, char **argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);



    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH | GLUT_RGBA); //double buffering used to avoid flickering problem in animation

    glutInitWindowSize(windowWidth,windowHeight);  // window size

    glutCreateWindow("Teapot Rotating Animation");  // create the window
    glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);		//Set cursor style

    init();

    yTranslate = 0.0;		//Placing object at origin
    xTranslate = 0.0;

    glClearColor(0.0,0.0,0.0,0.0);  //Setting background colour

    //Assign  the function used in events
    glutSpecialFunc(arrow_key);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFunc);
    glutIdleFunc(idleFunc);
    //Let start glut loop
    glutMainLoop();
    return 0;
}
