#ifndef INPUT
#define INPUT

#include <string>
#include <steam/steam_api.h>
#include <glm/vec2.hpp>

class Input {
    public:
        glm::vec2 leftStick; 
        glm::vec2 rightStick;
        void setup();
        void update(); 
};
#endif