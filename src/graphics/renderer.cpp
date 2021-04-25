#include "renderer.h"
#include "../log/log.h"
#include "window.h"
#include <functional>
#include <chrono>

Renderer::Renderer(Window* window) {

    this->window = window; 
    this->running = true;

    //Initializing glad
    log(INFO, "Instantiating GLAD"); 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        log(ERROR, "Failed to instantiate GLAD"); 
    }
    log(SUCCESS, "Instantiated GLAD"); 
    glEnable(GL_DEPTH_TEST);   


    //Generating a buffer ID and assigning it to VBO, VAO, EBO variables. 
    log(INFO, "Generating buffer IDs and assigning it to VBO, VAO, EBO"); 
    
    glGenBuffers(1, &VBO);  
    glGenVertexArrays(1,&VAO); 
    //glGenBuffers(1, &EBO);

    glBindVertexArray(VAO); 

    glBindBuffer(GL_ARRAY_BUFFER, VBO); 

    log(SUCCESS, "Done generating buffer IDs");


    log(INFO, "Giving OpenGL info about the intepretation of the vertex data"); 
    //Telling OpenGL how it should interpret the vertex data:
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); 
    glEnableVertexAttribArray(1); 
};
int Renderer::addRenderFunction(const std::function<void()> &function) {
    renderFunctions.push_back(function); 
    return -1; 
};
void Renderer::removeRenderFunction(int renderFunctionId) {
    renderFunctions.erase(renderFunctions.begin() + renderFunctionId);
};

void Renderer::start() {
    log(INFO, "Starting rendering loop."); 

    std::chrono::high_resolution_clock::time_point lastTick = std::chrono::high_resolution_clock::now();

    while(this->running && !glfwWindowShouldClose(this->window->window)) {
        //Render loop

        std::chrono::duration<float, std::milli> dt = std::chrono::high_resolution_clock::now() - lastTick;
        lastTick = std::chrono::high_resolution_clock::now(); 
        deltaTime = dt.count() / 1000;

        //Looping through every rendering functions and running them. 
        for(std::function<void()> function : renderFunctions) {
            function();
        }
    }
}
void Renderer::stop() {
    this->running = false; 
};

void Renderer::setArrayBuffer(float* buffer) {

    log(INFO, "Trying to assign buffer."); 

    glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
    
    log(SUCCESS, "Assigned buffer."); 
};