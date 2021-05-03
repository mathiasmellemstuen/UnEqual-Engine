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
#include "src/geometry/geometry.h"

#define JOYSTICK 2
#define WIDTH 1920
#define HEIGHT 1080

int main() {
    
    //Window class
    log(INFO, "Starting intantiation of the window context.");  
    Window window(WIDTH, HEIGHT, "Test vindu");
    log(SUCCESS, "Sucessully instantiated the window context."); 

    Input input;
    input.setJoystickDevice(JOYSTICK); 

    //Loading shaders.
    Shader textShader("assets/shaders/text.vs", "assets/shaders/text.fs"); 
    Shader sphereShader("assets/shaders/sphere.vs", "assets/shaders/sphere.fs"); 

    //Loading camera class
    Camera camera(WIDTH, HEIGHT, &sphereShader); 
    Renderer renderer(&window);

    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, glm::vec3(1.0f, 0.0f, -5.0f)); 
    
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
    
    Texture grassTexture;
    grassTexture.createFromFile("assets/textures/grass.jpg",TextureType::DIFFUSE);

    Mesh sp = sphere(4);
    sp.textures.push_back(grassTexture); 

    std::function<void()> function = [&](){
        
        input.update();

        sphereShader.use();
        camera.setShader(&sphereShader);

        model = glm::scale(glm::mat4(1.0f), glm::vec3(40.0f, 40.0f, 40.0f));
        camera.setModel(model);
        sphereShader.setVec3("lightPos", camera.getPosition()); 
        sp.draw(sphereShader); 
        
        text.draw(textShader, "fps: " + std::to_string(int(1.0f / renderer.deltaTime)), 0.0f,HEIGHT - 40.0f,0.3f,glm::vec3(0.0f,1.0f,0.0f)); 

    };

    renderer.addRenderFunction("Hello", function);

    //Cleanup before terminating
    renderer.start(); // This function is blocking

    glfwTerminate(); 
    log(SUCCESS, "Application was successfully terminated");  
    return 0; 
}