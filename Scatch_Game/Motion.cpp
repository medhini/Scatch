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

using namespace std;

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define NENDS 2

extern pair <float, float> Red_Path1[500];
extern pair <float, float> Red_Path2[500];
extern pair <float, float> Red_Path3[500];
extern pair <float, float> Red_Path4[500];
extern pair <float, float> Red_Path5[500];
extern pair <float, float> Blue_Path1[500];
extern pair <float, float> Blue_Path2[500];
extern pair <float, float> Blue_Path3[500];
extern pair <float, float> Blue_Path4[500];
extern pair <float, float> Blue_Path5[500];

extern int Red_Triangle_Counter_Variable, Blue_Circle_Counter_Variable;
extern int choose_path_red, choose_path_blue;
extern float Basket_LEFT, Basket_RIGHT;
extern bool red_caught, blue_clicked;
extern int Angle_Of_Rotation;
extern float Position_X_Basket;

void projectile_motion() //Animation of Triangles and Circles
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch(choose_path_red)
       {
            case 1:

                glPushMatrix();
                glTranslatef(Red_Path1[Red_Triangle_Counter_Variable].first, Red_Path1[Red_Triangle_Counter_Variable].second,0);

                if(Red_Path1[Red_Triangle_Counter_Variable].second>=67 && Red_Path1[Red_Triangle_Counter_Variable].second<=75.1 )
                {
                    if(Red_Path1[Red_Triangle_Counter_Variable].first>Basket_LEFT && Red_Path1[Red_Triangle_Counter_Variable].first<Basket_RIGHT)
                        red_caught=true;
                }
                glRotatef(Angle_Of_Rotation,0.0,0.0,1.0);
                glTranslatef(-25,-14,0);
                glColor3f(1.0, 0.0, 0.0);
                red_triangle_draw();
            glPopMatrix();
            break;

            case 2:

            glPushMatrix();
                glTranslatef(Red_Path2[Red_Triangle_Counter_Variable].first, Red_Path2[Red_Triangle_Counter_Variable].second,0);

                if(Red_Path2[Red_Triangle_Counter_Variable].second>=67 && Red_Path2[Red_Triangle_Counter_Variable].second<=75.1 )
                {
                    if(Red_Path2[Red_Triangle_Counter_Variable].first>Basket_LEFT && Red_Path2[Red_Triangle_Counter_Variable].first<Basket_RIGHT )
                        red_caught=true;
                }
                glRotatef(Angle_Of_Rotation,0.0,0.0,1.0);
                glTranslatef(-25,-14,0);
                glColor3f(1.0, 0.0, 0.0);
                red_triangle_draw();
            glPopMatrix();
            break;

            case 3:
            glPushMatrix();
                glTranslatef(Red_Path3[Red_Triangle_Counter_Variable].first, Red_Path3[Red_Triangle_Counter_Variable].second,0);
                if(Red_Path3[Red_Triangle_Counter_Variable].second>=67 && Red_Path3[Red_Triangle_Counter_Variable].second<=75.1  )
                {
                    if(Red_Path3[Red_Triangle_Counter_Variable].first>Basket_LEFT && Red_Path3[Red_Triangle_Counter_Variable].first<Basket_RIGHT)
                        red_caught=true;
                }
                glRotatef(Angle_Of_Rotation,0.0,0.0,1.0);
                glTranslatef(-25,-14,0);
                glColor3f(1.0, 0.0, 0.0);
                red_triangle_draw();
            glPopMatrix();
            break;

            case 4:
            glPushMatrix();
                glTranslatef(Red_Path4[Red_Triangle_Counter_Variable].first, Red_Path4[Red_Triangle_Counter_Variable].second,0);
                if(Red_Path4[Red_Triangle_Counter_Variable].second>=67 && Red_Path4[Red_Triangle_Counter_Variable].second<=75.1 )
                {
                    if(Red_Path4[Red_Triangle_Counter_Variable].first>Basket_LEFT && Red_Path4[Red_Triangle_Counter_Variable].first<Basket_RIGHT )
                        red_caught=true;
                }
                glRotatef(Angle_Of_Rotation,0.0,0.0,1.0);
                glTranslatef(-25,-14,0);
                glColor3f(1.0, 0.0, 0.0);
                red_triangle_draw();
            glPopMatrix();
            break;

            case 5:
            glPushMatrix();
                glTranslatef(Red_Path5[Red_Triangle_Counter_Variable].first, Red_Path5[Red_Triangle_Counter_Variable].second,0);
                if(Red_Path5[Red_Triangle_Counter_Variable].second>=67 && Red_Path5[Red_Triangle_Counter_Variable].second<=75.1)
                {
                    if(Red_Path5[Red_Triangle_Counter_Variable].first>Basket_LEFT && Red_Path5[Red_Triangle_Counter_Variable].first<Basket_RIGHT )
                       red_caught=true;
                }
                glRotatef(Angle_Of_Rotation,0.0,0.0,1.0);
                glTranslatef(-25,-14,0);
                glColor3f(1.0, 0.0, 0.0);
                red_triangle_draw();
            glPopMatrix();
            break;

    }

    switch(choose_path_blue)
        {
            case 1:
            glPushMatrix();
                glTranslatef(Blue_Path1[Blue_Circle_Counter_Variable].first, Blue_Path1[Blue_Circle_Counter_Variable].second,0);
                glTranslatef(-25,-14,0);
                glColor3f(0.0, 0.0, 1.0);
                blue_circle_draw();
            glPopMatrix();
            break;

            case 2:
            glPushMatrix();
                glTranslatef(Blue_Path2[Blue_Circle_Counter_Variable].first, Blue_Path2[Blue_Circle_Counter_Variable].second,0);
                glTranslatef(-25,-14,0);
                glColor3f(0.0, 0.0, 1.0);
                blue_circle_draw();
            glPopMatrix();
            break;

            case 3:
            glPushMatrix();
                glTranslatef(Blue_Path3[Blue_Circle_Counter_Variable].first, Blue_Path3[Blue_Circle_Counter_Variable].second,0);
                glTranslatef(-25,-14,0);
                glColor3f(0.0, 0.0, 1.0);
                blue_circle_draw();
            glPopMatrix();
            break;

            case 4:
            glPushMatrix();
                glTranslatef(Blue_Path4[Blue_Circle_Counter_Variable].first, Blue_Path4[Blue_Circle_Counter_Variable].second,0);
                glTranslatef(-25,-14,0);
                glColor3f(0.0, 0.0, 1.0);
                blue_circle_draw();
            glPopMatrix();
            break;

            case 5:

            glPushMatrix();
                glTranslatef(Blue_Path5[Blue_Circle_Counter_Variable].first, Blue_Path5[Blue_Circle_Counter_Variable].second,0);
                glTranslatef(-25,-14,0);
                glColor3f(0.0, 0.0, 1.0);
                blue_circle_draw();
            glPopMatrix();
            break;
        }
}

void move_container()
{
    glPushMatrix();
        glTranslatef(Position_X_Basket, 0, 0);
        Basket();
    glPopMatrix();
}



