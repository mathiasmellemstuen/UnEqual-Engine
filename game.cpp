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

#define WIDTH 1920
#define HEIGHT 1080

Mesh generateSphereFromIcosahedron(Model icosahedron, int passes) {

    std::vector<unsigned int> startingIndices = icosahedron.meshes.at(0).indices;
    std::vector<Vertex> startingVertices = icosahedron.meshes.at(0).verticies;
    std::vector<unsigned int> indices; 
    std::vector<Vertex> vertices; 
    for(int i = 0; i < startingIndices.size(); i+=3) {
        
        glm::vec3 v0 = startingVertices.at(startingIndices.at(i)).position;
        glm::vec3 v1 = startingVertices.at(startingIndices.at(i + 1)).position; 
        glm::vec3 v2 = startingVertices.at(startingIndices.at(i + 2)).position;

        glm::vec3 v3 = glm::normalize(0.5f * (v0 + v1)); 
        glm::vec3 v4 = glm::normalize(0.5f * (v1 + v2)); 
        glm::vec3 v5 = glm::normalize(0.5f * (v2 + v0));  
    }
    return Mesh("Sphere", vertices, indices, std::vector<Texture>{});
}
int main() {
    
    //Window class
    log(INFO, "Starting intantiation of the window context.");  
    Window window(WIDTH, HEIGHT, "Test vindu");
    log(SUCCESS, "Sucessully instantiated the window context."); 

    Input input;
    
    //Shader loading 
    Shader defaultShader ("assets/shaders/default.vs", "assets/shaders/default.fs"); 
    Shader strangeShader("assets/shaders/strangeFigure.vs", "assets/shaders/strangeFigure.fs"); 
    //Loading camera class

    Camera camera(WIDTH, HEIGHT, &strangeShader); 
    
    Renderer renderer(&window);

    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, glm::vec3(1.0f, 0.0f, -5.0f)); 

    Model cube("assets/models/cube/cube.obj");

    Model strangeFigure("assets/models/strangeFigure/strangeFigure.obj");
    
    Model icosahedron("assets/models/Icosahedron/icosahedron.obj"); 

    Shader icosahedronShader("assets/shaders/icosahedron.vs", "assets/shaders/icosahedron.fs", "assets/shaders/icosahedron.gs");
    Shader textShader("assets/shaders/text.vs", "assets/shaders/text.fs"); 
    Text text(WIDTH, HEIGHT);

    float ySpeed = 0.0f; 

    std::function<void(float* value, int maxCount)> movementListener = [&](float* values, int maxCount) {
        
        float speed =  20.0f * renderer.deltaTime;
        camera.move(glm::vec3(values[0], ySpeed, values[1]), glm::vec3(180.0f * values[2] * renderer.deltaTime, 180.0f * values[3] * renderer.deltaTime, 0.0f), speed);
    };
    
    std::function<void(bool* value, int maxCount)> moveYdirection = [&](bool* values, int maxCount) {
        ySpeed = values[7] ? 1.0f : values[6] ? -1.0f : 0.0f; 
    };
    input.addDigitalListener(moveYdirection); 
    input.addAnalogListener(movementListener); 

    std::function<void()> function = [&](){
        
        input.update();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
        glBindVertexArray(renderer.VAO);

        icosahedronShader.use();
        camera.setShader(&icosahedronShader);

        model = glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, 20.0f, 20.0f));
        camera.setModel(model);
        icosahedronShader.setVec3("lightPos", camera.getPosition()); 
        icosahedron.draw(icosahedronShader); 
        
        // strangeShader.use(); 
        // camera.setShader(&strangeShader); 
        // strangeShader.setVec3("lightPos", camera.getPosition()); 
        // camera.setModel(model);
        // strangeFigure.draw(strangeShader); 

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