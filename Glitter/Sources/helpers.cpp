
#include <helpers.hpp>

#define SMALL_FLOAT 0.00000001f

glm::vec3 cameraFront(0.0f,0.0f,-1.0f);
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = (float)mWidth/2.0f;
float lastY = (float)mHeight/2.0f;
float fov = 30.0f;
bool first_mouse = true;
Camera camera(glm::vec3(0.0f,0.0f,3.0f));

namespace shapes {
    const float r_tri[] = {
       -0.5f, 0.25f, 0.0f,  // top-left
       -0.5f, -0.5f, 0.0f,  // bottom-left
       0.5f, -0.5f, 0.0f,  // bottom-right
    };
    
    const unsigned int r_tri_ind[] = {
        0, 1, 2
    };
    
    const float rect[] = {
        // position       
        -0.5,  0.5f, 0.0f,//top-left
         0.5,  0.5f, 0.0f, //top-right
         0.5, -0.5f, 0.0f, //bottom-right
        -0.5, -0.5f, 0.0f, //bottom-left
    };
    const float rect_c_t[] = {
        // position         color           texture coor
        -0.5,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,//top-left
         0.5,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, //top-right
         0.5, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, //bottom-right
        -0.5, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, //bottom-left
    };
    const float rect_t[] = {
        // position           texture coor
        -0.5,  0.5f, 0.0f,  0.0f, 1.0f,//top-left
         0.5,  0.5f, 0.0f,  1.0f, 1.0f, //top-right
         0.5, -0.5f, 0.0f,  1.0f, 0.0f, //bottom-right
        -0.5, -0.5f, 0.0f,  0.0f, 0.0f, //bottom-left
    };
    
    const unsigned int rect_ind[] = {
        0, 1, 2,
        0, 2, 3,

    };
    
    const float cube[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    };
    const float textured_cube[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    const unsigned int cube_ind[] = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10, 11,
        12, 13, 14,
        15, 16, 17,
        18, 19, 20,
        21, 22, 23,
        24, 25, 26,
        27, 28, 29,
        30, 31, 32,
        33, 34, 35
    };
    
    const std::vector<glm::vec3> cubePositions = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

};

void drawDoubleTexturedShape(unsigned int &VAO, unsigned int &EBO, Shader shader, unsigned int vert_cnt, unsigned int texture1, unsigned int texture2){
    shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, vert_cnt, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void drawTexturedShape(unsigned int &VAO, unsigned int &EBO, Shader shader, unsigned int vert_cnt, unsigned int texture){
    shader.use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, vert_cnt, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
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
void processInput(GLFWwindow* mWindow, Camera& camera, float deltatime){

    if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(mWindow, true);
    if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltatime);
    if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltatime);
    if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltatime);
    if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltatime);
}
void processInput(GLFWwindow* mWindow, glm::vec3& cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, float deltatime){
    float movementSpeed = 5.5;
    float cameraSpeed = movementSpeed * deltatime;
    glm::vec3 velocity(0.0f);
    if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(mWindow, true);
    if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
        velocity += cameraFront;
    if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
        velocity -= cameraFront;
    if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
        velocity += glm::normalize(glm::cross(cameraFront,cameraUp));
    if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
        velocity -= glm::normalize(glm::cross(cameraFront,cameraUp));
    
    if(glm::length(velocity) > SMALL_FLOAT) 
        velocity = glm::normalize(velocity) * cameraSpeed;
    cameraPos += velocity;
}

void create_shape(unsigned int &VAO, unsigned int &VBO, unsigned int& EBO, 
    const float vert[], unsigned int vert_cnt, const unsigned int ind[], 
    unsigned int ind_cnt){
        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vert_cnt*sizeof(float), vert, GL_STATIC_DRAW);
        
        glGenBuffers(1,&EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_cnt*sizeof(unsigned int), ind, GL_STATIC_DRAW);
        
        unsigned int dimensions = 3;
        
        
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

GLFWwindow* loadGLFWCreateWindow(int width, int height){
    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);
    return mWindow;
}

