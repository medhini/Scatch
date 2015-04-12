#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "Projectile.h"
#include "Figures.h"
//#include "Declaration.h"

using namespace std;

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define NENDS 2 /* number of end "points" to draw */
GLdouble width, height; /* window width and height */
int wd; /* GLUT window handle */
int eands[NENDS][2];
int i=0, count_red=20, count_blue=20, score=0; /* array of 2D points */
float x, y, r=15, u, theta, angle=0, ch1=0, ch2 = 0, chosenY=0, chosenX=0, containerX=500, containerY=650;
float tof;
float X[100],Y[100];
void calc(void);
float posX = 0, posY = 0, posZ = 0;

extern GLfloat xRotated, yRotated, zRotated, yTranslate, xTranslate;

#define PI 3.14159265

int recordX[1000]={}, recordY[1000]={};
extern pair <int, int> Red_Path1[500];
extern pair <int, int> Red_Path2[500];
extern pair <int, int> Red_Path3[500];
extern pair <int, int> Red_Path4[500];
extern pair <int, int> Red_Path5[500];
extern pair <int, int> Blue_Path1[500];
extern pair <int, int> Blue_Path2[500];
extern pair <int, int> Blue_Path3[500];
extern pair <int, int> Blue_Path4[500];
extern pair <int, int> Blue_Path5[500];

extern vector <int> max_distance;

int temp1;
int temp2;
int choose_path_red=1, choose_path_blue=1;
//vector <float> u;

