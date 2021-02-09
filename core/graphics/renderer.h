#ifndef RENDERER 
#define RENDERER
#include "../window.h"

class Renderer {
    public:
        Renderer(Window* window);
        void stop();
        bool nextRenderCall();
        void setArrayBuffer(float* buffer);
    private:
        Window* window;
        bool running; 
        unsigned int VBO, VAO; 
};

#endif