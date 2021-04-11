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

Camera::Camera(int screenWidth, int screenHeight) {


    log(INFO, "Creating a camera."); 
    
    width = screenWidth; 
    height = screenHeight; 
    
    model = glm::mat4(1.0); 
    view = glm::mat4(1.0); 
    projection = glm::mat4(1.0);  
    setProjection(glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f)); 
    setModel(glm::mat4(1.0)); 
    //    shader->set_mat4("model", model); 
    //    shader->set_mat4("projection", projection); 
    //    shader->set_mat4("view", view); 

    log(SUCCESS, "Camera setup is complete."); 
}
