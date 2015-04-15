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
#include "Figures.h"
#include "Declaration.h"
#include "Motion.h"
#include "Menus.h"
#include "Update.h"
#include "Projectile.h"

using namespace std;

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define NENDS 2 /* number of end "points" to draw */
extern GLdouble width, height; /* window width and height */
extern int width_screen; /* GLUT window handle */

extern bool blue_clicked;
extern int game_state;
extern float Position_X_Basket;
extern float Basket_LEFT, Basket_RIGHT;


void readapixel(int x, int y)
{
 float color[3];
 glReadPixels(x, height - y - 1, 1, 1, GL_RGB, GL_FLOAT, color);
 cout<<"Clicked on pixel "<<x<<"\t"<<height - y<<"\nColor R = "<<color[0]<<"\tG = "<< color[1]<<"\tB = "<< color[2]<<"\tA = "<< color[3]<<endl;

    if(color[0]==0 && color[1]==0 && color[2]==1)
        blue_clicked = true;
}

void onMouse(int button, int state, int x, int y)
{
    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            if(state==GLUT_DOWN)
                {
                    readapixel(x,y);
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

void keyboardown(unsigned char key, int x, int y) {

    switch(game_state)
    {
        case 0:
            switch(key)
            {
                case ' ':
                    game_state=1;
                    break;
            }
            break;
        case 1:
            switch (key)
            {
                            case 'd':
                                Position_X_Basket = Position_X_Basket + 15;
                                Basket_LEFT = Basket_LEFT + 15;
                                Basket_RIGHT = Basket_RIGHT + 15;
                                //cout<<containerX<<" "<<containerY<<endl;
                                break;
                            case 'a':
                                Position_X_Basket = Position_X_Basket - 15;
                                Basket_LEFT = Basket_LEFT - 15;
                                Basket_RIGHT = Basket_RIGHT - 15;
                                //cout<<containerX<<" "<<containerY<<endl;
                                break;

                            case 'p' :
                                game_state=2;
                                break;

                            case 27 :
                                game_state=4;
                                break;
            }
            break;
        case 2 :
            switch(key)
            {
                case 'p' :
                        game_state=1;
                        break;
            }
            break;
        case 3 :
            switch(key)
            {
                case ' ':
                    game_state=1;
                    break;
                case 27 :
                    game_state=4;
                    break;
            }
            break;
        case 4 :
            switch(key)
            {
                case 'y':
                    exit(0);
                    break;
                case 'n':
                    game_state=1;
                    break;
            }
            break;
    }
}
