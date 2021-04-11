#ifndef UNEQUAL_RENDERER 
#define UNEQUAL_RENDERER
#include "window.h"
#include <vector>
#include <functional>

class Renderer {
    public:
        int addRenderFunction(const std::function<void()> &function);
        void removeRenderFunction(int renderFunctionId); 
        Renderer(Window* window);
        void start();
        void stop();
        void setArrayBuffer(float* buffer);
        unsigned int VBO, VAO; 
    private:
        std::vector<std::function<void()>> renderFunctions;
        Window* window;
        bool running; 
};

#endif