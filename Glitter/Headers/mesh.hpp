#ifndef MESH
#define MESH
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float2.hpp"
#include "string"
#include <shader.hpp>
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
};

class Mesh {
    public:
        std::vector<Vertex> vertices;
        std::vector<Texture> textures;
        std::vector<unsigned int> indices;
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw(Shader& shader);
    private:
        unsigned int VAO, VBO, EBO;
        void setupMesh();
};
#endif