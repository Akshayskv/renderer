#ifndef TEXTURE_H
#define TEXTURE_H

#include <string_view>
#include <cstdint>

class Texture {
public:
    Texture(std::string_view filepath);
    ~Texture();
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    void bind() const;
    void unbind() const;

private:
    int width;
    int height;
    int channels;
    unsigned char* image;
    std::uint32_t m_texture;
};

#endif