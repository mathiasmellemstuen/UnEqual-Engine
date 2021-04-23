#include "core/graphics/window.h"
#include "core/input/input.h"
#include "core/log/log.h"
#include "core/graphics/camera.h"
#include "core/graphics/model.h"
#include "core/graphics/renderer.h"
#include "core/graphics/shader.h"
#include "core/graphics/text.h"
#include "core/graphics/texture.h"
#include "snake/sphere.h"
#include <string>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WIDTH 2560
#define HEIGHT 1444

int main() {
    
    Window window(WIDTH, HEIGHT, "Snakeception");

    Input input; 
    input.setup(); 

    Renderer renderer(&window);

    Shader strangeShader("assets/shaders/strangeFigure.vs", "assets/shaders/strangeFigure.fs"); 
    Shader textShader("assets/shaders/text.vs", "assets/shaders/text.fs"); 

    Text text(WIDTH, HEIGHT); 
    Camera camera(WIDTH, HEIGHT, &strangeShader);

    std::function<void()> processInputAndClearScreen = [&](){
        
        input.update();

        glfwSwapBuffers(window.window);
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        text.draw(textShader, " PRE-ALPHA BUILD 1.0 - " + std::to_string(int(1.0f / renderer.deltaTime)) + " fps - " + std::to_string(renderer.deltaTime) + " dt",0.0f,HEIGHT - 45.0f, 0.35f,glm::vec3(1.0f,1.0f,1.0f));
    };

    Mesh m = generateSphere();
    Model cube("assets/models/cube/cube.obj");

    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model,glm::vec3(0.0f,0.0f,-5.0f));
    std::function<void()> renderSphere = [&]() {


        strangeShader.use();
        strangeShader.setVec3("lightPos", camera.getPosition());
        m.draw(strangeShader);
        camera.setModel(model); 
        cube.draw(strangeShader); 

        camera.setShader(&strangeShader); 
        float speed =  20.0f * renderer.deltaTime;
        float y = input.buttons[7] == GLFW_PRESS ? 1.0f : input.buttons[6] == GLFW_PRESS ? -1.0f : 0.0f;
        camera.move(glm::vec3(input.leftStick.x, y, input.leftStick.y), glm::vec3(90.0f * input.rightStick.x * renderer.deltaTime, 90.0f * input.rightStick.y * renderer.deltaTime, 0.0f), speed);
    };

    renderer.addRenderFunction(processInputAndClearScreen); 
    renderer.addRenderFunction(renderSphere); 

    renderer.start(); 
    return 0; 
}