#ifndef UNEQUAL_RENDERER 
#define UNEQUAL_RENDERER
#include "window.h"
#include <vector>

using RenderFunction = []void ()->void;

class Renderer {
    public:
        static Renderer* instance;
        int addRenderFunction(RenderFunction function); 
        void removeRenderFunction(int renderFunctionId); 
        Renderer(Window* window);
        void start();
        void stop();
        void setArrayBuffer(float* buffer);
        unsigned int VBO, VAO; 
    private:
        std::vector<RenderFunction> renderFunctions;
        Window* window;
        bool running; 
};

#endif