#ifndef SHADER_H
#define SHADER_H

#include <string_view>
#include <cstdint>
#include <glm/mat4x4.hpp>

class Shader {
public:
    Shader(std::string_view vertfilePath, std::string_view fragfilePath);
    Shader(std::string_view vertfilePath, std::string_view fragfilePath, std::string_view geofilePath);
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    ~Shader();
public:
    int getUniformLocation(std::string_view name);
    void setUniformMatrix4f(int location, glm::mat4 value);
    void bind() const;
    void unbind() const;
private:
    void compileProgram(std::string_view vertfilePath, std::string_view fragfilePath, std::string_view geofilePath = "");
    std::string parseFile(std::string_view filepath);
private:

    std::uint32_t m_shader; 
};

#endif