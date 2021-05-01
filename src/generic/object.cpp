#include "object.h"
#include "../graphics/renderer.h"
#include "../input/input.h"

Object::Object(Renderer* renderer, Input* input) {
    this->renderer = renderer; 
    this->input = input; 
    this->model = glm::mat4(1.0f); 
}