#ifndef MODEL 
#define MODEL

#include <vector>
#include "shader.h"
#include <string>
#include "mesh.h"
#include "texture.h"
#include <glm/vec3.hpp>
#include "vertex.h"
#include <array>
#include "../sharedlib.h"

struct MeshData {
    std::string name; 
    std::vector<unsigned int> faces; 
    std::vector<glm::vec3> vertices; 
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureCoordinates;
};


class DLLEXPORT Model {
    public: 
        Model(std::string filePath); 
        void draw(Shader &shader);
        std::vector<Mesh> meshes; 
    private:
        std::string filePath;
        void loadModel(std::string filePath);
        std::vector<Texture> loadMtllib(std::string filePath);
};
#endif