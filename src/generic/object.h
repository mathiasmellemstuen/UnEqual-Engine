#ifndef OBJECT 
#define OBJECT


#include "../graphics/renderer.h"
#include "../input/input.h"
#include "../sharedlib.h"
#include <glm/glm.hpp>
#include <string>

class DLLEXPORT Object {
    public:
        Object(Renderer* renderer, Input* input);
        glm::mat4 model;
    protected: 
        Renderer* renderer; 
        Input* input;
        std::string address;
};

#endif