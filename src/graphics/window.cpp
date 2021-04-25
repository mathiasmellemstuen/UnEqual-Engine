#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include "../log/log.h"
#include "window.h"

Window::Window(int width, int height, std::string title) {
    this->width = width; 
    this->height = height; 
    this->title = title;

    //Instantiating GLFW
    log(INFO, "Instantiating GLFW"); 
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        log(ERROR, "Could not initzialize glad. Exiting."); 
    }

    //Adding viewport
    glViewport(0, 0, width, height);
    
    //Adding framebuffer callback on size change.
    auto lambdaFunc = [](GLFWwindow* window, int width, int height) {
        //Window::getInstance()->setSize(width,height); 
        glViewport(0,0,width,height);
    };
    glfwSetFramebufferSizeCallback(window, lambdaFunc);


    if (window == NULL) { 
        log(ERROR, "Failed to create GLFW window");
        glfwTerminate();
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    log(SUCCESS, "Instantiated GLFW"); 
};
void Window::setSize(int width, int height) {
    this->width = width;
    this->height = height; 
};