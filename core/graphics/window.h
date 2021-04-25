#ifndef WINDOW
#define WINDOW

#include "../../thirdparty/glad/glad.h"
#include "../../thirdparty/GLFW/glfw3.h"
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