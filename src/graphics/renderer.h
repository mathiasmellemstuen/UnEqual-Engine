#ifndef UNEQUAL_RENDERER 
#define UNEQUAL_RENDERER
#include "window.h"
#include <vector>
#include <functional>
#include "../sharedlib.h"
#include <glm/vec4.hpp>
#include <map>
#include <string>

class DLLEXPORT Renderer {
    public:
        float deltaTime;
        void addRenderFunction(std::string name, const std::function<void()> &function);
        void removeRenderFunction(std::string name); 
        Renderer(Window* window);
        void start();
        void stop();
        void setArrayBuffer(float* buffer);
        unsigned int VBO, VAO; 
        glm::vec4 clearColor;
    private:
        std::map<std::string, std::function<void()>> renderFunctions; 
        std::vector<std::string> renderFunctionsToRemove; 
        Window* window;
        bool running; 
        float lastTick;
};

#endif