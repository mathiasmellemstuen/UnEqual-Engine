#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "shader.h"
#include "../log/log.h" 

void Camera::setShader(Shader* newShader) {

    shader = newShader;
    
    modelLocation = glGetUniformLocation(shader->id, "model"); 
    viewLocation = glGetUniformLocation(shader->id, "view"); 
    projectionLocation = glGetUniformLocation(shader->id, "projection"); 

}

void Camera::setModel(glm::mat4 newModel) {
    model = newModel;
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model)); 
}
void Camera::setProjection(glm::mat4 newProjection) {
    projection = newProjection;
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
}
void Camera::setView(glm::mat4 newView) {
    view = newView; 
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
}
glm::mat4 Camera::getModel() {
    return model; 
}
glm::mat4 Camera::getView() {
    return view; 
}
glm::mat4 Camera::getProjection() {
    return projection; 
}

Camera::Camera(int screenWidth, int screenHeight, Shader* s) {


    log(INFO, "Creating a camera."); 

    setShader(s);  

    shader->use(); 
    width = screenWidth; 
    height = screenHeight; 
    
    model = glm::mat4(1.0); 
    view = glm::mat4(1.0); 
    projection = glm::mat4(1.0);
    position = glm::vec3(0.0, 0.0, 0.0); 
    setProjection(glm::perspective(glm::radians(90.0f), (float)width / (float)height, 0.1f, 100.0f)); 
    setModel(model); 
    setView(view); 
    setPosition(position);  
    
    rotate(glm::vec2(10.0,0.0), glm::vec2(0.0,0.0));
    log(SUCCESS, "Camera setup is complete."); 
}

void Camera::rotate(glm::vec2 direction, glm::vec2 speed) {
    glm::vec3 dirV;
    dirV.x = cos(glm::radians(direction.y)) * cos(glm::radians(direction.x));
    dirV.y = sin(glm::radians(direction.x));
    dirV.z = sin(glm::radians(direction.y)) * cos(glm::radians(direction.x));
    glm::vec3 cameraFront = glm::normalize(dirV);
    
    glm::mat4 v = glm::lookAt(position, position + cameraFront, glm::vec3(0.0f,1.0f,0.0f));
    setView(v);
};

void Camera::setPosition(glm::vec3 pos) {
    position = pos;
    setView(glm::translate(glm::mat4(1.0), pos)); 
};

glm::vec3 Camera::getPosition() {
    return position; 
}