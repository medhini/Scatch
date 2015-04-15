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
#include "Declaration.h"

using namespace std;

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define NENDS 2

void drawText(char const *str,float x,float y)
{
    int i;
    int len=strlen(str);
    glColor3f(0.0,0.0,1.0);
    glRasterPos2f(x,y);

    for(i=0;i<len;i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
}
void Basket()
{
    glColor3f(0.0, 0.3, 0.5);
    glLineWidth(3.0);
    glBegin(GL_POLYGON);
        glVertex2d(550,0);
        glVertex2d(500,70);
        glVertex2d(650, 70);
        glVertex2d(600, 0);
    glEnd();
}
void red_triangle_draw()
{
    glLineWidth(3.0);
    glBegin(GL_POLYGON);
        glVertex2d(0,0);
        glVertex2d(25,43);
        glVertex2d(50, 0);
    glEnd();
}

void blue_circle_draw()
{
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);

     for(int j=0;j<=360;++j)
      {
        float deg=j*3.14/180;
        glVertex2f(cos(deg)*40,40+sin(deg)*40);
      }

    glEnd();
}

void Truck()
{
    glLineWidth(3.0);
    glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 0.3);
        glVertex2d(0,50);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2d(0,200);
        glColor3f(1.0, 1.0, 0.0);
        glVertex2d(200, 200);
        glColor3f(0.0, 0.0, 0.3);
        glVertex2d(100, 50);
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

}




