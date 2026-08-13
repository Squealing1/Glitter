#ifndef MODEL
#define MODEL
#include "assimp/scene.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <mesh.hpp>
#include <stb_image.h>
class Model{
    public:
        Model(std::string path){
            std::cout << path;
            loadModel(path);
        }
        void Draw(Shader& shader);
    private:
        // model data
        std::vector<Mesh> meshes;
        std::string directory;
        
        void loadModel(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
#endif