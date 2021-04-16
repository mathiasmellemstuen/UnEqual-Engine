#ifndef MESH
#define MESH

#include <vector>
#include "vertex.h"
#include "texture.h"
#include "shader.h"
#include <string>

class Mesh {
    public:
        std::string name; 
        std::vector<Vertex> verticies; 
        std::vector<unsigned int> indices; 
        std::vector<Texture> textures;

        Mesh(std::string name, std::vector<Vertex> verticies, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void draw(Shader &shader); 

    private: 
        unsigned int VAO, VBO, EBO;
        void setup(); 
};
#endif