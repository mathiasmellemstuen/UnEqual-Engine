#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include "log.h"
#include "texture.h"
#include "window.h"
#include "renderer.h"

int main() {
    
    float verticies[] = {

    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
}; 
    //Window class
    log(INFO, "Starting intantiation of the window context.");  
    Window window(800, 600, "Test vindu");
    log(SUCCESS, "Sucessully instantiated the window context."); 
    
    //Shader loading 
    Shader defaultShader ("shaders/default.vs", "shaders/default.fs"); 
    
    //Texture loading
    Texture texture;
    texture.createFromFile("textures/wall.jpeg", DIFFUSE); 
    defaultShader.use(); 
    defaultShader.setInt("texture", 0); 
    glBindTexture(GL_TEXTURE_2D, texture.getTextureId()); 

    //Loading camera class
    Camera camera(800, 600); 
    camera.setShader(&defaultShader); 
    
    //Starting to render
    Renderer renderer(Window::instance);
    
    auto function = [&](){
        
        glClearColor(0.2f,0.4f,0.2f,0.2f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glBindVertexArray(Renderer::instance->VAO);
        
        camera.setProjection(glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f)); 
        camera.setView(glm::translate(camera.getView(), glm::vec3(0.0f, 0.0f, -0.01f))); 

        glm::mat4 model = glm::mat4(1); 
        model = glm::translate(model, glm::vec3(0.0f,0.0f,0.0f));
        
        camera.setModel(model);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        defaultShader.use(); 

        glfwSwapBuffers(Window::instance->window);
        glfwPollEvents();
    };

    renderer.addRenderFunction(function);
    
    //Cleanup before terminating
    glfwTerminate(); 

    log(SUCCESS, "Application was successfully terminated");  
    return 0; 
}