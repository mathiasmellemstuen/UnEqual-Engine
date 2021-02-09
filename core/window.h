#ifndef WINDOW
#define WINDOW

#include "../thirdparty/linux/glad/glad.h"
#include "../thirdparty/linux/GLFW/glfw3.h"
#include <string>

class Window {
    public:
        static Window* instance; 
        Window(int width, int height, std::string title);
        void processInput();
        void setSize(int width, int height); 
        GLFWwindow* window;
    private:
        int width; 
        int height; 
        std::string title; 
};
#endif