#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "shader.h"
#include "../log/log.h" 
#include <string>

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
    position = glm::vec3(0.0, 0.0, 3.0);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); 
    rotation = glm::vec3(-90.0f, 0.0f, 0.0f);
    setProjection(glm::perspective(glm::radians(90.0f), (float)width / (float)height, 0.1f, 100.0f)); 
    setModel(model); 
    setView(view); 
    setPosition(position);  
   
    log(SUCCESS, "Camera setup is complete."); 
}

void Camera::setRotation(glm::vec3 r) {
    
    rotation = r; 
};

void Camera::setPosition(glm::vec3 pos) {
    position = pos;
};

glm::vec3 Camera::getPosition() {
    return position; 
}
glm::vec3 Camera::getRotation() {
    return rotation; 
}
void Camera::moveDirection(glm::vec3 direction, float distance) {
    glm::vec3 currentDirection = glm::normalize(rotation);
    //position += direction.z * currentDirection * distance; 
}
void Camera::update() {
    
    glm::vec3 dirV;
    dirV.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    //dirV.y = sin(glm::radians(rotation.x));
    dirV.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
    cameraFront = glm::normalize(dirV);
    cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));  
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront)); 
    //log(INFO, "X: " + std::to_string(dirV.x) + " Y: " + std::to_string(dirV.y) + " Z: " + std::to_string(dirV.z));  

    glm::mat4 v = glm::lookAt(position, position + cameraFront, cameraUp);
    //cameraUp = glm::cross(cameraUp, cameraFront);
    log(INFO, "X: " + std::to_string(cameraUp.x) + " Y: " + std::to_string(cameraUp.y) + " Z: " + std::to_string(cameraUp.z));  
    setView(v);
}