/* Program initialization NOT OpenGL/GLUT dependent,
as we haven't created a GLUT window yet */
void init(void)
{
    width = 1280.0; /* initial window width and height, */
    height = 800.0; /* within which we draw. */
    eands[0][0] = (int)(0.0*width); /* (0,0) is the lower left corner */
    eands[0][1] = (int)(1.0*height);
    eands[1][0] = (int)(1.0*width);
    eands[1][1] = (int)(0.0*height);
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

void triangle_draw()
{
    glLineWidth(3.0);
    glBegin(GL_POLYGON);
       // glColor3f(0.0, 1.0, 0.0);
        glVertex2d(0,0);
       // glColor3f(1.0, 0.0, 0.0);
        glVertex2d(25,43);
      //  glColor3f(0.0, 0.0, 1.0);
        glVertex2d(50, 0);
    glEnd();
}
void repeated_draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch(choose_path_red)
       {
            case 1:

            glPushMatrix();
                glTranslatef(Red_Path1[count_red].first, Red_Path1[count_red].second,0);

                //cout<<Red_Path1[count_red].first<<" "<<Red_Path1[count_red].second<<endl;
                chosenY=Red_Path1[count_red].second;
                glRotatef(angle,0.0,0.0,1.0);
                glTranslatef(-25,-14,0);
                glColor3f(1.0, 0.0, 0.0);
                triangle_draw();
            glPopMatrix();
            break;

            case 2:

            glPushMatrix();
                glTranslatef(Red_Path2[count_red].first, Red_Path2[count_red].second,0);

               // cout<<Red_Path2[count_red].first<<" "<<Red_Path2[count_red].second<<endl;
                chosenY=Red_Path2[count_red].second;
                glRotatef(angle,0.0,0.0,1.0);
                glTranslatef(-25,-14,0);
                glColor3f(1.0, 0.0, 0.0);
                triangle_draw();
            glPopMatrix();
            break;

            case 3:
            glPushMatrix();
                glTranslatef(Red_Path3[count_red].first, Red_Path3[count_red].second,0);

                //cout<<Red_Path3[count_red].first<<" "<<Red_Path3[count_red].second<<endl;
                chosenY=Red_Path3[count_red].second;
                glRotatef(angle,0.0,0.0,1.0);
                glTranslatef(-25,-14,0);
                glColor3f(1.0, 0.0, 0.0);
                triangle_draw();
            glPopMatrix();
            break;

            case 4:
            glPushMatrix();
                glTranslatef(Red_Path4[count_red].first, Red_Path4[count_red].second,0);

               // cout<<Red_Path4[count_red].first<<" "<<Red_Path4[count_red].second<<endl;
                chosenY=Red_Path4[count_red].second;
                glRotatef(angle,0.0,0.0,1.0);
                glTranslatef(-25,-14,0);
                glColor3f(1.0, 0.0, 0.0);
                triangle_draw();
            glPopMatrix();
            break;

            case 5:
            glPushMatrix();
                glTranslatef(Red_Path5[count_red].first, Red_Path5[count_red].second,0);

              //  cout<<Red_Path5[count_red].first<<" "<<Red_Path5[count_red].second<<endl;
                chosenY=Red_Path5[count_red].second;
                glRotatef(angle,0.0,0.0,1.0);
                glTranslatef(-25,-14,0);
                glColor3f(1.0, 0.0, 0.0);
                triangle_draw();
            glPopMatrix();
            break;

    }

    switch(choose_path_blue)
        {
            case 1:
            glPushMatrix();
                glTranslatef(Blue_Path1[count_blue].first, Blue_Path1[count_blue].second,0);
                glRotatef(angle,0.0,0.0,1.0);
                glTranslatef(-25,-14,0);
                glColor3f(0.0, 0.0, 1.0);
                triangle_draw();
            glPopMatrix();
            break;

            case 2:
            glPushMatrix();
                glTranslatef(Blue_Path2[count_blue].first, Blue_Path2[count_blue].second,0);
                glRotatef(angle,0.0,0.0,1.0);
                glTranslatef(-25,-14,0);
                glColor3f(0.0, 0.0, 1.0);
                triangle_draw();
            glPopMatrix();
            break;

            case 3:
            glPushMatrix();
                glTranslatef(Blue_Path3[count_blue].first, Blue_Path3[count_blue].second,0);
                glRotatef(angle,0.0,0.0,1.0);
                glTranslatef(-25,-14,0);
                glColor3f(0.0, 0.0, 1.0);
                triangle_draw();
            glPopMatrix();
            break;

            case 4:
            glPushMatrix();
                glTranslatef(Blue_Path4[count_blue].first, Blue_Path4[count_blue].second,0);
                glRotatef(angle,0.0,0.0,1.0);
                glTranslatef(-25,-14,0);
                glColor3f(0.0, 0.0, 1.0);
                triangle_draw();
            glPopMatrix();
            break;

            case 5:

            glPushMatrix();
                glTranslatef(Blue_Path5[count_blue].first, Blue_Path5[count_blue].second,0);
                glRotatef(angle,0.0,0.0,1.0);
                glTranslatef(-25,-14,0);
                glColor3f(0.0, 0.0, 1.0);
                triangle_draw();
            glPopMatrix();
            break;
        }
}
void find_chosenX(int path)
{
    switch(path)
    {
        case 1:
                for(int i=0; i<max_distance[9]; i++)
                {
                    if(Red_Path1[i].second>=67 && Red_Path1[i].second<=73 && Red_Path1[i].second<Red_Path1[i-1].second)
                    {
                        chosenX=Red_Path1[i].first;
                        break;
                    }
                }
                break;
        case 2:
                for(int i=0; i<max_distance[8]; i++)
                {
                    if(Red_Path2[i].second>=67 && Red_Path2[i].second<=73 && Red_Path2[i].second<Red_Path2[i-1].second)
                    {
                        chosenX=Red_Path2[i].first;
                        break;
                    }
                }
                break;

        case 3:
                for(int i=0; i<max_distance[7]; i++)
                {
                    if(Red_Path3[i].second>=67 && Red_Path3[i].second<=73 && Red_Path3[i].second<Red_Path3[i-1].second)
                    {
                        chosenX=Red_Path3[i].first;
                        break;
                    }
                }
                break;

        case 4:
                for(int i=0; i<max_distance[6]; i++)
                {
                    if(Red_Path4[i].second>=67 && Red_Path4[i].second<=73 && Red_Path4[i].second<Red_Path4[i-1].second)
                    {
                        chosenX=Red_Path4[i].first;
                        break;
                    }
                }
                break;

        case 5:
                for(int i=0; i<max_distance[5]; i++)
                {
                    if(Red_Path5[i].second>=67 && Red_Path5[i].second<=73 && Red_Path5[i].second<Red_Path5[i-1].second)
                    {
                        chosenX=Red_Path5[i].first;
                        break;
                    }
                }
                break;
    }
}
void choose_new_red_path()
{
    count_red=20;
    chosenY=0;
    int k = rand()%5 + 1;
    switch(k)
    {
        case 1:
            temp1=max_distance[9];
            choose_path_red=1;
            find_chosenX(1);
            break;
        case 2:
            temp1=max_distance[8];
            choose_path_red=2;
            find_chosenX(2);
            break;

        case 3:
            temp1=max_distance[7];
            choose_path_red=3;
            find_chosenX(3);
            break;

        case 4:
            temp1=max_distance[6];
            choose_path_red=4;
            find_chosenX(4);
            break;
        case 5:
            temp1=max_distance[5];
            choose_path_red=5;
            find_chosenX(5);
            break;
    }
    chosenY=0;
    count_red=20;
}
int check_visited=0;
void update(int l) //update function pushes the frames ahead. Calls GlutPostRedisplay
{
    angle+=10;

    if(count_red<temp1)
        count_red++;
    else
        choose_new_red_path();

    if(chosenY>=64 && chosenY<=76)
    {
        if(chosenX>=containerX && chosenX<=containerY)
        {
            choose_new_red_path();
            score+=10;
        }

        cout<<score<<endl;
        cout<<chosenX<<" "<<containerX<<" "<<containerY<<endl;
    }

    if(count_blue<temp2)
        count_blue++;

    else
    {
        count_blue=20;
        int k = rand()%5 + 1;
        switch(k)
        {
            case 1:
                temp2=max_distance[4];
                choose_path_blue=1;
                break;
            case 2:
                temp2=max_distance[3];
                //color='b';
                choose_path_blue=2;
                break;
            case 3:
                temp2=max_distance[2];
               // color='b';
                choose_path_blue=3;
                break;
            case 4:
                temp2=max_distance[1];
               // color='b';
                choose_path_blue=4;
                break;
            case 5:
                temp2=max_distance[0];
               // color='b';
                choose_path_blue=5;
                break;

        }
    }

    yRotated += 0.1;

    if(yTranslate>-1.5)
        yTranslate -= 0.001;
    else
    {
        yTranslate = 4.5;
        xTranslate = 0.02;
    }

    glutPostRedisplay();
    glutTimerFunc(25, update, l);
}
void sq()
{
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_POLYGON);
        glVertex2d(0,50);
        glVertex2d(0,150);
        glVertex2d(150, 150);
        glVertex2d(75, 50);
    glEnd();
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

