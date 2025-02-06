// GRAPscratch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include "cmath"
#define _USE_MATH_DEFINES
#include <math.h>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#define PI 3.14159265358979
using namespace std;


float x_mod = 0;
float y_mod = 0;
float z_mod = -1.f;

float theta = 0;
float thetaY = 0;
float scale_x = 1.0;
float scale_y = 1.0;
float scale_z = 1.0;

float axis_x = 0.0;
float axis_y = 1.0;
float axis_z = 0.0;

void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_D) {
		x_mod += 0.1;
    }

	if (key == GLFW_KEY_A) {
		x_mod -= 0.1;
	}
    
	if (key == GLFW_KEY_W) {
		y_mod += 0.1;
	}

	if (key == GLFW_KEY_S) {
		y_mod -= 0.1;
	}

	if (key == GLFW_KEY_Z) {
		z_mod += 0.1;
	}

	if (key == GLFW_KEY_X) {
		z_mod -= 0.1;
	}

	if (key == GLFW_KEY_RIGHT) {
		theta += 1.0;
	}

	if (key == GLFW_KEY_LEFT) {
		theta -= 1.0;
	}

    if (key == GLFW_KEY_UP)
    {
        thetaY -= 1;
    }

	if (key == GLFW_KEY_DOWN)
	{
		thetaY += 1;
	}


	if (key == GLFW_KEY_E) {
		scale_x += 0.1;
		scale_y += 0.1;
	}

	if (key == GLFW_KEY_Q) {
		scale_x -= 0.1;
		scale_y -= 0.1;
	}

	

    
}


