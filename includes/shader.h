#ifndef SHADER_H
#define SHADER_H

#include <string_view>
#include <cstdint>

class Shader {
public:
    Shader(std::string_view vertfilePath, std::string_view fragfilePath);
    Shader(std::string_view vertfilePath, std::string_view fragfilePath, std::string_view geofilePath);
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    ~Shader();
public:
    void bind() const;
    void unbind() const;
private:
    void compileProgram(std::string_view vertfilePath, std::string_view fragfilePath, std::string_view geofilePath = "");
    std::string parseFile(std::string_view filepath);
private:

    std::uint32_t m_shader; 
};

#endif