void create_textured_shape(unsigned int &VAO, unsigned int &VBO, unsigned int& EBO, 
    const float vert[], unsigned int vert_cnt, unsigned int const ind[], 
    unsigned int ind_cnt){
    
        
        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vert_cnt*sizeof(float), vert, GL_STATIC_DRAW);
        
        glGenBuffers(1,&EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_cnt*sizeof(unsigned int), ind, GL_STATIC_DRAW);
        
        unsigned int dimensions = 3;
        unsigned int tex_dimensions = 2;
        
        unsigned int total = dimensions + tex_dimensions;
        
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, total * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, tex_dimensions, GL_FLOAT, GL_FALSE, total * sizeof(float), (void*)((total-tex_dimensions)*sizeof(float)));
        glEnableVertexAttribArray(1);
    }
void create_colored_textued_shape(unsigned int &VAO, unsigned int &VBO, unsigned int& EBO, 
    float vert[], unsigned int vert_cnt, unsigned int ind[], 
    unsigned int ind_cnt){
    
        
        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vert_cnt*sizeof(float), vert, GL_STATIC_DRAW);
        
        glGenBuffers(1,&EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_cnt*sizeof(unsigned int), ind, GL_STATIC_DRAW);
        
        unsigned int dimensions = 3;
        unsigned int color_atts = 3;
        unsigned int tex_dimensions = 2;
        
        unsigned int total = dimensions + color_atts + tex_dimensions;
        
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, total * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, color_atts, GL_FLOAT, GL_FALSE, total * sizeof(float), (void*)(dimensions*sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, tex_dimensions, GL_FLOAT, GL_FALSE, total * sizeof(float), (void*)((total-tex_dimensions)*sizeof(float)));
        glEnableVertexAttribArray(2);
    }

void create_texture(unsigned int &texture, const char texture_filepath[], std::string filetype){
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texture_filepath, &width, &height, &nrChannels, 0);
    glGenTextures(1, &texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    
    if (data){
        if(filetype == "jpg")
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else if(filetype == "png")
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        else {
            throw std::runtime_error("Bad file type: " + filetype);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        throw std::runtime_error("Failed to load texture: " + std::string(texture_filepath));
    }
    stbi_image_free(data);
}

GLFWwindow* initOpenGL(int& return_status, int width, int height){
    // Load GLFW and Create a Window
    auto mWindow = loadGLFWCreateWindow(width, height);

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return_status = EXIT_FAILURE;
        return mWindow;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
    

    glEnable(GL_DEPTH_TEST);
    return_status = EXIT_SUCCESS;
    return mWindow;
}

DeltaTimer::DeltaTimer(){}
float DeltaTimer::getDeltaTime(bool do_update){
    if(do_update) 
        updateDeltaTime();
    return deltatime;
}
void DeltaTimer::updateDeltaTime(){
    elapsed_time = glfwGetTime();
    deltatime = elapsed_time - lastframe_time;
    lastframe_time = elapsed_time;
}

// learnopgl start

int drawCubes(int argc, char * argv[]){
    
    // Initialize OpenGL
    int return_status = EXIT_SUCCESS;
    auto mWindow = initOpenGL(return_status, mWidth, mHeight);
    if(return_status != EXIT_SUCCESS) return return_status;
    
    DeltaTimer deltaTimer{};
    

    
    unsigned int texture1;
    create_texture(texture1, "Glitter/Textures/container.jpg", "jpg");
    unsigned int texture2;
    create_texture(texture2, "Glitter/Textures/awesomeface.png", "png");


    Shader shaderDoubleTextureMVP("Glitter/Shaders/double-texture-mvp.vs", "Glitter/Shaders/double-texture.fs");
    
    unsigned int VBO_T, VAO_T, EBO_T;
    
    
    
    
    create_textured_shape(VAO_T, VBO_T, EBO_T, shapes::textured_cube, 5*36, shapes::cube_ind, 36);
    
    

    shaderDoubleTextureMVP.use();
    shaderDoubleTextureMVP.setUniform("ourTexture1",0);
    shaderDoubleTextureMVP.setUniform("ourTexture2",1);
    
    glm::mat4 proj;
    proj = glm::perspective(glm::radians(45.0f), (float)mWidth / (float)mHeight, 0.1f, 100.0f);

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f,0.0f,-3.0f));

    glm::mat4 model(1.0f);

    shaderDoubleTextureMVP.setUniform("projection", proj);
    shaderDoubleTextureMVP.setUniform("view", view);
    shaderDoubleTextureMVP.setUniform("model",model);
    
    
    glm::vec3 cameraPos(0.0f,0.0f,3.0f);
    glm::vec3 cameraUp(0.0f,1.0f,0.0f);
    glm::vec3 cameraTarget(0.0f,0.0f,0.0f);
    
    glm::vec3 toCameraDirection(cameraPos - cameraTarget);
    glm::vec3 up(0.0f,1.0f,0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, toCameraDirection));
    
    
    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(mWindow, mouse_callback);
    glfwSetScrollCallback(mWindow, scroll_callback);


    
    
    // Rendering Loop
    while (!glfwWindowShouldClose(mWindow)) {

        // Background Fill Color
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        proj = glm::perspective(glm::radians(camera.Zoom), (float)mWidth / (float)mHeight, 0.1f, 100.0f);
        shaderDoubleTextureMVP.setUniform("projection",proj);
        

        view = camera.GetViewMatrix();
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
        processInput(mWindow, camera, deltaTimer.getDeltaTime());
        

        
    }   glfwTerminate();
    return EXIT_SUCCESS;
}


