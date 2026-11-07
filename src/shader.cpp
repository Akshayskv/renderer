#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

Shader::Shader(std::string_view vertfilePath, std::string_view fragfilePath) {
    m_shader = glCreateProgram();
    compileProgram(vertfilePath, fragfilePath);
}

Shader::Shader(std::string_view vertfilePath, std::string_view fragfilePath, std::string_view geofilePath) {
    m_shader = glCreateProgram();
    compileProgram(vertfilePath, fragfilePath, geofilePath);
}

Shader::~Shader() {
    if(m_shader != 0) {
        glDeleteProgram(m_shader);
    }
}

void Shader::bind() const {
    glUseProgram(m_shader);
}

void Shader::unbind() const {
    glUseProgram(0);
}

int Shader::getUniformLocation(std::string_view name) {
    return glGetUniformLocation(m_shader, std::string(name).c_str());
}

void Shader::setUniformMatrix4f(int location, glm::mat4 value) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::compileProgram(std::string_view vertfilePath, std::string_view fragfilePath, std::string_view geofilePath) {
    
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string vs = parseFile(vertfilePath);
    std::string fs = parseFile(fragfilePath);
    const char* vertSource = vs.c_str();
    const char* fragSource = fs.c_str();
    int success;
    char infoLog[512];

    glShaderSource(vertexShader, 1, &vertSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILURE\n" << infoLog << std::endl;
        return;
    }

    glAttachShader(m_shader, vertexShader);
    glDeleteShader(vertexShader);

    glShaderSource(fragmentShader, 1, &fragSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILURE\n" << infoLog << std::endl;
        return;
    }
    glAttachShader(m_shader, fragmentShader);
    glDeleteShader(fragmentShader);

    uint32_t geometryShader = 0;
    if(geofilePath != "") {
        geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        std::string gs = parseFile(geofilePath).c_str();
        const char* geoSource = gs.c_str();
        glShaderSource(geometryShader, 1, &geoSource, nullptr);
        glCompileShader(geometryShader);
        glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(geometryShader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILURE\n" << infoLog << std::endl;
            return;
        }
        glAttachShader(m_shader, geometryShader);
        glDeleteShader(geometryShader);
    }

    glLinkProgram(m_shader);
    glGetProgramiv(m_shader, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(m_shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILURE\n" << infoLog << std::endl;
        return;
    }

    glDetachShader(m_shader, vertexShader);
    glDetachShader(m_shader, fragmentShader);
    if(geometryShader != 0) {
        glDetachShader(m_shader, geometryShader);
    }
}

std::string Shader::parseFile(std::string_view filepath) {
    std::ifstream file{std::string(filepath)};
    if(!file.is_open()) {
        throw std::runtime_error(std::string{filepath} + " file not found");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    
    return buffer.str();
}