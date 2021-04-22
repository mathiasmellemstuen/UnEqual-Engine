#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h" 

class Camera {
    private:
        glm::vec3 position;
        int width;
        int height;
        unsigned int modelLocation;
        unsigned int viewLocation;
        unsigned int projectionLocation; 
        glm::mat4 model; 
        glm::mat4 view; 
        glm::mat4 projection;
        Shader* shader; 

    public:
        Camera(int screenWidth, int screenHeight, Shader* shader);
        void setShader(Shader* newShader); 
        void setModel(glm::mat4 newModel); 
        void setView(glm::mat4 newView); 
        void setProjection(glm::mat4 newProjection); 
        void rotate(glm::vec2 direction, glm::vec2 speed);
        void setPosition(glm::vec3 pos); 
        glm::mat4 getModel(); 
        glm::mat4 getView();
        glm::mat4 getProjection(); 
        glm::vec3 getPosition(); 

}; 
#endif