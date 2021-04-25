#include "text.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "shader.h" 
#include "../log/log.h"
#include <map>
#include "renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

Text::Text(int windowWidth, int windowHeight) {

    this->windowWidth = windowWidth; 
    this->windowHeight = windowHeight; 
    
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        log(ERROR, "ERROR::FREETYPE: Could not init FreeType Library");
    }

    FT_Face face;
    if (FT_New_Face(ft, "assets/fonts/Roboto/Roboto-Black.ttf", 0, &face)) {
        log(ERROR, "ERROR::FREETYPE: Failed to load font");
    } else {
        FT_Set_Pixel_Sizes(face, 0, 48); 

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 

        for(unsigned char c = 0; c < 128; c++) {

            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                log(ERROR, "ERROR::FREETYTPE: Failed to load Glyph: " + std::to_string(c));
                continue;
            }

            unsigned int texture; 

            glGenTextures(1, &texture); 
            glBindTexture(GL_TEXTURE_2D, texture); 
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int> (face->glyph->advance.x)
            };
            characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0); 
    }
    FT_Done_Face(face); 
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
};

void Text::draw(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color) {
    shader.use();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(windowWidth), 0.0f, static_cast<float>(windowHeight));
    glUniformMatrix4fv(glGetUniformLocation(shader.id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(shader.id, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
    std::string::const_iterator c; 

    for(c = text.begin(); c != text.end(); c++) {
        Character ch = characters[*c];
        float xPos = x + ch.bearing.x * scale; 
        float yPos = y - (ch.size.y - ch.bearing.y) * scale; 

        float w = ch.size.x * scale; 
        float h = ch.size.y * scale; 

        float vertices[6][4] = {
            { xPos,     yPos + h,   0.0f, 0.0f },            
            { xPos,     yPos,       0.0f, 1.0f },
            { xPos + w, yPos,       1.0f, 1.0f },

            { xPos,     yPos + h,   0.0f, 0.0f },
            { xPos + w, yPos,       1.0f, 1.0f },
            { xPos + w, yPos + h,   1.0f, 0.0f }           
        };
        glBindTexture(GL_TEXTURE_2D, ch.textureId); 
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (ch.advance >> 6) * scale;
    }
    glBindVertexArray(0); 
    glBindTexture(GL_TEXTURE_2D, 0); 
};