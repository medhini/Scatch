#include <math.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
//#include "Declaration.h"

float g=9.8;
#define PI 3.14159265

using namespace std;

pair <int, int> Red_Path1[500];
pair <int, int> Red_Path2[500];
pair <int, int> Red_Path3[500];
pair <int, int> Red_Path4[500];
pair <int, int> Red_Path5[500];
pair <int, int> Blue_Path1[500];
pair <int, int> Blue_Path2[500];
pair <int, int> Blue_Path3[500];
pair <int, int> Blue_Path4[500];
pair <int, int> Blue_Path5[500];

vector <int> max_distance;

void Calculate_Path(float u, float theta, int max_distance, int case_num) //Creates the 10 paths
{


    float time_of_flight = 2*u*sin(theta)/g;
    float delta_time = time_of_flight/max_distance;

    float time = 0;

    switch(case_num)
    {
    case 1:

        for(int i=0; i<max_distance; i++)
        {
            Red_Path1[i].first = u*cos(theta)*time;
            Red_Path1[i].second = u*sin(theta)*time - ((g*time*time)/2);

            time += delta_time;
        }
        break;
    case 2 :

        for(int i=0; i<max_distance; i++)
        {
            Red_Path2[i].first = u*cos(theta)*time;
            Red_Path2[i].second = u*sin(theta)*time - ((g*time*time)/2);

            time += delta_time;
        }
        break;
    case 3:
        for(int i=0; i<max_distance; i++)
        {
            Red_Path5[i].first = u*cos(theta)*time;
            Red_Path5[i].second = u*sin(theta)*time - ((g*time*time)/2);

            time += delta_time;
        }
        break;
    case 4:
        for(int i=0; i<max_distance; i++)
        {
            Red_Path3[i].first = u*cos(theta)*time;
            Red_Path3[i].second = u*sin(theta)*time - ((g*time*time)/2);

            time += delta_time;
        }
        break;
    case 5:
        for(int i=0; i<max_distance; i++)
        {
            Red_Path4[i].first = u*cos(theta)*time;
            Red_Path4[i].second = u*sin(theta)*time - ((g*time*time)/2);

            time += delta_time;
        }
        break;
    case 6:
        for(int i=0; i<max_distance; i++)
        {
            Blue_Path5[i].first = u*cos(theta)*time;
            Blue_Path5[i].second = u*sin(theta)*time - ((g*time*time)/2);

            time += delta_time;
        }
        break;
    case 7:
        for(int i=0; i<max_distance; i++)
        {
            Blue_Path4[i].first = u*cos(theta)*time;
            Blue_Path4[i].second = u*sin(theta)*time - ((g*time*time)/2);

            time += delta_time;
        }
        break;
    case 8:
        for(int i=0; i<max_distance; i++)
        {
            Blue_Path3[i].first = u*cos(theta)*time;
            Blue_Path3[i].second = u*sin(theta)*time - ((g*time*time)/2);

            time += delta_time;
        }
        break;
    case 9:
        for(int i=0; i<max_distance; i++)
        {
            Blue_Path2[i].first = u*cos(theta)*time;
            Blue_Path2[i].second = u*sin(theta)*time - ((g*time*time)/2);

            time += delta_time;
        }
        break;
    case 10:
        for(int i=0; i<max_distance; i++)
        {
            Blue_Path1[i].first = u*cos(theta)*time;
            Blue_Path1[i].second = u*sin(theta)*time - ((g*time*time)/2);

            time += delta_time;
        }
        break;
    }

}

void Generate_U_Theta()
{
    vector <float> u;  //Initial Velocites
    vector <float> theta; //Angles

    for(int i=0; i<10; i++) //Generating random initial velocities
    {
        u.push_back(rand()%100 + 100);
    }

    sort(u.begin(), u.end());

    for(int i=0; i<5; i++) //Generating random angles
    {
        float angle_in_degrees = rand()%45+44;
        float angle_in_radians = (angle_in_degrees*PI)/180;

        theta.push_back(angle_in_radians);
    }
    for(int i=0; i<5; i++)
        cout<<theta[i]<<" ";

    for(int i=0;i<10; i++)
    {
        max_distance.push_back(rand()%100 + 50);
    }

    sort(max_distance.begin(), max_distance.end());
    int j=0;
    for(int i=0; i<10; i++) //Calling calculate_path 10 times to calculate 10 paths
    {
        if(i<5)
        Calculate_Path(u[i], theta[i], max_distance[10-i-1], i+1);
        else
        {

            Calculate_Path(u[i], theta[j], max_distance[10-i-1], i+1);
            j++;
        }
    }

   /* for(int i=0; i<100; i++)
    {
        cout<<Red_Path1[i].first<<" "<<Red_Path1[i].second<<endl;
    }*/
}

