#ifndef INPUT
#define INPUT

#include <string>
#include <glm/vec2.hpp>
#include <vector>

#include "../sharedlib.h"

class DLLEXPORT Input {
    public:
        glm::vec2 leftStick; 
        glm::vec2 rightStick;
        const unsigned char* buttons;
        void setup();
        void update(); 
};
#endif