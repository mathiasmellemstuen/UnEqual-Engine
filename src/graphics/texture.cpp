#include <string>
#include <iostream>
#include "shader.h"
#include "camera.h"
#include "../log/log.h"
#include "texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void Texture::createFromFile(std::string filePath, TextureType type) {
    log(INFO, "Loading and creating textures"); 

    this->type = type;
    this->filePath = filePath; 
    
    log(INFO, "Filepath: " + filePath);
    log(INFO, "Type: " + (std::string)(type == DIFFUSE ? "Diffuse" : "Specular")); 

    glGenTextures(1, &textureId); 
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    //Setting texture wrapping and filtering options 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   
    int width, height, nrChannels; 

    stbi_set_flip_vertically_on_load(false);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0); 

    log(INFO, "Height:" + std::to_string(height));
    log(INFO, "Width: " + std::to_string(width));

    //Now that the texture is bound, we can start generating it with the data we loaded. 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    log(INFO, "Reaching this."); 

    glActiveTexture(GL_TEXTURE0); 
    glGenerateMipmap(GL_TEXTURE_2D); 

    //Freeing the image memory sice we are done with it. 
    stbi_image_free(data);
    log(SUCCESS, "Successfully loaded texture from file!"); 
};

unsigned int Texture::getTextureId() {
    return this->textureId; 
};

TextureType Texture::getTextureType() {
    return this->type; 
};
std::string Texture::getFilePath() {
    return filePath; 
};