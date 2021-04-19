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

    std::ifstream file(filePath); 
    std::string line; 
    std::regex map_kdExpression("^map_Kd ");
    std::regex map_BumpExpression("^map_Bump ");
    std::regex map_KsExpression("^map_Ks");
    std::smatch match;
   
    std::string mapKd; 
    std::string mapBump; 
    std::string mapKs; 
    
    while(std::getline(file, line)) {

        if(std::regex_search(line, map_kdExpression)) {
            line.erase(0,7);
            mapKd = line; 
            continue; 
        }

        if(std::regex_search(line, map_BumpExpression)) {
            line.erase(0,9);
            mapBump = line; 
            continue; 
        }

        if(std::regex_search(line, map_KsExpression)) {
            line.erase(0,7);
            mapKs = line; 
            continue; 
        }
    }

    std::regex folderExpression("^.+\\/");
    std::regex_search(filePath, match, folderExpression);
    mapKd = (std::string)match[0] + mapKd;
    mapBump = (std::string)match[0] + mapBump;
    mapKs = (std::string)match[0] + mapKs;  
    
    log(INFO, mapKd); 
    log(INFO, mapBump); 
    log(INFO, mapKs);

    Texture diffuse;
    diffuse.createFromFile(mapKd, DIFFUSE); 

    Texture specular; 
    specular.createFromFile(mapKs, SPECULAR);
    std::vector<Texture> textures = {diffuse, specular}; 

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
    std::vector<Vertex> tempVertices; 

    for(unsigned int i = 0; i < outVertices.size(); i++) {
        
        Vertex v; 
        v.position = outVertices[i];
        v.textureCoordinates = outTextureCoordinates[i];
        v.normal = outNormals[i];  
    }

    //TODO: Generating indices
    std::vector<unsigned int> indices;

//    for(unsigned int i = 0; i < tempVertices.size(); i++) {
//        indices.push_back(i);
//        for(unsigned int j = 0; j < tempVertices.size(); j++) {
//            if(i != j) {
//
//            }
//        }
//    }
    std::regex folderExpression("^.+\\/");
    std::regex_search(filePath, match, folderExpression); 
    std::vector<Texture> textures = loadMtllib((std::string)match[0] + mtllibFileName);

    Mesh mesh("temp name", tempVertices, indices, textures);
    meshes.push_back(mesh); 
    
    log(INFO, "This model has: " + std::to_string(outVertices.size()) + " vertices, " + std::to_string(outTextureCoordinates.size()) + " texture coordinates and " + std::to_string(outNormals.size()) +  " normals.");
    log(SUCCESS, "Model loaded!"); 
};

//
//    log(INFO, "Started loading model: " + filePath); 
//    std::ifstream file(filePath);
//    std::string line; 
//
//    std::regex mtllibExpression("^mtllib");
//    std::regex findNumericValueExpression("[+-]?([0-9]*[.])?[0-9]+");
//    std::regex findMeshNameExpression("([^\\s]+)$");
//    std::smatch match;
//
//    std::string mtllibFileName;
//    
//    std::vector<glm::vec3> positions; 
//    std::vector<glm::vec2> textureCoordinates; 
//    std::vector<glm::vec3> normals;
//    std::vector<Vertex> currentMeshVertices; 
//    std::string currentMeshName; 
//    while(std::getline(file, line)) {
//
//        if(line[0] == 'o') {
//            line.erase(0,2);
//            log(INFO, "Adding mesh: " + line);
//            currentMeshName = line; 
//            continue; 
//        }
//
//        if(line[0] == '#') {
//            continue; 
//        }
//        
//        if(std::regex_search(line, mtllibExpression)) {
//            line.erase(0, 7);
//            mtllibFileName = line; 
//            continue; 
//        }
//
//        if(line[0] == 'v' && line[1] == ' ') {
//            int i = 0; 
//            glm::vec3 vertex; 
//            while(std::regex_search(line, match, findNumericValueExpression)) {
//                vertex[i] = std::stof(match[0]);
//                line = match.suffix();
//                i++; 
//            }
//            positions.push_back(vertex); 
//            continue; 
//        }
//
//        if(line[0] == 'v' && line[1] == 't') {
//            int i = 0; 
//            glm::vec2 textureCoordinate; 
//
//            while(std::regex_search(line, match, findNumericValueExpression)) {
//                textureCoordinate[i] = std::stof(match[0]); 
//                line = match.suffix();
//                i++; 
//            }
//            textureCoordinates.push_back(textureCoordinate);
//            continue; 
//        }
//
//        if(line[0] == 'v' && line[1] == 'n') {
//            int i = 0; 
//            glm::vec3 normal; 
//
//            while(std::regex_search(line, match, findNumericValueExpression)) {
//                normal[i] = std::stof(match[0]); 
//                line = match.suffix(); 
//                i++;
//            }
//            normals.push_back(normal); 
//            continue; 
//        }
//
//        if(line[0] == 'f') {
//            while(std::regex_search(line, match, findNumericValueExpression)) {
//                face = std::stoul(match[0]); 
//                line = match.suffix(); 
//            }
//            continue; 
//        }
//    }
//
//    std::regex folderExpression("^.+\\/");
//    std::regex_search(filePath, match, folderExpression); 
//    std::vector<Texture> textures = loadMtllib((std::string)match[0] + mtllibFileName);
//    log(SUCCESS, "Loaded model.");
//    
//    log(INFO, std::to_string(meshDataList.at(1).vertices.size()));
//
//    log(INFO, "Total meshes to process: " + std::to_string(meshDataList.size())); 
//    for(int i = 1; i < meshDataList.size(); i++) {
//
//        std::vector<Vertex> vertices;
//        log(INFO, "Processing mesh: " + std::to_string(i) + "/" + std::to_string(meshDataList.size()));
//        for(int j = 0; j < meshDataList.at(i).faces.size() - 4; j+=3) {
//
//            if(meshDataList.at(i).vertices.size() == 0 || meshDataList.at(i).textureCoordinates.size() == 0 || meshDataList.at(i).normals.size() == 0) {
//                log(ERROR, "Wrong amount of elements at: " + std::to_string(i)); 
//                continue; 
//            }
//
//            Vertex v;
//            v.position = meshDataList.at(i).vertices.at(meshDataList.at(i).faces.at(j) - 1);
//
//            log(INFO, "1"); 
//            v.textureCoordinates = meshDataList.at(i).textureCoordinates.at(meshDataList.at(i).faces.at(j) + 1 - 1);
//            log(INFO, "2"); 
//            v.normal = meshDataList.at(i).normals.at(meshDataList.at(i).faces.at(j) + 2 - 1);
//            log(INFO, "3");  
//        }
//        log(SUCCESS, "Adding mesh."); 
//        Mesh mesh(meshDataList[i].name, vertices, meshDataList[i].faces, textures);
//        meshes.push_back(mesh); 
//    }
    //log(SUCCESS, "Loaded model " + filePath + " with: " + std::to_string(modelData.vertices.size()) + " vertices, " + std::to_string(modelData.normals.size()) + " normals, " + std::to_string(modelData.textureCoordinates.size()) + " texture coordinates and " + std::to_string(modelData.indices.size()) + " indices."); 
//};

void Model::draw(Shader& shader) {

    for(int i = 0; i < meshes.size(); i++) {
        meshes[i].draw(shader); 
    }
};