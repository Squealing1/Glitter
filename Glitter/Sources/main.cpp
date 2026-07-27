// Local Headers
#include "glitter.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/geometric.hpp"
#include <iterator>
#include <shader.hpp>
#include <helpers.hpp>

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <stb_image.h>
#include <stdexcept>






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
    


    
    unsigned int texture1;
    create_texture(texture1, "Glitter/Textures/container.jpg", "jpg");
    unsigned int texture2;
    create_texture(texture2, "Glitter/Textures/awesomeface.png", "png");


    Shader shader("Glitter/Shaders/shader.vs", "Glitter/Shaders/shader.fs");
    Shader shaderTexture("Glitter/Shaders/texture.vs", "Glitter/Shaders/texture.fs");
    Shader shaderDoubleTexture("Glitter/Shaders/double-texture.vs", "Glitter/Shaders/double-texture.fs");
    Shader shaderColoredTexture("Glitter/Shaders/disco-texture.vs", "Glitter/Shaders/disco-texture.fs");
    Shader shaderDoubleTextureTransform("Glitter/Shaders/double-texture-transform.vs", "Glitter/Shaders/double-texture.fs");
    Shader shaderDoubleTextureMVP("Glitter/Shaders/double-texture-mvp.vs", "Glitter/Shaders/double-texture.fs");
    
    unsigned int VBO_T, VAO_T, EBO_T;
    
    glm::vec3 cameraPos(0.0f,0.0f,3.0f);
    glm::vec3 cameraTarget(0.0f,0.0f,0.0f);
    
    glm::vec3 toCameraDirection(cameraPos - cameraTarget);
    glm::vec3 up(0.0f,1.0f,0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, toCameraDirection));
    
    glm::vec3 cameraUp = glm::normalize(glm::cross(toCameraDirection,cameraRight));
    
    
    create_textured_shape(VAO_T, VBO_T, EBO_T, shapes::cube, 5*36, shapes::cube_ind, 36);
    
    

    shaderDoubleTextureMVP.use();
    shaderDoubleTextureMVP.setUniform("ourTexture1",0);
    shaderDoubleTextureMVP.setUniform("ourTexture2",1);
    
    glm::mat4 proj;
    proj = glm::perspective(glm::radians(45.0f), (float)mWidth / (float)mHeight, 0.1f, 100.0f);
    //float divisor = (float)mWidth/8.0f;
    //proj = glm::ortho(-(float)mWidth/divisor,(float)mWidth/divisor,-(float)mHeight/divisor,(float)mHeight/divisor,0.1f,100.0f);

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f,0.0f,-3.0f));

    glm::mat4 model(1.0f);

    shaderDoubleTextureMVP.setUniform("projection", proj);
    shaderDoubleTextureMVP.setUniform("view", view);
    shaderDoubleTextureMVP.setUniform("model",model);
    
    
    
    glEnable(GL_DEPTH_TEST);
    
    
    // Rendering Loop
    while (!glfwWindowShouldClose(mWindow)) {

        // Background Fill Color
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float time = glfwGetTime();
        
        const float radius = 10.0f;
        float camX = glm::sin(time)*radius;
        float camZ = glm::cos(time)*radius;
        view = glm::lookAt(glm::vec3(camX,0.0f,camZ), cameraTarget, cameraUp);
        shaderDoubleTextureMVP.setUniform("view",view);


        for(unsigned int i = 0; i < std::size(shapes::cubePositions); i++){
            model = glm::mat4(1.0f);
            model = glm::translate(model, shapes::cubePositions[i]);
            model = glm::rotate(model, glm::radians(15.0f)*(float)i, glm::vec3(0.4f,0.95f,0.2f));
            shaderDoubleTextureMVP.setUniform("model",model);
            drawDoubleTexturedShape(VAO_T, EBO_T, shaderDoubleTextureMVP, 36, texture1, texture2);
        }
        


        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
        processInput(mWindow);
        

        
    }   glfwTerminate();
    return EXIT_SUCCESS;
}