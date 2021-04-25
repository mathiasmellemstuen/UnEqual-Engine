#include "sphere.h"
#include "../core/graphics/mesh.h"
#include "../core/graphics/vertex.h"
#include <glm/vec3.hpp>
#include <stdio.h>
#include <math.h>
#include <string>
#include "../core/log/log.h"

Mesh generateSphere() {
    std::string name = "sphere"; 
    std::vector<Vertex> verticies; 
    std::vector<unsigned int> indices; 
    std::vector<Texture> textures;

    const double pi = 3.14159265358979323846;
    
    float t = (1.0f + sqrt(5.0f) / 2.0f) / 2.0f;
    
    Vertex v1;
    v1.position = glm::vec3(-1.0f, t, 0.0f);
    v1.normal = glm::vec3(0.0f,0.0f,1.0f);

    Vertex v2;
    v1.position = glm::vec3(1.0f, t, 0.0f);
    v1.normal = glm::vec3(0.0f,0.0f,1.0f);

    Vertex v3;
    v1.position = glm::vec3(-1.0f, -t, 0.0f);
    v1.normal = glm::vec3(0.0f,0.0f,1.0f);

    Vertex v4;
    v1.position = glm::vec3(1.0f, -t, 0.0f);
    v1.normal = glm::vec3(0.0f,0.0f,1.0f);

    Vertex v5;
    v1.position = glm::vec3(0.0f, -1.0f, t);
    v1.normal = glm::vec3(0.0f,0.0f,1.0f);

    Vertex v6;
    v1.position = glm::vec3(0.0f, 1.0f, t);
    v1.normal = glm::vec3(0.0f,0.0f,1.0f);

    Vertex v7;
    v1.position = glm::vec3(0.0f, -1.0f, -t);
    v1.normal = glm::vec3(0.0f,0.0f,1.0f);

    Vertex v8;
    v1.position = glm::vec3(0.0f, 1.0f, -t);
    v1.normal = glm::vec3(0.0f,0.0f,1.0f);

    Vertex v9;
    v1.position = glm::vec3(t, 0.0f, -1.0f);
    v1.normal = glm::vec3(0.0f,0.0f,1.0f);

    Vertex v10;
    v1.position = glm::vec3(t, 0.0f, 1.0f);
    v1.normal = glm::vec3(0.0f,0.0f,1.0f);

    Vertex v11;
    v1.position = glm::vec3(-t, 0.0f, -1.0f);
    v1.normal = glm::vec3(0.0f,0.0f,1.0f);

    Vertex v12;
    v1.position = glm::vec3(-t, 0.0f, 1.0f);
    v1.normal = glm::vec3(0.0f,0.0f,1.0f);

    verticies.push_back(v1);
    verticies.push_back(v2);
    verticies.push_back(v3);
    verticies.push_back(v4);
    verticies.push_back(v5);
    verticies.push_back(v6);
    verticies.push_back(v7);
    verticies.push_back(v8);
    verticies.push_back(v9);
    verticies.push_back(v10);
    verticies.push_back(v11);
    verticies.push_back(v12);

    indices.push_back(0);
    indices.push_back(11);
    indices.push_back(5);

    indices.push_back(0);
    indices.push_back(5);
    indices.push_back(1);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(7);

    indices.push_back(0);
    indices.push_back(7);
    indices.push_back(10);

    indices.push_back(0);
    indices.push_back(10);
    indices.push_back(11);

    indices.push_back(1);
    indices.push_back(5);
    indices.push_back(9);

    indices.push_back(5);
    indices.push_back(11);
    indices.push_back(4);

    indices.push_back(11);
    indices.push_back(10);
    indices.push_back(2);

    indices.push_back(10);
    indices.push_back(7);
    indices.push_back(6);

    indices.push_back(7);
    indices.push_back(1);
    indices.push_back(8);

    indices.push_back(3);
    indices.push_back(9);
    indices.push_back(4);

    indices.push_back(3);
    indices.push_back(4);
    indices.push_back(2);

    indices.push_back(3);
    indices.push_back(2);
    indices.push_back(6);

    indices.push_back(3);
    indices.push_back(6);
    indices.push_back(8);

    indices.push_back(3);
    indices.push_back(8);
    indices.push_back(9);

    indices.push_back(4);
    indices.push_back(9);
    indices.push_back(5);

    indices.push_back(2);
    indices.push_back(4);
    indices.push_back(11);

    indices.push_back(6);
    indices.push_back(2);
    indices.push_back(10);

    indices.push_back(8);
    indices.push_back(6);
    indices.push_back(7);

    indices.push_back(8);
    indices.push_back(8);
    indices.push_back(1);

    return Mesh(name, verticies, indices, textures);
};