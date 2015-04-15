#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <sys/time.h>
#include <cstdlib>
#include <sstream>
#include<cstring>
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

extern int Angle_Of_Rotation;
extern int Red_Triangle_Counter_Variable, Blue_Circle_Counter_Variable;
extern int Red_Range, Blue_Range;
extern vector<int> max_distance;
extern int choose_path_blue, choose_path_red;
extern bool red_caught, blue_clicked;
extern int Number_Of_Misses,Final_Score, Saved_Score;
extern int game_state;

void Update_Angle_Of_Rotation()
{
    Angle_Of_Rotation = Angle_Of_Rotation + 10;
}

void choose_new_red_path()
{
    Red_Triangle_Counter_Variable=20;
    int k = rand()%5 + 1;
    switch(k)
    {
        case 1:
            Red_Range=max_distance[9];
            choose_path_red=1;
            break;

        case 2:
            Red_Range=max_distance[8];
            choose_path_red=2;
            break;

        case 3:
            Red_Range=max_distance[7];
            choose_path_red=3;
            break;

        case 4:
            Red_Range=max_distance[6];
            choose_path_red=4;
            break;

        case 5:
            Red_Range=max_distance[5];
            choose_path_red=5;
            break;
    }

    red_caught=false;
    Red_Triangle_Counter_Variable=20;
}

void choose_new_blue_path()
{
    Blue_Circle_Counter_Variable=20;
    int k = rand()%5 + 1;
    switch(k)
    {
        case 1:
            Blue_Range=max_distance[4];
            choose_path_blue=1;
            break;

        case 2:
            Blue_Range=max_distance[3];
            choose_path_blue=2;
            break;

        case 3:
            Blue_Range=max_distance[2];
            choose_path_blue=3;
            break;

        case 4:
            Blue_Range=max_distance[1];
            choose_path_blue=4;
            break;

        case 5:
            Blue_Range=max_distance[0];
            choose_path_blue=5;
            break;

    }
    blue_clicked=false;
    Blue_Circle_Counter_Variable=20;
}

void Update_Red_Path()
{

    if(Red_Triangle_Counter_Variable<Red_Range && red_caught==true)
    {
        choose_new_red_path();
        Final_Score+=10;
    }
    else if(Red_Triangle_Counter_Variable<Red_Range)
    {
        Red_Triangle_Counter_Variable++;
    }
    else
    {
        choose_new_red_path();
        Number_Of_Misses++;
    }
}

void Update_Blue_Path()
{
    if(Blue_Circle_Counter_Variable<Blue_Range && blue_clicked==true)
    {
        choose_new_blue_path();
        Final_Score+=20;
    }
    else if(Blue_Circle_Counter_Variable<Blue_Range)
    {
        Blue_Circle_Counter_Variable++;
    }
    else
    {
        choose_new_blue_path();
        Number_Of_Misses++;
    }
}

void Update_Game_State_Miss()
{

            if(Number_Of_Misses>30)
            {
                Saved_Score=Final_Score;
                Number_Of_Misses=0;
                Final_Score=0;
                game_state=3;
            }

}
