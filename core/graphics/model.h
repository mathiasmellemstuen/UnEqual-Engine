#ifndef MODEL 
#define MODEL

#include <vector>
#include "shader.h"
#include <string>
#include <assimp/scene.h>
#include "mesh.h"
#include "texture.h"


class Model {
    public: 
        Model(char* path); 
        void draw(Shader &shader);
    private:
        std::vector<Mesh> meshes; 
        std::string directory;
        void loadModel(std::string path); 
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string typeName); 
        std::vector<Texture> loadedTextures; 
};
#endif