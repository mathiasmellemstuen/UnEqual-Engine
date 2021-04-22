#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h" 

class Camera {
    private:
        glm::vec3 rotation;
        glm::vec3 position;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        glm::vec3 cameraRight;
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
        void setRotation(glm::vec3 r);
        void setPosition(glm::vec3 pos);
        void move(glm::vec3 direction, glm::vec3 rotation, float speed);
        glm::mat4 getModel(); 
        glm::mat4 getView();
        glm::mat4 getProjection(); 
        glm::vec3 getPosition(); 
        glm::vec3 getRotation(); 
        

}; 
#endif