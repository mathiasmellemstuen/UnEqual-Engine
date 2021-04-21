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

int main() {

    //Window class
    log(INFO, "Starting intantiation of the window context.");  
    Window window(800, 600, "Test vindu");
    log(SUCCESS, "Sucessully instantiated the window context."); 
    
    //Shader loading 
    Shader defaultShader ("assets/shaders/default.vs", "assets/shaders/default.fs"); 
    
 //   //Texture loading
  //  Texture texture;
   // texture.createFromFile("assets/textures/wall.jpeg", DIFFUSE); 
    //defaultShader.use(); 
    //defaultShader.setInt("texture", 0); 
    //glBindTexture(GL_TEXTURE_2D, texture.getTextureId()); 

    //Loading camera class
    Camera camera(800, 600); 
    camera.setShader(&defaultShader); 
    
    //std::vector<Texture> textures = {texture};
    //std::vector<unsigned int> indices;
    Renderer renderer(&window);
    //Starting to render

   // Model backpack("assets/models/backpack.obj");

    glm::mat4 model = glm::mat4(1);
    glm::mat4 model2 = glm::mat4(1);
    model2 = glm::translate(model, glm::vec3(-3.0f,0.0f,0.0f)); 
    

    float i = 0.0; 
    Model cube("assets/models/cube/cube.obj");
    std::function<void()> function = [&](){

        window.processInput(); 

        defaultShader.use(); 
        std::string s = "time";
        defaultShader.setFloat(s.c_str(),i);
        i = i + 0.1f; 

        log(INFO, std::to_string(i)); 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
        glBindVertexArray(renderer.VAO);
        
        camera.setProjection(glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f)); 
        camera.setView(glm::translate(camera.getView(), glm::vec3(0.0f, 0.0f, -0.01f))); 
        //model = glm::translate(model, glm::vec3(0.0f,0.0f,0.0f));
        model = glm::rotate(model, 0.01f, glm::vec3(0.0, 1.0, 0.0));

        camera.setModel(model);
       // backpack.draw(defaultShader);
        cube.draw(defaultShader); 
        camera.setModel(model2); 
       // backpack.draw(defaultShader); 
        
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