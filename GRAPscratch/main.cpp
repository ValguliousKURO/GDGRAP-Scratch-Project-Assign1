// GRAPscratch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <GLFW/glfw3.h>
#include "cmath"
#define PI 3.14159265358979
using namespace std;
int main(void)
{
    
    int sides = 8;
    float rotate = (22.5 * (PI / 180)); // 22.5 =  360 / 8 = 45 / 2
    //for checking values
    for (int i = 0; i < sides; i++) {
        float theta = 2 * PI * i / sides + rotate;
        float x = cos(theta);
        float y = sin(theta) + (1- 0.92388);
        //glVertex2f(x, y);
        cout << "(" << x << ", " << y << ")" << endl;
    }



    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(700, 700, "Arvin Lawrence B. Dacanay", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }



    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);   
        glBegin(GL_POLYGON);
        
        for (int i = 0; i < sides; i++) {
            float theta = 2 * PI * i / sides + rotate;
            float x = cos(theta);
            float y = sin(theta) + (1 - 0.92388);
            glVertex2f(x, y);
            //cout<<"(" << x << ", "<< y << ")" << endl;
        }
       /* glVertex2f(0.9239, 0.3827);
        glVertex2f(0.3827, 0.9239);
        glVertex2f(-0.3827, 0.9239);
        glVertex2f(-0.9239, 0.3827);
        glVertex2f(-0.9239, -0.3827);
        glVertex2f(-0.3827, -0.9239);
        glVertex2f(0.3827, -0.9239);
        glVertex2f(0.9239, -0.3827);*/
        
        /*glVertex2f(0.5, -1);
        glVertex2f(-0.5, -1);
        glVertex2f(-1, -0.5);
        glVertex2f(-1, 0.5);
        glVertex2f(-0.5, 1);
        glVertex2f(0.5, 1);
        glVertex2f(1, 0.5);
        glVertex2f(1, -0.5);*/
        glEnd();    

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}