#ifndef TEXT
#define TEXT

#include <glm/glm.hpp>
#include "shader.h"
#include <string>
#include <ft2build.h>
#include <map>
#include "renderer.h"

#include FT_FREETYPE_H

#include "../sharedlib.h"

struct Character {
    unsigned int textureId; 
    glm::ivec2 size; 
    glm::ivec2 bearing; 
    unsigned int advance; 
};


class DLLEXPORT Text {
    public:

        void draw(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);
        Text(int windowWidth, int windowHeight); 
    private:
        unsigned int VAO, VBO;
        std::map<GLchar, Character> characters;
        int windowWidth, windowHeight;
};

#endif