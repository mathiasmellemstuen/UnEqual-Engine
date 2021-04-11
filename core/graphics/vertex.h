#ifndef VERTEX
#define VERTEX

#include <glm/vec3.hpp>

struct Vertex {
    glm::vec3 position; 
    glm::vec3 normal; 
    glm::vec3 textureCoordinates;
};

#endif