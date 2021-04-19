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

    log(INFO, "Started loading model: " + filePath); 
    std::vector<MeshData> meshDataList; 
    std::ifstream file(filePath);
    std::string line; 

    std::regex mtllibExpression("^mtllib");
    std::regex findNumericValueExpression("[+-]?([0-9]*[.])?[0-9]+");
    std::regex findMeshNameExpression("([^\\s]+)$");
    std::smatch match;

    std::string mtllibFileName; 

    while(std::getline(file, line)) {

        if(line[0] == 'o') {
            line.erase(0,2);
            log(INFO, "Adding mesh: " + line);
            MeshData data; 
            data.name = line; 
            meshDataList.push_back(data); 
            continue; 
        }

        if(meshDataList.size() == 0) {
            MeshData data; 
            data.name = "Undefined name."; 
            meshDataList.push_back(data); 
        }

        if(line[0] == '#') {
            continue; 
        }
        
        if(std::regex_search(line, mtllibExpression)) {
            line.erase(0, 7);
            mtllibFileName = line; 
            continue; 
        }

        if(line[0] == 'v' && line[1] == ' ') {
            int i = 0; 
            glm::vec3 vertex; 
            while(std::regex_search(line, match, findNumericValueExpression)) {
                vertex[i] = std::stof(match[0]);
                line = match.suffix();
                i++; 
            }

            meshDataList[meshDataList.size() - 1].vertices.push_back(vertex); 
            continue; 
        }

        if(line[0] == 'v' && line[1] == 't') {
            int i = 0; 
            glm::vec2 textureCoordinate; 

            while(std::regex_search(line, match, findNumericValueExpression)) {
                textureCoordinate[i] = std::stof(match[0]); 
                line = match.suffix();
                i++; 
            }

            meshDataList[meshDataList.size() - 1].textureCoordinates.push_back(textureCoordinate); 
            continue; 
        }

        if(line[0] == 'v' && line[1] == 'n') {
            int i = 0; 
            glm::vec3 normal; 

            while(std::regex_search(line, match, findNumericValueExpression)) {
                normal[i] = std::stof(match[0]); 
                line = match.suffix(); 
                i++;
            }

            meshDataList[meshDataList.size() - 1].normals.push_back(normal);
            continue; 
        }

        if(line[0] == 'f') {
            
            while(std::regex_search(line, match, findNumericValueExpression)) {
                meshDataList[meshDataList.size() - 1].faces.push_back(std::stoul(match[0])); 
                line = match.suffix(); 
            }
            continue; 
        }
    }

    std::regex folderExpression("^.+\\/");
    std::regex_search(filePath, match, folderExpression); 
    std::vector<Texture> textures = loadMtllib((std::string)match[0] + mtllibFileName);
    log(SUCCESS, "Loaded model.");

    for(int i = 0; i < meshDataList.size(); i++) {
        
        std::vector<Vertex> vertices;

        for(int j = 0; j < meshDataList[i].faces.size(); j+3) {
            Vertex v;
            v.position = meshDataList[i].vertices[meshDataList[i].faces[j]];
            v.textureCoordinates = meshDataList[i].textureCoordinates[meshDataList[i].faces[j] + 1];
            v.normal = meshDataList[i].normals[meshDataList[i].faces[j] + 2];
        }

        Mesh mesh(meshDataList[i].name, vertices, meshDataList[i].faces, textures);
    }
    //log(SUCCESS, "Loaded model " + filePath + " with: " + std::to_string(modelData.vertices.size()) + " vertices, " + std::to_string(modelData.normals.size()) + " normals, " + std::to_string(modelData.textureCoordinates.size()) + " texture coordinates and " + std::to_string(modelData.indices.size()) + " indices."); 
};

void Model::draw(Shader& shader) {

    for(int i = 0; i < meshes.size(); i++) {
        meshes[i].draw(shader); 
    }
};