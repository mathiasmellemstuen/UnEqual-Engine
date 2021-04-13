#include <string>
#include <iostream>
#include "shader.h"
#include "camera.h"
#include "../log/log.h"
#include "texture.h"

#include "../../thirdparty/glad/glad.h"
#include "../../thirdparty/GLFW/glfw3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../thirdparty/stb_image.h"

void Texture::createFromModel(std::string filePath, TextureType type) {
    log(INFO, "Loading and creating textures that belongs to a model"); 
    this->type = type;
    this->filePath = filePath; 

    glGenTextures(1, &textureId); 

    int width, height, nrChannels; 

    unsigned char*data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0); 

    if(data) {
        
        GLenum format; 

        if(nrChannels == 1) {
            format = GL_RED;
        } else if(nrChannels == 3) {
            format = GL_RGB; 
        } else if(nrChannels == 4) {
            format = GL_RGBA; 
        }

        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data); 
        glGenerateMipmap(GL_TEXTURE_2D); 

            //Setting texture wrapping and filtering options 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data); 
   
    } else {
        log(ERROR, "Texture failed to load at path: " + filePath); 
        stbi_image_free(data); 
    }
};
void Texture::createFromFile(std::string filePath, TextureType type) {
    log(INFO, "Loading and creating textures"); 

    this->type = type;
    this->filePath = filePath; 

    glGenTextures(1, &textureId); 
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    //Setting texture wrapping and filtering options 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   
    int width, height, nrChannels; 

    stbi_set_flip_vertically_on_load(true); 
     
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0); 
    
    //Now that the texture is bound, we can start generating it with the data we loaded. 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

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

void Texture::setTextureId(unsigned int textureId) {
    this->textureId = textureId; 
};
void Texture::setTextureType(TextureType type) {
    this->type = type; 
};
std::string Texture::getFilePath() {
    return filePath; 
};