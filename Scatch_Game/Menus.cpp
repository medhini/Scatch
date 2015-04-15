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
#include "Update.h"
#include "Motion.h"

using namespace std;

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define NENDS 2

extern int Final_Score, Number_Of_Misses, Saved_Score;


void draw_pause_menu()
{
    string head = "GAME PAUSED";
    string head1 = "PRESS 'p' TO CONTINUE THE GAME";
    drawText(head.data(),550,710);
    drawText(head1.data(),410,500);

}
void exit_menu()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 0.0, 0.0, 0.0);

    glBegin(GL_LINE_STRIP);
        glVertex2d(420,700);
        glVertex2d(900,700);
        glVertex2d(900,730);
        glVertex2d(420,730);
        glVertex2d(420,700);
    glEnd();

    string head = "ARE YOU SURE YOU WANT TO QUIT?!?!?!";
    string head1 = "PRESS N TO CONTINUE THE GAME!";
    string head3 = "PRESS Y TO EXIT THE GAME";

    glBegin(GL_LINE_STRIP);
        glVertex2d(200,50);
        glVertex2d(1080,50);
        glVertex2d(1080,700);
        glVertex2d(200,700);
        glVertex2d(200,50);
    glEnd();

    drawText(head.data(),420,710);
    drawText(head1.data(),480,500);
    drawText(head3.data(),510,600);
}

void game_screen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.8, 0.6, 1.2, 0.0);

    projectile_motion();
    Truck();
    wheel(40);
    move_container();

    glBegin(GL_LINE_STRIP);
        glVertex2d(1000,600);
        glVertex2d(1180,600);
        glVertex2d(1180,700);
        glVertex2d(1000,700);
        glVertex2d(1000,600);
    glEnd();

    string head1="SCORE:";
    drawText(head1.data(),1020,670);

    stringstream string_score;
    string_score<<Final_Score;
    string head2 = string_score.str();
    drawText(head2.data(),1120,670);

    string head3="MISSES:";
    drawText(head3.data(),1020,620);

    stringstream string_miss;
    string_miss<<Number_Of_Misses;
    string head4 = string_miss.str();
    drawText(head4.data(),1140,620);

    glBegin(GL_LINE_STRIP);
        glVertex2d(800,600);
        glVertex2d(1000,600);
        glVertex2d(1000,700);
        glVertex2d(800,700);
        glVertex2d(800,600);
    glEnd();

    string head5 = "p -> PAUSE";
    string head6 = "ESC -> EXIT";

    drawText(head5.data(),805,670);
    drawText(head6.data(),805,620);

}
void menu_start()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 0.0, 0.0, 0.0);

    glBegin(GL_LINE_STRIP);
        glVertex2d(200,50);
        glVertex2d(1080,50);
        glVertex2d(1080,700);
        glVertex2d(200,700);
        glVertex2d(200,50);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glVertex2d(180,30);
        glVertex2d(1100,30);
        glVertex2d(1100,720);
        glVertex2d(180,720);
        glVertex2d(180,30);
    glEnd();

    string head = "CLUB PENGIUN";
    string head1 = "PRESS SPACEBAR TO PLAY!";
    string head2 = "INSTRUCTIONS";
    string head3 = "**CATCH THE RED TRIANGLES**";
    string head4 = "**DESTROY THE BLUE CIRCLES**";
    string head5 = "**A -> MOVE LEFT**";
    string head6 = "**D -> MOVE RIGHT**";
    string head7 = "**LEFT CLICK MOUSE TO DESTROY";
    string head8 = "THE BLUE  CIRCLES**";

    drawText(head.data(),550,700);
    drawText(head1.data(),520,100);
    drawText(head2.data(),550,650);

    glBegin(GL_LINE_STRIP);
        glVertex2d(400,400);
        glVertex2d(900,400);
        glVertex2d(900,600);
        glVertex2d(400,600);
        glVertex2d(400,400);
    glEnd();

    drawText(head3.data(),420,580);
    drawText(head4.data(),420,550);
    drawText(head5.data(),420,520);
    drawText(head6.data(),420,490);
    drawText(head7.data(),420,460);
    drawText(head8.data(),420,430);
}

void menu_game_over()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 0.0, 0.0, 0.0);

    glBegin(GL_LINE_STRIP);
        glVertex2d(200,50);
        glVertex2d(1080,50);
        glVertex2d(1080,700);
        glVertex2d(200,700);
        glVertex2d(200,50);
    glEnd();

    stringstream StreamScore;
    StreamScore<<Saved_Score;

    string head = "GAME OVER";
    string head1 = "PRESS SPACEBAR TO PLAY AGAIN!";
    string head2 = "PRESS ESC TO EXIT";
    string head3 = "SCORE : ";
    string head4 = StreamScore.str();
    string head5 = "GAME CREDITS : ";
    string head6 = "AKANKSHA KUMARI";
    string head7 = "SHREYA SINGH";
    string head8 = "SURYANSH D KUMAR";
    string head9 = "ANJAN RAGH";
    string head10 = "MEDHINI NARASIMHAN";

    drawText(head.data(),550,710);
    drawText(head1.data(),430,630);
    drawText(head2.data(),500,600);
    drawText(head3.data(),520,500);
    drawText(head4.data(),650,500);
    drawText(head5.data(),700,400);
    drawText(head6.data(),700,370);
    drawText(head7.data(),700,340);
    drawText(head8.data(),700,310);
    drawText(head9.data(),700,280);
    drawText(head10.data(),700,250);
}

