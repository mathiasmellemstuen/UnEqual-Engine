#ifndef INPUT
#define INPUT

#include <string>
#include <steam/steam_api.h>
#include <glm/vec2.hpp>
#include <vector>

class Input {
    public:
        glm::vec2 leftStick; 
        glm::vec2 rightStick;
        const unsigned char* buttons;
        void setup();
        void update(); 
};
#endif