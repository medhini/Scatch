//ScanLine Algorithm
/*
 * Copyright (c) 2009 University of Michigan, Ann Arbor.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of Michigan, Ann Arbor. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Authors: Manoj Rajagopalan, Sugih Jamin
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define NENDS 2           /* number of end "points" to draw */

GLdouble width, height;   /* window width and height */
int wd;                   /* GLUT window handle */
int ends[NENDS][2];       /* array of 2D points */

/* Program initialization NOT OpenGL/GLUT dependent,
   as we haven't created a GLUT window yet */

struct line
  {
    int x1, x2, y1, y2;

    int x1clip, x2clip, y1clip, y2clip;

    int dx, dy;

    int edgeLeft, edgeRight, edgeBottom, edgeTop;

  }newline;

void
init(void)
{
  width  = 1080.0;                 /* initial window width and height, */
  height = 1000.0;                  /* within which we draw. */
  ends[0][0] = (int)(0.25*width);  /* (0,0) is the lower left corner */
  ends[0][1] = (int)(0.75*height);
  ends[1][0] = (int)(0.75*width);
  ends[1][1] = (int)(0.25*height);

}

void circle(int x, int y, int r)
{
 glColor3f(0.0, 5.0, 0.0);

  glBegin(GL_POINTS);

  int h = 1-r;
  int x0 = 0, y0 = r;

  double end = r/(sqrt(2));


  while(x0<=end)
  {
    if(h<=0)
    {
        h += 2*x0 + 3;
	printf("Chosen east\n");
    }
    else
    {
        h += 2*x0 - 2*y0 + 5;
        y0--;
	printf("Chosen southeast\n");
    }
    x0++;

    glVertex2d(x + x0, y + y0);
    glVertex2d(x + x0, y - y0);
    glVertex2d(x - x0, y - y0);
    glVertex2d(x - x0, y + y0);
    glVertex2d(x + y0, y + x0);
    glVertex2d(x + y0, y - x0);
    glVertex2d(x - y0, y - x0);
    glVertex2d(x - y0, y + x0);
  }
  glEnd();
  glutSwapBuffers();
}

void drawSquare()
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP); // Start drawing a line primitive
	glVertex2f(200, 200); // The bottom left corner
	glVertex2f(200, 400);
	glVertex2f(400, 400); // The top left corner
	glVertex2f(400, 200); // The top right corner
 // The bottom right corner
    glEnd();

    newline.edgeLeft = 200;
    newline.edgeRight=400;
    newline.edgeBottom = 200;
    newline.edgeTop=400;

    glutSwapBuffers();
}

bool Line_Clip_Liang_Barsky()
{
    double p, q, r, t0=0.0, t1=1.0;

    for(int edge=0; edge<4; edge++)
    {
        if (edge==0) {  p = -newline.dx;    q = -(newline.edgeLeft-newline.x1);  } //Left
        if (edge==1) {  p = newline.dx;     q =  (newline.edgeRight-newline.x1); } //Right
        if (edge==2) {  p = -newline.dy;    q = -(newline.edgeBottom-newline.y1);} //Bottom
        if (edge==3) {  p = newline.dy;     q =  (newline.edgeTop-newline.y1);   } //Top

        r = q/p;
        if(p<0)
        {
            if(r>t1)
                return false;         // Don't draw line at all.
            else if(r>t0) t0=r;            // Line is clipped!
        }
        else if(p>0)
        {
            if(r<t0)
                return false;      // Don't draw line at all.
            else if(r<t1) t1=r;         // Line is clipped!
        }
    }

    newline.x1clip = newline.x1 + t0*newline.dx;
    newline.y1clip = newline.y1 + t0*newline.dy;
    newline.x2clip = newline.x1 + t1*newline.dx;
    newline.y2clip = newline.y1 + t1*newline.dy;

    return true;        // (clipped) line is drawn
}

void draw_line()
{
    newline.x1=100;
    newline.x2=500;
    newline.y1=500;
    newline.y2=100;

    newline.dx = newline.x2-newline.x1;
    newline.dy = newline.y2-newline.y1;

    if(Line_Clip_Liang_Barsky()==true)
    {
        glBegin(GL_LINES);
        glVertex3f(newline.x1clip, newline.y1clip, 0.0);
        glVertex3f(newline.x2clip, newline.y2clip, 0.0);
        glEnd();
    }

    glutSwapBuffers();
}

void display(void)
{
  int i;

  /* clear the screen to white */
  glClearColor(0.4, 2.0, 2.3, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glLineWidth(2);
  /* draw a black line */


  drawSquare();
  draw_line();
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

int
main(int argc, char *argv[])
{
  /* perform initialization NOT OpenGL/GLUT dependent,
     as we haven't created a GLUT window yet */
  init();

  /* initialize GLUT, let it extract command-line
     GLUT options that you may provide
     - NOTE THE '&' BEFORE argc */
  glutInit(&argc, argv);

  /* specify the display to be single
     buffered and color as RGBA values */
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

  /* set the initial window size */
  glutInitWindowSize((int) width, (int) height);

  /* create the window and store the handle to it */
  wd = glutCreateWindow("Experiment with line drawing" /* title */ );

  /* --- register callbacks with GLUT --- */

  /* register function to handle window resizes */
  glutReshapeFunc(reshape);

  /* register function that draws in the window */
  glutDisplayFunc(display);

  /* start the GLUT main loop */
  glutMainLoop();

  return 0;
}

