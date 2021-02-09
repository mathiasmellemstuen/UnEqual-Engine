#ifndef TEXTURE
#define TEXTURE

#include <string>

class Texture {
    public:
        void createFromFile(std::string filePath);
        unsigned int getTextureId();
    private:
        unsigned int textureId;
};

#endif