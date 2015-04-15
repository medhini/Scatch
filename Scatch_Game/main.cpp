#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <sys/time.h>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "Projectile.h"
#include "Callbacks.h"
#include "Figures.h"
#include "Declaration.h"
#include "Motion.h"
#include "Menus.h"
#include "Update.h"

using namespace std;

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define NENDS 2 /* number of end "points" to draw */

extern GLdouble width, height;
extern int Ends[NENDS][2];
extern int game_state;
extern int Red_Range, Blue_Range;
extern vector <int> max_distance;
extern int width_screen;

extern bool blue_clicked;
extern int game_state;


/* Program initialization NOT OpenGL/GLUT dependent,
as we haven't created a GLUT window yet */
void init(void)
{
    width = 1280.0; /* initial window width and height, */
    height = 800.0; /* within which we draw. */
    Ends[0][0] = (int)(0.0*width); /* (0,0) is the lower left corner */
    Ends[0][1] = (int)(1.0*height);
    Ends[1][0] = (int)(1.0*width);
    Ends[1][1] = (int)(0.0*height);

}

void timer_func(int l)
{
    if(game_state==1)
    {
        Update_Angle_Of_Rotation();
        Update_Blue_Path();
        Update_Red_Path();
        Update_Game_State_Miss();
    }

    glutPostRedisplay();
    glutTimerFunc(25, timer_func, l);

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
    gluOrtho2D(0.0, width, 0.0, height);

}

void Main_Display(void)
{
    switch(game_state)
    {
        case 0 :
            menu_start();
            break;
        case 1 :
            game_screen();
            break;
        case 2 :
            draw_pause_menu();
            break;
        case 3 :
            menu_game_over();
            break;
        case 4 :
            exit_menu();
            break;
    }
    glFlush();
    glutSwapBuffers();
}
int main(int argc, char *argv[])
{

    Generate_U_Theta();

    Red_Range = max_distance[9];
    Blue_Range = max_distance[5];

    init();
    glutInit(&argc, argv);
    /* specify the display to be single
    buffered and color as RGBA values */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    /* set the initial window size */
    glutInitWindowSize((int) width, (int) height);
    /* create the window and store the handle to it */
    width_screen = glutCreateWindow("Scatch" /* title */ );
    glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
    /* --- register callbacks with GLUT --- */
    /* register function to handle window resizes */
    glutReshapeFunc(reshape);

    /* register function that draws in the window */

    glutDisplayFunc(Main_Display);
    glutKeyboardFunc(keyboardown);

    glutMouseFunc(onMouse);
    /* start the GLUT main loop */
    glutTimerFunc(25, timer_func, 0);
    glutMainLoop();
    return 0;
}