// learnopgl end

glm::vec3 cameraDirection(float yaw, float pitch){
    glm::vec3 direction;
    direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    direction.y = glm::sin(glm::radians(pitch));
    direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    return direction;
}
void mouse_callback(GLFWwindow* mWindow, double xpos, double ypos){
    if(first_mouse){
        lastX = xpos;
        lastY = ypos;
        first_mouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* mWindow, double xoffset, double yoffset){
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

int drawLight(int argc, char * argv[]){
    
    // Initialize OpenGL
    int return_status = EXIT_SUCCESS;
    auto mWindow = initOpenGL(return_status, mWidth, mHeight);
    if(return_status != EXIT_SUCCESS) return return_status;
    
    DeltaTimer deltaTimer{};
    

    


    
    unsigned int VBO_O, VAO_O, EBO_O;
    unsigned int VBO_T, VAO_T, EBO_T;
    
    
    
    
    create_shape(VAO_T, VBO_T, EBO_T, shapes::cube, 3*36, shapes::cube_ind, 36);
    create_shape(VAO_O, VBO_O, EBO_O, shapes::cube, 3*36, shapes::cube_ind, 36);
    
    

    
    glm::mat4 proj;
    proj = glm::perspective(glm::radians(45.0f), (float)mWidth / (float)mHeight, 0.1f, 100.0f);

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f,0.0f,-3.0f));

    glm::mat4 model(1.0f);

    Shader object_shader("Glitter/Shaders/light.vs", "Glitter/Shaders/light.fs");
    Shader light_shader("Glitter/Shaders/light.vs", "Glitter/Shaders/shader.fs");
    object_shader.use();
    object_shader.setUniform("projection", proj);
    object_shader.setUniform("view", view);
    object_shader.setUniform("model",model);
    object_shader.setUniform("light_color", glm::vec3(1.0f,1.0f,1.0f));
    object_shader.setUniform("object_color", glm::vec3(1.0f,0.5f,0.31f));
    
    light_shader.use();
    
    glm::vec3 light_pos(1.2f,1.0f,2.0f);
    model = glm::translate(model, light_pos);
    model = glm::scale(model, glm::vec3(0.2f));
    light_shader.setUniform("projection", proj);
    light_shader.setUniform("view", view);
    light_shader.setUniform("model",model);
    light_shader.setUniform("aColor",glm::vec3(1.0f,1.0f,1.0f));
    
    
    
    
    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(mWindow, mouse_callback);
    glfwSetScrollCallback(mWindow, scroll_callback);


    
    
    // Rendering Loop
    while (!glfwWindowShouldClose(mWindow)) {

        // Background Fill Color
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        proj = glm::perspective(glm::radians(camera.Zoom), (float)mWidth / (float)mHeight, 0.1f, 100.0f);
        

        view = camera.GetViewMatrix();
        light_shader.use();
        light_shader.setUniform("projection",proj);
        light_shader.setUniform("view",view);
        object_shader.use();
        object_shader.setUniform("view",view);
        object_shader.setUniform("projection",proj);
        
        drawShape(VAO_T, EBO_T, light_shader, 3*36);
        drawShape(VAO_O, VAO_O, object_shader, 3*36);


        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
        processInput(mWindow, camera, deltaTimer.getDeltaTime());
        

        
    }   glfwTerminate();
    return EXIT_SUCCESS;
}