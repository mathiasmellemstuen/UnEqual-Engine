#include "model.h"
#include "mesh.h"
#include "texture.h"
#include <string>
#include <fstream>
#include "../log/log.h"
#include <regex>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

Model::Model(std::string filePath) {
    loadModel(filePath);
};

std::vector<Texture> Model::loadMtllib(std::string filePath) {
    
    log(INFO, "Starting loading mtllib file. ");
    log(INFO, "Filepath: " + filePath); 
    
    std::vector<Texture> textures; 

    std::ifstream file(filePath); 
    std::string line; 
    std::regex map_kdExpression("^map_Kd ");
    std::regex map_BumpExpression("^map_Bump ");
    std::regex map_KsExpression("^map_Ks");
    std::smatch match;
   
    std::regex folderExpression("^.+\\/");
    std::regex_search(filePath, match, folderExpression); 
    std::string folderPath = (std::string)match[0]; 

    while(std::getline(file, line)) {

        if(std::regex_search(line, map_kdExpression)) {
            line.erase(0,7);
            
            Texture texture;
            texture.createFromFile(folderPath + line, DIFFUSE);

            textures.push_back(texture); 
            continue; 
        }

        if(std::regex_search(line, map_BumpExpression)) {
            line.erase(0,9);
            continue; 
        }

        if(std::regex_search(line, map_KsExpression)) {
            line.erase(0,7);

            Texture texture;
            texture.createFromFile(folderPath + line, SPECULAR);

            textures.push_back(texture); 
            continue; 
        }
    }

    return textures; 
}
void Model::loadModel(std::string filePath) {

    log(INFO, "Loading model at: " + filePath); 
    std::vector<unsigned int> vertexIndices; 
    std::vector<unsigned int> textureCoordinateIndices;
    std::vector<unsigned int> normalIndices; 

    std::vector<glm::vec3> vertices; 
    std::vector<glm::vec2> textureCoordinates; 
    std::vector<glm::vec3> normals; 
    
    std::ifstream file(filePath); 
    std::string line;

    std::regex findNumericValue("[+-]?([0-9]*[.])?[0-9]+");
    std::regex mtllibExpression("^mtllib");
    std::smatch match;

    std::string mtllibFileName;

    while(std::getline(file, line)) {
        
        if(line[0] == 'v' && line[1] == ' ') {

            int i = 0; 
            glm::vec3 vertex; 
            while(std::regex_search(line, match, findNumericValue)) {
                vertex[i] = std::stof(match[0]);
                line = match.suffix();
                i++; 
            }
            vertices.push_back(vertex); 
        }
        else if(line[0] == 'v' && line[1] == 't') {

            int i = 0; 
            glm::vec2 textureCoordinate; 
            while(std::regex_search(line, match, findNumericValue)) {
                textureCoordinate[i] = std::stof(match[0]);
                line = match.suffix();
                i++; 
            }
            textureCoordinates.push_back(textureCoordinate);
        }
        else if(line[0] == 'v' && line[1] == 'n') {

            int i = 0; 
            glm::vec3 normal; 
            while(std::regex_search(line, match, findNumericValue)) {
                normal[i] = std::stof(match[0]);
                line = match.suffix();
                i++; 
            }
            normals.push_back(normal);
        }
        else if(line[0] == 'f') {
            
            unsigned int indices[9]; 
            int i = 0;
            
            while(std::regex_search(line, match, findNumericValue)) {
                indices[i] = std::stoul(match[0]); 
                line = match.suffix();
                i++; 
            }

            vertexIndices.push_back(indices[0]);
            textureCoordinateIndices.push_back(indices[1]); 
            normalIndices.push_back(indices[2]); 

            vertexIndices.push_back(indices[3]);
            textureCoordinateIndices.push_back(indices[4]); 
            normalIndices.push_back(indices[5]); 

            vertexIndices.push_back(indices[6]);
            textureCoordinateIndices.push_back(indices[7]); 
            normalIndices.push_back(indices[8]);
        }
        else if(std::regex_search(line, mtllibExpression)) {
            line.erase(0, 7);
            mtllibFileName = line; 
        }
    }

    std::vector<glm::vec3> outVertices; 
    std::vector<glm::vec2> outTextureCoordinates;
    std::vector<glm::vec3> outNormals;

    // Indexing the vertex, UV and normal data. 

    for(unsigned int i = 0; i < vertexIndices.size(); i++) {

        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = vertices[ vertexIndex - 1];
        outVertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < normalIndices.size(); i++) {

        unsigned int normalIndex = normalIndices[i];
        glm::vec3 normal = normals[ normalIndex - 1];
        outNormals.push_back(normal); 
    }
    for(unsigned int i = 0; i < textureCoordinateIndices.size(); i++) {

        unsigned int textureCoordinateIndex = textureCoordinateIndices[i];
        glm::vec2 textureCoordinate = textureCoordinates[ textureCoordinateIndex - 1];
        outTextureCoordinates.push_back(textureCoordinate); 
    }
    
    // Creating vertex structs.

    log(INFO, "Creating vertex structs.");

    std::vector<Vertex> tempVertices; 
    std::vector<unsigned int> indices;

    for(unsigned int i = 0; i < outVertices.size(); i++) {
        
        Vertex v; 
        v.position = outVertices[i];
        v.textureCoordinates = outTextureCoordinates[i];
        v.normal = outNormals[i];
        

        bool exists = false; 
        for(unsigned int j = 0; j < tempVertices.size(); j++) {

            if(tempVertices[j] == v) {
                indices.push_back(j); 
                exists = true; 
                break; 
            }
        }
        if(!exists) {

            tempVertices.push_back(v);
            indices.push_back(tempVertices.size() - 1);
        }
    }
    log(INFO, "Total number of indices: " + std::to_string(indices.size()));
    

    ///

    int i = 0; 
    std::cout << "Size: " << indices.size() << std::endl; 
    while(i <= indices.size() - 3) {
        glm::vec3 a = tempVertices.at(indices.at(i)).position;
        i++;
        glm::vec3 b = tempVertices.at(indices.at(i)).position; 
        i++;
        glm::vec3 c = tempVertices.at(indices.at(i)).position; 
        i++;
        glm::vec3 dir = glm::cross(b - a, c - a);
        glm::vec3 normalized = glm::normalize(dir);

        std::cout << i / 3 << ": " << normalized.x << " " << normalized.y << " " << normalized.z << " " << std::endl; 
    }



    ///
    std::regex folderExpression("^.+\\/");
    std::regex_search(filePath, match, folderExpression); 
    std::vector<Texture> textures = loadMtllib((std::string)match[0] + mtllibFileName);

    Mesh mesh("temp name", tempVertices, indices, textures);
    meshes.push_back(mesh); 
    
    log(SUCCESS, "Model loaded!"); 
};
void Model::draw(Shader& shader) {
    
    for(int i = 0; i < meshes.size(); i++) {
        meshes[i].draw(shader); 
    }
};