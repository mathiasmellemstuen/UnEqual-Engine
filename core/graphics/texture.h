#ifndef TEXTURE
#define TEXTURE

#include <string>

#include "../sharedlib.h"

enum TextureType {
    DIFFUSE,
    SPECULAR
};


class DLLEXPORT Texture {
    public:
        void createFromFile(std::string filePath, TextureType type);
        unsigned int getTextureId();
        TextureType getTextureType();
        std::string getFilePath(); 
        
    private:
        unsigned int textureId;
        TextureType type;
        std::string filePath;
};
#endif