#include "mesh.h"
#include <vector>
#include "texture.h"
#include "../log/log.h"
#include "../../thirdparty/linux/glad/glad.h"
#include "vertex.h"

Mesh::Mesh(std::vector<Vertex> verticies, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->verticies = verticies; 
    this->indices = indices;
    this->textures = textures;

    log(INFO, "Mesh setup is starting.");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); 
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 

    glBufferData(GL_ARRAY_BUFFER, this->verticies.size() * sizeof(Vertex), &(this->verticies[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &(this->indices[0]), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));

    glBindVertexArray(0);

    log(SUCCESS, "Mesh setup is complete."); 
};
void Mesh::draw(Shader &shader) {
    
};