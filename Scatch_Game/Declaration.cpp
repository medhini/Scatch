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
//#include "Declaration.h"

using namespace std;

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define NENDS 2


GLdouble width, height; /* window width and height */
int width_screen; /* GLUT window handle */
int Ends[NENDS][2];

int Red_Triangle_Counter_Variable=20, Blue_Circle_Counter_Variable=20;
int Final_Score=0, Saved_Score=0, Number_Of_Misses=0;
float Basket_LEFT=500, Basket_RIGHT=650;


int Angle_Of_Rotation=0;
bool blue_clicked=false;
bool red_caught=false;

float Position_X_Basket=0;

int game_state=0;

extern GLfloat xRotated, yRotated, zRotated, yTranslate, xTranslate;

//Path Values
int Red_Range, Blue_Range;
int choose_path_red=1, choose_path_blue=1;
vector <int> max_distance;

//Path Coordinates

pair <float, float> Red_Path1[500];
pair <float, float> Red_Path2[500];
pair <float, float> Red_Path3[500];
pair <float, float> Red_Path4[500];
pair <float, float> Red_Path5[500];
pair <float, float> Blue_Path1[500];
pair <float, float> Blue_Path2[500];
pair <float, float> Blue_Path3[500];
pair <float, float> Blue_Path4[500];
pair <float, float> Blue_Path5[500];






