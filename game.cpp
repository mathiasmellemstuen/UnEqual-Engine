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
#include <ft2build.h>
#include FT_FREETYPE_H

int main() {
    
    //Window class
    log(INFO, "Starting intantiation of the window context.");  
    Window window(2560, 1440, "Test vindu");
    log(SUCCESS, "Sucessully instantiated the window context."); 

    Input input;
    input.setup(); 
    
    //Shader loading 
    Shader defaultShader ("assets/shaders/default.vs", "assets/shaders/default.fs"); 
    Shader strangeShader("assets/shaders/strangeFigure.vs", "assets/shaders/strangeFigure.fs"); 
    //Loading camera class

    Camera camera(2560, 1440, &strangeShader); 
    
    Renderer renderer(&window);

    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, glm::vec3(1.0f, 0.0f, -5.0f)); 

    glm::mat4 model2 = glm::mat4(1); 
    model2 = glm::translate(model2, glm::vec3(10.0f, 0.0f, -5.0f)); 
    
    float time = 0.0; 

    Model cube("assets/models/cube/cube.obj");

    Model strangeFigure("assets/models/strangeFigure/strangeFigure.obj");

    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, "assets/fonts/Roboto/Roboto-Black.ttf", 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;  
        return -1;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;  
        return -1;
    }
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