int main(void)
{
    


    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

	float windowWidth = 700.f;
	float windowHeight = 700.f;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowWidth, windowHeight, "Arvin Lawrence B. Dacanay", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }



    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	gladLoadGL();
	glfwSetKeyCallback(window, Key_Callback);

	glViewport(0, 0, 700, 700);
    
    fstream vertSrc("Shaders/sample.vert");
    stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();
    string vertS = vertBuff.str();
    const char* v = vertS.c_str();

	fstream fragSrc("Shaders/sample.frag");
	stringstream fragBuff;
	fragBuff << fragSrc.rdbuf();
	string fragS = fragBuff.str();
	const char* f = fragS.c_str();

    //create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //assign the src to vertex shader
	glShaderSource(vertexShader, 1, &v, NULL);
	//compile the shader
	glCompileShader(vertexShader);

	//create fragment shader
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	//assign the src to fragment shader
	glShaderSource(fragShader, 1, &f, NULL);
	//compile the shader
	glCompileShader(fragShader);

	//create shader program
	GLuint shaderProg = glCreateProgram();
	//attach the compiled shaders to the program
	glAttachShader(shaderProg, vertexShader);
	glAttachShader(shaderProg, fragShader);
	//link the program
	glLinkProgram(shaderProg);







    std::string path = "3D/bunny.obj";
    std::vector<tinyobj::shape_t> shapes;
    std::vector < tinyobj::material_t> material;
    std::string warning, error;

    tinyobj::attrib_t attributes; //positions, texture data, and etc.

    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str()
    );

    std::vector<GLuint> mesh_indices;

    for (int i = 0; i < shapes[0].mesh.indices.size(); i++)
    {
        mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
    }

	GLfloat vertices[] {
		0.0f, 0.5f, 0.f, // Vertex 1 (X, Y, Z)
		-0.5f, -0.f, 0.f, // Vertex 2 (X, Y, Z)
		0.5f, -0.f, 0.f // Vertex 3 (X, Y, Z)
	};

    GLuint indices[]
    {
        0, 1, 2
    };

	GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //current VAO = null
    glBindVertexArray(VAO);
	//current VBO = VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Data
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(GLfloat) * attributes.vertices.size(), //Size of buffer in bytes
        &attributes.vertices[0], //Array itself
        GL_STATIC_DRAW //Static Objects for moving object need to use GL_DYNAMIC_DRAW
    );

    //Describes how to read data
    glVertexAttribPointer(
        //0 Position Data
        0, //Attrib Index-Index of VBO
        3, // X , Y , Z
        GL_FLOAT, //Array of GL floats
        GL_FALSE, //Is normalized?
        3 * sizeof(GLfloat), //size of components in bytes
        (void*)0 //stride value
    );

    //current VBO = VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //current VBO = EBO
    //current VAO.VBO.append(EBO)

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(GLuint) * mesh_indices.size(),
        mesh_indices.data(),
        GL_STATIC_DRAW
    );

    //enables attrib index 0
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
	glm::mat4 identity_matrix = glm::mat4(1.0f);
	//glm::mat3 identity_matrix = glm::mat3(1.0f);

	//glm::mat4 projectionMatrix = glm::ortho(-2.0f,//left
	//	2.0f,//right
	//	-2.0f, //bottom
	//	2.0f, //top
	//	-1.0f, //zNear
	//	1.0f); //zFar

	glm::mat4 projectionMatrix = glm::perspective(
		glm::radians(60.f), //fov
		windowHeight / windowWidth, // aspect ratio
		0.1f, //zNear
		100.f); //zFar
	
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);   
        //glBegin(GL_POLYGON);
        
		
		/*unsigned int xLoc = glGetUniformLocation(shaderProg, "x");
		glUniform1f(xLoc, x_mod);

		unsigned int yLoc = glGetUniformLocation(shaderProg, "y");
		glUniform1f(yLoc, y_mod);*/
		
		glm::vec3 cameraPos = glm::vec3(0, 0, 6.f); //eye
		glm::mat4 cameraPositionMatrix = glm::translate(glm::mat4(1.0f), cameraPos * -1.0f);

        //Orientation
		glm::vec3 worldUp = glm::normalize(glm::vec3(0, 1.f, 0)); //pointing up
		glm::vec3 cameraCenter = glm::vec3(0, 3.f + z_mod, 0); //center. a bit on the top of the bunny

		glm::vec3 cameraFront = glm::normalize(cameraCenter - cameraPos);
		cameraFront = glm::normalize(cameraFront);

		glm::vec3 cameraRight = glm::cross(cameraFront, worldUp) ;

		glm::vec3 cameraUp = glm::cross(cameraRight, cameraFront);

		glm::mat4 cameraOrientationMatrix = glm::mat4(1.0f); 


		//Matrix[column][row]
		cameraOrientationMatrix[0][0] = cameraRight.x;
		cameraOrientationMatrix[1][0] = cameraRight.y;
		cameraOrientationMatrix[2][0] = cameraRight.z;

		cameraOrientationMatrix[0][1] = cameraUp.x;
		cameraOrientationMatrix[1][1] = cameraUp.y;
		cameraOrientationMatrix[2][1] = cameraUp.z;

		cameraOrientationMatrix[0][2] = -cameraFront.x;
		cameraOrientationMatrix[1][2] = -cameraFront.y;
		cameraOrientationMatrix[2][2] = -cameraFront.z;


		//glm::mat4 viewMatrix = (cameraOrientationMatrix * cameraPositionMatrix);

		glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraCenter, worldUp);

        glm::mat4 transformation = glm::translate(
            identity_matrix,
            glm::vec3(x_mod, y_mod, z_mod)
        );

        transformation = glm::scale(
            transformation,
            glm::vec3(scale_x, scale_y, scale_z)
        );

        transformation = glm::rotate(transformation,
            glm::radians(theta),
            glm::normalize(glm::vec3(axis_x, axis_y, axis_z)));

        transformation = glm::rotate(
            transformation,
            glm::radians(thetaY),
            glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));

		unsigned int viewLoc = glGetUniformLocation(shaderProg, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        
		unsigned int projLoc = glGetUniformLocation(shaderProg, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        unsigned int transformLoc = glGetUniformLocation(shaderProg, "transform");
        //Assign the matrix
        glUniformMatrix4fv(transformLoc,
            1,
            GL_FALSE, //transpose?
            glm::value_ptr(transformation)); //Pointer to the matrix

        //glUniformMatrix4fv(transformLoc,
        //    1,
        //    GL_FALSE, //transpose?
        //    glm::value_ptr(scale)); //Pointer to the matrix
        //
        //glUniformMatrix4fv(transformLoc,
        //    1,
        //    GL_FALSE, //transpose?
        //    glm::value_ptr(rotate)); //Pointer to the matrix

        

        // use compiled shaders
		glUseProgram(shaderProg);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, mesh_indices.size(), GL_UNSIGNED_INT, 0);
       
        glEnd();    

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}