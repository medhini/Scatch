


void onMouse(int button, int state, int x, int y)
{

    if ((state != GLUT_DOWN) && ((button!=GLUT_LEFT_BUTTON)||(button!=GLUT_RIGHT_BUTTON)))
            return;

    if(state==GLUT_DOWN)
                if(button==GLUT_LEFT_BUTTON)
                            yTranslate+=0.05;
                else if(button==GLUT_RIGHT_BUTTON)
                        yTranslate-=0.05;




}
