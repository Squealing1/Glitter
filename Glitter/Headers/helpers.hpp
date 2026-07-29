#ifndef HELPERS
#define HELPERS
// Local Headers
#include "glitter.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/geometric.hpp"
#include <iterator>
#include <shader.hpp>

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <stb_image.h>
#include <stdexcept>

void drawShape(unsigned int &VAO, unsigned int &EBO, Shader shader, unsigned int vert_cnt);
void drawTexturedShape(unsigned int &VAO, unsigned int &EBO, Shader shader, unsigned int vert_cnt, unsigned int texture);
void drawDoubleTexturedShape(unsigned int &VAO, unsigned int &EBO, Shader shader, unsigned int vert_cnt, unsigned int texture1, unsigned int texture2);
void create_shape(unsigned int &VAO, unsigned int &VBO, unsigned int& EBO, 
    float vert[], unsigned int vert_cnt, unsigned int ind[], 
    unsigned int ind_cnt, unsigned int dimensions);
void create_colored_textued_shape(unsigned int &VAO, unsigned int &VBO, unsigned int& EBO, 
    float vert[], unsigned int vert_cnt, unsigned int ind[], 
    unsigned int ind_cnt);
void processInput(GLFWwindow* mWindow, glm::vec3& cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);
void processInput(GLFWwindow* mWindow, glm::vec3& cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, float deltatime);
void create_textured_shape(unsigned int &VAO, unsigned int &VBO, unsigned int& EBO, 
    const float vert[], unsigned int vert_cnt, const unsigned int ind[], 
    unsigned int ind_cnt);
void create_texture(unsigned int &texture, const char texture_filepath[], std::string filetype);
GLFWwindow* loadGLFWCreateWindow(int width, int height);
GLFWwindow* initOpenGL(int& return_status, int width, int height);
int drawCubes(int argc, char * argv[]);
int drawOther(int argc, char * argv[]);
void mouse_callback(GLFWwindow* mWindow, double xPos, double yPos);

void scroll_callback(GLFWwindow* mWindow, double xoffset, double yoffset);
extern float yaw;
extern float pitch;
extern float lastX;
extern float lastY;
extern bool first_mouse;

namespace shapes {
    extern const float r_tri[];
    extern const unsigned int r_tri_ind[];
    extern const float rect[];
    extern const float rect_c_t[];
    extern const float rect_t[];
    extern const unsigned int rect_ind[];
    extern const float cube[];
    extern const unsigned int cube_ind[];
    extern const std::vector<glm::vec3> cubePositions;
};

class DeltaTimer{
    public:
        DeltaTimer();
        float getDeltaTime(bool do_update = true);
    private:
        void updateDeltaTime();
        float elapsed_time = 0.0f;
        float lastframe_time = 0.0f;
        float deltatime = 0.0f;
};
glm::vec3 cameraDirection(float yaw, float pitch);

#endif