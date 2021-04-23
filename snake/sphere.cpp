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

    int M = 10; //Latitude
    int N = 10;  //Longitude
    const double pi = 3.14159265358979323846;
    unsigned int i = 0; 
    for(int m = 0; m < M; m++) {
        for(int n = 0; n < N; n++) {
            Vertex v;
            float x = sin(pi * (m / M)) * cos(2 * pi * (n / N));
            float y = sin(pi * (m / M)) * sin(2 * pi * (n / N));
            float z = cos(pi * (m / M));

            v.position = glm::vec3(x * 10.0f,y * 10.0f,z * 10.0f); 
            v.normal = glm::vec3(x,y,z); 

            indices.push_back(i);
            i++; 
            verticies.push_back(v);
        }
    }
    return Mesh(name, verticies, indices, textures);
};