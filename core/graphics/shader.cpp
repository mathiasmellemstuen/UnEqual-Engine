#include "shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../log/log.h"

void Shader::use() {
    glUseProgram(id);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value); 
}
void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value); 
}
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode; 
    std::string fragmentCode; 
    
    std::ifstream vertexShaderFile; 
    std::ifstream fragmentShaderFile; 
    
    vertexShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {

        //Open files: 
        vertexShaderFile.open(vertexPath); 
        fragmentShaderFile.open(fragmentPath); 

        std::stringstream vertexShaderStream, fragmentShaderStream; 

        vertexShaderStream << vertexShaderFile.rdbuf(); 
        fragmentShaderStream << fragmentShaderFile.rdbuf(); 

        vertexShaderFile.close(); 
        fragmentShaderFile.close(); 

        vertexCode = vertexShaderStream.str(); 
        fragmentCode = fragmentShaderStream.str();
    } catch(std::ifstream::failure e) {
        log(ERROR, "ERROR::01::SHADER::FILE_NOT_SUCCESSFULLY_READ");
    }
    const char* vertex_shader_code = vertexCode.c_str(); 
    const char* fragment_shader_code = fragmentCode.c_str(); 

    unsigned int vertex, fragment; 
    int success; 
    char info_log[512];
    
    //Setting up vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER); 
    glShaderSource(vertex, 1, &vertex_shader_code, NULL); 
    glCompileShader(vertex); 

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success); 

    if(!success) {
        glGetShaderInfoLog(vertex, 512, NULL, info_log);
        log(ERROR, "ERROR::02::SHADER::VERTEX::COMPILATION_FAILED\n" + (std::string)info_log);
    }

    //Setting up fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER); 
    glShaderSource(fragment, 1, &fragment_shader_code, NULL); 
    glCompileShader(fragment); 

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success); 

    if(!success) {
        glGetShaderInfoLog(fragment, 512, NULL, info_log);
        log(ERROR, "ERROR::03::SHADER::FRAGMENT::COMPILATION_FAILED\n" + (std::string)info_log);
    }
    
    //Creating a shader program
    id = glCreateProgram(); 
    glAttachShader(id, vertex); 
    glAttachShader(id, fragment); 
    glLinkProgram(id); 

    //Displaying linking errors
    glGetProgramiv(id, GL_LINK_STATUS, &success); 
    if(!success) {
        glGetProgramInfoLog(id, 512, NULL, info_log); 

        log(ERROR, "ERROR::04::SHADER::PRORAM::LINKING::FAILED\n" + (std::string)info_log);
    }
    //Deleting shaders now that they are linked to our program and therfore no longer needed.
    glDeleteShader(vertex); 
    glDeleteShader(fragment); 
}
