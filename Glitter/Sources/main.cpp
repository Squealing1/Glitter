// Local Headers
#include "glitter.hpp"
#include "glm/ext/vector_float4.hpp"
#include <shader.hpp>

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <iostream>

void drawShape(unsigned int &VAO, unsigned int &EBO, Shader shader, unsigned int vert_cnt);
void drawShape(unsigned int &VAO, unsigned int &EBO, unsigned int &shaderProgram, unsigned int vert_cnt);
void create_shape(unsigned int &VAO, unsigned int &VBO, unsigned int& EBO, 
    float vert[], unsigned int vert_cnt, unsigned int ind[], 
    unsigned int ind_cnt, unsigned int dimensions);
void processInput(GLFWwindow* window);

namespace shapes {
    float r_tri[] = {
       -0.5f, 0.25f, 0.0f,  // top-left
       -0.5f, -0.5f, 0.0f,  // bottom-left
       0.5f, -0.5f, 0.0f,  // bottom-right
    };
    
    unsigned int r_tri_ind[] = {
        0, 1, 2
    };
    
    float rect[] = {
        -0.5, 0.5f, 0.0f, //top-left
        0.5, 0.5f, 0.0f, //top-right
        0.5, -0.5f, 0.0f, //bottom-right
        -0.5, -0.5f, 0.0f, //bottom-left
    };
    
    unsigned int rect_ind[] = {
        0, 1, 2,
        0, 2, 3,

    };

};





int main(int argc, char * argv[]) {

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    Shader shader("Glitter/Shaders/shader.vs", "Glitter/Shaders/shader.fs");
    
    unsigned int VBO, VAO, EBO;
    unsigned int VBO2, VAO2, EBO2;
    
    create_shape(VAO, VBO, EBO, shapes::rect, 12, shapes::rect_ind, 6, 3);
    create_shape(VAO2, VBO2, EBO2, shapes::r_tri, 9, shapes::r_tri_ind, 3, 3);
    
    
    glm::vec4 aColor1(0.5f,0.5f,0.0f,1.0f);
    glm::vec4 aColor2(0.1f,0.0f,0.5f,1.0f);
    // Rendering Loop
    while (!glfwWindowShouldClose(mWindow)) {

        // Background Fill Color
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        
        shader.use();
        shader.setUniform("aColor", aColor1);
        drawShape(VAO, EBO, shader,6);
        shader.setUniform("aColor", aColor2);
        drawShape(VAO2, EBO, shader, 3);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
        processInput(mWindow);
        

        
    }   glfwTerminate();
    return EXIT_SUCCESS;
}

void drawShape(unsigned int &VAO, unsigned int &EBO, Shader shader, unsigned int vert_cnt){
    shader.use();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, vert_cnt, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void processInput(GLFWwindow* mWindow){
    if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(mWindow, true);
}

void create_shape(unsigned int &VAO, unsigned int &VBO, unsigned int& EBO, 
    float vert[], unsigned int vert_cnt, unsigned int ind[], 
    unsigned int ind_cnt, unsigned int dimensions){
        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vert_cnt*sizeof(float), vert, GL_STATIC_DRAW);
        
        glGenBuffers(1,&EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_cnt*sizeof(unsigned int), ind, GL_STATIC_DRAW);
        
        
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
