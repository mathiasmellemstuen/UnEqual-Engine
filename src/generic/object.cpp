#include "object.h"
#include "../graphics/renderer.h"
#include "../input/input.h"
#include <sstream>
#include <string>
Object::Object(Renderer* renderer, Input* input) {
    this->renderer = renderer; 
    this->input = input; 
    this->model = glm::mat4(1.0f); 

    std::ostringstream addressStream; 
    addressStream << this;
    this->address = addressStream.str(); 
}