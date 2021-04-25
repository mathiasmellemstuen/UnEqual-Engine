#include "mesh.h"
#include <vector>
#include "texture.h"
#include "../log/log.h"
#include <glad/glad.h>
#include "vertex.h"
#include <string>

Mesh::Mesh(std::string name, std::vector<Vertex> verticies, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->name = name; 
    this->verticies = verticies; 
    this->indices = indices;
    this->textures = textures;

    setup(); 
};
void Mesh::setup() {
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
}
void Mesh::draw(Shader &shader) {

   unsigned int diffuseNr = 1; 
   unsigned int specularNr = 1; 

   for(unsigned int i = 0; i < this->textures.size(); i++) {
        
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number; 

        if(this->textures[i].getTextureType() == TextureType::DIFFUSE) {
            number = std::to_string(diffuseNr++);
        }

        else if(this->textures[i].getTextureType() == TextureType::SPECULAR) {
            number = std::to_string(specularNr++);  
        }

        std::string name = this->textures[i].getTextureType() == TextureType::DIFFUSE ? "diffuse" : "specular"; 
        shader.setInt((name + number).c_str(), i);


        glBindTexture(GL_TEXTURE_2D, textures[i].getTextureId()); 

    }
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0); 
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0); 
};