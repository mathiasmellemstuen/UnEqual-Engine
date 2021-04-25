#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "src/graphics/shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "src/graphics/camera.h"
#include "src/log/log.h"
#include "src/graphics/texture.h"
#include "src/graphics/window.h"
#include "src/graphics/renderer.h"
#include <functional>
#include <vector>
#include "src/graphics/mesh.h"
#include "src/graphics/vertex.h"
#include <glm/vec3.hpp>
#include "src/graphics/model.h"
#include <time.h>
#include "src/input/input.h"
#include "src/graphics/text.h"

#define WIDTH 2560
#define HEIGHT 1440

int main() {
    
    //Window class
    log(INFO, "Starting intantiation of the window context.");  
    Window window(WIDTH, HEIGHT, "Test vindu");
    log(SUCCESS, "Sucessully instantiated the window context."); 

    Input input;
    input.setup(); 
    
    //Shader loading 
    Shader defaultShader ("assets/shaders/default.vs", "assets/shaders/default.fs"); 
    Shader strangeShader("assets/shaders/strangeFigure.vs", "assets/shaders/strangeFigure.fs"); 
    //Loading camera class

    Camera camera(WIDTH, HEIGHT, &strangeShader); 
    
    Renderer renderer(&window);

    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, glm::vec3(1.0f, 0.0f, -5.0f)); 

    glm::mat4 model2 = glm::mat4(1); 
    model2 = glm::translate(model2, glm::vec3(10.0f, 0.0f, -5.0f)); 
    
    float time = 0.0; 

    Model cube("assets/models/cube/cube.obj");

    Model strangeFigure("assets/models/strangeFigure/strangeFigure.obj");
    
    Shader textShader("assets/shaders/text.vs", "assets/shaders/text.fs"); 
    Text text(WIDTH, HEIGHT);

    std::function<void()> function = [&](){
        
        input.update();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
        glBindVertexArray(renderer.VAO);
        strangeShader.use();
        camera.setShader(&strangeShader);
        strangeShader.setVec3("lightPos", camera.getPosition());
        camera.setModel(model);
        strangeFigure.draw(strangeShader);



        float speed =  20.0f * renderer.deltaTime;
        float y = input.buttons[7] == GLFW_PRESS ? 1.0f : input.buttons[6] == GLFW_PRESS ? -1.0f : 0.0f;
        camera.move(glm::vec3(input.leftStick.x, y, input.leftStick.y), glm::vec3(90.0f * input.rightStick.x * renderer.deltaTime, 90.0f * input.rightStick.y * renderer.deltaTime, 0.0f), speed);

        std::string s = "time";
        time = time + 1.0f * renderer.deltaTime;

        defaultShader.use(); 
        defaultShader.setFloat(s.c_str(),time);
        camera.setShader(&defaultShader); 
        camera.setModel(model2); 
        cube.draw(defaultShader);

        text.draw(textShader, "fps: " + std::to_string(int(1.0f / renderer.deltaTime)), 0.0f,HEIGHT - 40.0f,0.3f,glm::vec3(0.0f,1.0f,0.0f)); 

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