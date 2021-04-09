#include "../../thirdparty/glad/glad.h"
#include "../../thirdparty/GLFW/glfw3.h"
#include <string>
#include "log/log.h"
#include "window.h"

Window::Window(int width, int height, std::string title) {
    instance = this; 
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
    
    //Adding viewport
    glViewport(0, 0, width, height);
    //Adding framebuffer callback on size change.
     
    auto lambdaFunc = [](GLFWwindow* window, int width, int height) {
        Window::instance->setSize(width,height); 
        glViewport(0,0,width,height);
    };
    glfwSetFramebufferSizeCallback(window, lambdaFunc);


    if (window == NULL) { 
        log(ERROR, "Failed to create GLFW window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    log(SUCCESS, "Instantiated GLDW"); 
};
void Window::processInput() {

    //Checking if the escape key was pressed and closing the window if that's the case. 
    if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, true); 
}; 
void Window::setSize(int width, int height) {
    this->width = width;
    this->height = height; 
};