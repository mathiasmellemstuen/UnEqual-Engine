#ifndef VERTEX
#define VERTEX

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "../sharedlib.h"

struct Vertex {
    glm::vec3 position; 
    glm::vec3 normal; 
    glm::vec2 textureCoordinates;

    inline bool operator==(Vertex& other) {
        return 
        position.x == other.position.x &&
        position.y == other.position.y &&
        position.z == other.position.z &&
        normal.x == other.normal.x &&
        normal.y == other.normal.y &&
        normal.z == other.normal.z &&
        textureCoordinates.x == other.textureCoordinates.x &&
        textureCoordinates.y == other.textureCoordinates.y;
    };
};

#endif