void wheel(int position)
{
int j;
glColor3f(0.0, 0.0, 0.0);
glBegin(GL_POLYGON);


 for( j=0;j<=360;++j)
  {
    float deg=j*3.14/180;
    glVertex2f(position+cos(deg)*40,40+sin(deg)*40);
  }

glEnd();
//glFlush();
//glutSwapBuffers();
}

void move_container()
{
    glPushMatrix();
        glTranslatef(posX, posY, posZ);
        container();
    glPopMatrix();
}
void display(void) //This function redraws the scene by creating the frames
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);

    gluOrtho2D(0.0, width, 0.0, height);
    repeated_draw();
    sq();
    wheel(40);
    move_container();

    //gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);

   // glViewport(0,0,x,y);
    //createTeaPot();
    glFlush();
    glutSwapBuffers();

}
/* Called when window is resized,
also when window is first created,
before the first call to display(). */
void reshape(int w, int h)
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



}
void keyboardown(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_RIGHT:
        posX += 15;
        containerX+=15;
        containerY+=15;
        break;
    case GLUT_KEY_LEFT:
        posX -= 15;
        containerX-=15;
        containerY-=15;
        break;
    default:
        break;
    }
}
void glutPassiveMotionFunc(void (*func)(int x, int y));
void mouse(int button, int state, int x, int y)
{
    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            if(state==GLUT_DOWN)
                {

                }
            break;

        case GLUT_RIGHT_BUTTON:
            if(state==GLUT_DOWN)
                exit(0);
            break;

        default:
            break;
    }
}
int
main(int argc, char *argv[])
{

Generate_U_Theta();

temp1 = max_distance[9];
temp2 = max_distance[5];

find_chosenX(1);
init();
glutInit(&argc, argv);
/* specify the display to be single
buffered and color as RGBA values */
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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
//glutPassiveMotionFunc()
glutMouseFunc(mouse);
/* start the GLUT main loop */
glutTimerFunc(100, update, 0);
glutMainLoop();
return 0;
}
