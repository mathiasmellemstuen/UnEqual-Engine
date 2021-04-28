#include "geometry.h." 
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../graphics/vertex.h"
#include <vector>
#include "../graphics/mesh.h"
#include "../graphics/texture.h"


Mesh icosahedron() {

    std::vector<Vertex> verticies = {
        Vertex {glm::vec3(0.0f, -0.525731f, 0.850651f),glm::vec3(0),glm::vec3(0)},
        Vertex {glm::vec3(0.850651f, 0.0f, 0.525731f),glm::vec3(0),glm::vec3(0)},
        Vertex {glm::vec3(0.850651f, 0.0f, -0.525731f),glm::vec3(0),glm::vec3(0)},
        Vertex {glm::vec3(-0.850651f, 0.0f, -0.525731f),glm::vec3(0),glm::vec3(0)},
        Vertex {glm::vec3(-0.850651f, 0.0f, 0.525731f),glm::vec3(0),glm::vec3(0)},
        Vertex {glm::vec3(-0.525731f, 0.850651f, 0.0f),glm::vec3(0),glm::vec3(0)},
        Vertex {glm::vec3(0.525731f, 0.850651f, 0.0f),glm::vec3(0),glm::vec3(0)},
        Vertex {glm::vec3(0.525731f, -0.850651f, 0.0f),glm::vec3(0),glm::vec3(0)},
        Vertex {glm::vec3(-0.525731f, -0.850651f, 0.0f),glm::vec3(0),glm::vec3(0)},
        Vertex {glm::vec3(0.0f, -0.525731f, -0.850651f),glm::vec3(0),glm::vec3(0)},
        Vertex {glm::vec3(0.0f, 0.525731f, -0.850651f),glm::vec3(0),glm::vec3(0)},
        Vertex {glm::vec3(0.0f, 0.525731f, 0.850651f),glm::vec3(0),glm::vec3(0)}
    };
    std::vector<unsigned int> indices = {
        1,2,6,
        1,7,2,
        3,4,5,
        4,3,8,
        6,5,11,
        5,6,10,
        9,10,2,
        10,9,3,
        7,8,9,
        8,7,0,
        11,0,1,
        0,11,4,
        6,2,10,
        1,6,11,
        3,5,10,
        5,4,11,
        2,7,9,
        7,1,0,
        3,9,8,
        4,8,0
    };

    std::vector<Texture> textures = {}; 
    return Mesh("Icosahedron", verticies, indices, textures);
};

Mesh sphere(int passes) {
    Mesh mesh = icosahedron();
    mesh.name = "Sphere"; 

    for(int i = 0; i < passes; i++) {
        mesh = calculateIcosahedronRounding(mesh); 
    }
    return mesh; 
}

Mesh calculateIcosahedronRounding(Mesh from) {

    std::vector<unsigned int> startingIndices = from.indices;
    std::vector<Vertex> startingVertices = from.verticies;
    std::vector<unsigned int> indices; 
    std::vector<Vertex> vertices; 

    int j = 0; 

    for(int i = 0; i < startingIndices.size(); i+=3) {

        glm::vec3 v0 = startingVertices.at(startingIndices.at(i)).position;
        glm::vec3 v1 = startingVertices.at(startingIndices.at(i + 1)).position; 
        glm::vec3 v2 = startingVertices.at(startingIndices.at(i + 2)).position;

        glm::vec3 v3 = glm::normalize(0.5f * (v0 + v1)); 
        glm::vec3 v4 = glm::normalize(0.5f * (v1 + v2)); 
        glm::vec3 v5 = glm::normalize(0.5f * (v2 + v0)); 

        Vertex vertex0; 
        Vertex vertex1; 
        Vertex vertex2; 
        Vertex vertex3; 
        Vertex vertex4;
        Vertex vertex5;

        vertex0.position = v0;
        vertex1.position = v1; 
        vertex2.position = v2; 
        vertex3.position = v3; 
        vertex4.position = v4; 
        vertex5.position = v5; 

        vertices.push_back(vertex0); 
        vertices.push_back(vertex1); 
        vertices.push_back(vertex2); 
        vertices.push_back(vertex3); 
        vertices.push_back(vertex4); 
        vertices.push_back(vertex5);

        int startingIndex = 6 * j;
        indices.push_back(startingIndex + 0);
        indices.push_back(startingIndex + 3);
        indices.push_back(startingIndex + 5);

        indices.push_back(startingIndex + 3);
        indices.push_back(startingIndex + 1);
        indices.push_back(startingIndex + 4);

        indices.push_back(startingIndex + 4);
        indices.push_back(startingIndex + 2);
        indices.push_back(startingIndex + 5);

        indices.push_back(startingIndex + 3);
        indices.push_back(startingIndex + 4);
        indices.push_back(startingIndex + 5);
        j++; 
    }
    return Mesh("Sphere", vertices, indices, from.textures);
}