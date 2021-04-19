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

struct MeshData {
    std::string name; 
    std::vector<unsigned int> faces; 
    std::vector<glm::vec3> vertices; 
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureCoordinates;
};

class Model {
    public: 
        Model(std::string filePath); 
        void draw(Shader &shader);
    private:
        std::vector<Mesh> meshes; 
        std::string filePath;
        void loadModel(std::string filePath);
        std::vector<Texture> loadMtllib(std::string filePath);
};
#endif