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
#include "core/input/input.h"

int main() {
    
    //Window class
    log(INFO, "Starting intantiation of the window context.");  
    Window window(2560, 1440, "Test vindu");
    log(SUCCESS, "Sucessully instantiated the window context."); 

    Input input;
    input.setup(); 
    
    //Shader loading 
    Shader defaultShader ("assets/shaders/default.vs", "assets/shaders/default.fs"); 
    
    //Loading camera class
    Camera camera(2560, 1440, &defaultShader); 
    
    Renderer renderer(&window);

    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f)); 
    float i = 0.0; 
    float time = 0; 

    Model cube("assets/models/cube/cube.obj");
    std::function<void()> function = [&](){
        input.update(); 
        defaultShader.use(); 
        std::string s = "time";
        defaultShader.setFloat(s.c_str(),i);
        i = i + 1.0f * renderer.deltaTime;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
        glBindVertexArray(renderer.VAO);

        //camera.setPosition(camera.getPosition() + glm::vec3(0.0f, 0.0f, -1.0f * renderer.deltaTime)); 
        //camera.setView(glm::translate(camera.getView(), glm::vec3(20.0f * -input.leftStick.x * renderer.deltaTime, 0.0f, 20.0f * -input.leftStick.y * renderer.deltaTime)));
        //glm::mat4 cameraModel = camera.getModel(); 
        //cameraModel = glm::rotate(cameraModel, 2.0f * 3.14f * renderer.deltaTime, glm::vec3(-input.rightStick.x,-input.rightStick.y, 0.0f));
        //camera.setModel(cameraModel);
        //model = glm::translate(model, glm::vec3(0.0f,0.0f,0.0f));
        //model = glm::rotate(model, 2 * 3.14f * renderer.deltaTime, glm::vec3(0.0, 1.0, 0.0));
        float speed = 2.0f * 3.14f * renderer.deltaTime; 
        //camera.rotate(glm::vec2(-input.rightStick.x, -input.rightStick.y), glm::vec2(speed, speed));

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