#ifndef MESH
#define MESH

#include <vector>
#include "vertex.h"
#include "texture.h"
#include "shader.h"

class Mesh {
    public:
        std::vector<Vertex> verticies; 
        std::vector<unsigned int> indices; 
        std::vector<Texture> textures;
        
        Mesh(std::vector<Vertex> verticies, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void draw(Shader &shader); 

    private: 
        unsigned int VAO, VBO, EBO;
};
#endif