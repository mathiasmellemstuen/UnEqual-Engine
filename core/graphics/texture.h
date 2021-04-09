#ifndef TEXTURE
#define TEXTURE

#include <string>

enum TextureType {
    DIFFUSE,
    SPECULAR
};

class Texture {
    public:
        void createFromFile(std::string filePath, TextureType type);
        unsigned int getTextureId();
        TextureType getTextureType();
    private:
        unsigned int textureId;
        TextureType type;
};
#endif