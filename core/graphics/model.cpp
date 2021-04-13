#include "model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include "../log/log.h"
#include "mesh.h"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "texture.h"

Model::Model(char* path) {
    loadModel(path); 
};

void Model::draw(Shader &shader) {
    log(ERROR, "From drawing model!"); 
    for(unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].draw(shader);
    }
};

void Model::loadModel(std::string path) {
    Assimp::Importer import; 
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); 

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        const char* error = import.GetErrorString(); 
        log(ERROR, "ERROR::ASSIMP " + (std::string)error);
        exit(1);
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene); 
};
void Model::processNode(aiNode *node, const aiScene* scene) {
    
    log(ERROR, std::to_string(node->mNumChildren)); 

    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
                log(ERROR, std::to_string(i)); 
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
};

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices; 
    std::vector<unsigned int> indices;
    std::vector<Texture> textures; 

    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex; 

        glm::vec3 vector; 
        vector.x = mesh->mVertices[i].x; 
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;

        vertex.position = vector; 

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;


        if(mesh->mTextureCoords[0]) {
            glm::vec2 vector; 
            vector.x = mesh->mTextureCoords[0][i].x;
            vector.y = mesh->mTextureCoords[0][i].y;
            vertex.textureCoordinates = vector; 
        } else {
            vertex.textureCoordinates = glm::vec2(0.0f, 0.0f); 
        }

        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {

        aiFace face = mesh->mFaces[i];

        for(unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    if(mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex]; 

        std::vector<Texture> diffuseMaps = loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse"); 
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end()); 
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string typeName) {
    std::vector<Texture> textures;

    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++) {

        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false; 

        for(unsigned int j = 0; j < loadedTextures.size(); j++) {
            
            const char* s1 = loadedTextures[j].getFilePath().c_str();
            if(std::strcmp(s1, str.C_Str()) == 0) {
                textures.push_back(loadedTextures[j]); 
                skip = true; 
                break; 
            }
        }
        if(!skip) {
            Texture texture;
            std::string textureFile = (std::string)str.C_Str();
            std::string fullTexturePath = "assets/models/" + textureFile; 
            log(INFO, fullTexturePath);
            texture.createFromModel(fullTexturePath, typeName == "texture_diffuse" ? DIFFUSE : SPECULAR);
            textures.push_back(texture);
            loadedTextures.push_back(texture); 
        }
    }
    return textures;
};