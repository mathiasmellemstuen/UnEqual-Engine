#ifndef WINDOW
#define WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include "../sharedlib.h"

class DLLEXPORT Window {
    public:
        Window(int width, int height, std::string title);
        void setSize(int width, int height); 
        GLFWwindow* window;
    private:
        int width; 
        int height; 
        std::string title; 
};
#endif