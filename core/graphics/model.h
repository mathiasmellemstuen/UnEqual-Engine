#ifndef MODEL 
#define MODEL

#include <vector>
#include "mesh.h"
#include "shader.h"
#include <string>
#include <assimp/scene.h>

class Model {
    public: 
        Model(char* path); 
        void draw(Shader &shader);

    private:
        std::vector<Mesh> meshes; 
        std::string directory; 
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};
#endif