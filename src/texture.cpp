#include <glad/gl.h>
#include <stb_image.h>
#include <string>
#include <stdexcept>

#include "texture.h"

Texture::Texture(std::string_view filepath) {
    glGenTextures(1, &m_texture);
    image = stbi_load(std::string{filepath}.c_str(), &width, &height, &channels, 0);
    if(!image) {
        throw std::runtime_error("Error:failed to load image from file");
    }

    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    unbind();
}

Texture::~Texture() {
    stbi_image_free(image);
    if(m_texture != 0) {
        unbind();
        glDeleteTextures(1, &m_texture);
    }
}

void Texture::bind() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::unbind() const {
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}