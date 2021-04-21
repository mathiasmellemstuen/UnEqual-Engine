#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "core/graphics/shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core/graphics/camera.h"
#include "core/log/log.h"
#include "core/graphics/texture.h"
#include "core/graphics/window.h"
#include "core/graphics/renderer.h"
#include <functional>
#include <vector>
#include "core/graphics/mesh.h"
#include "core/graphics/vertex.h"
#include <glm/vec3.hpp>
#include "core/graphics/model.h"
#include <time.h>
#include <steam/steam_api.h>

int main() {
    
    //Window class
    log(INFO, "Starting intantiation of the window context.");  
    Window window(800, 600, "Test vindu");
    log(SUCCESS, "Sucessully instantiated the window context."); 
    

    if(SteamAPI_Init()) {
    
        log(SUCCESS, "Steam API started.");

        if(SteamInput()->Init()) {
            log(SUCCESS, "Successfully initiated steamInput!");
            const char *name = SteamFriends()->GetPersonaName();
            log(INFO, "Player name: " + (std::string)name); 

        } else {
            log(ERROR, "Failed to init Steam Input."); 
        }
    }
    else {

        log(ERROR, "Failed to initialize steam api."); 
    }

    //Shader loading 
    Shader defaultShader ("assets/shaders/default.vs", "assets/shaders/default.fs"); 
    
    //Loading camera class
    Camera camera(800, 600); 
    camera.setShader(&defaultShader); 
    
    Renderer renderer(&window);

    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f)); 
    float i = 0.0; 
    float time = 0; 

    Model cube("assets/models/cube/cube.obj");

    std::function<void()> function = [&](){

        defaultShader.use(); 
        std::string s = "time";
        defaultShader.setFloat(s.c_str(),i);
        i = i + 1.0f * renderer.deltaTime;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
        glBindVertexArray(renderer.VAO);
        
        camera.setProjection(glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f)); 
        camera.setView(glm::translate(camera.getView(), glm::vec3(0.0f, 0.0f, -3.0f * renderer.deltaTime))); 
        //model = glm::translate(model, glm::vec3(0.0f,0.0f,0.0f));
        model = glm::rotate(model, 2 * 3.14f * renderer.deltaTime, glm::vec3(0.0, 1.0, 0.0));

        time += renderer.deltaTime; 

        camera.setModel(model);

        cube.draw(defaultShader); 
        
        glfwSwapBuffers(window.window);
        glfwPollEvents();
    };

    renderer.addRenderFunction(function);
    //Cleanup before terminating
    
    renderer.start(); // This function is blocking

    glfwTerminate(); 
    log(SUCCESS, "Application was successfully terminated");  
    return 0; 
}