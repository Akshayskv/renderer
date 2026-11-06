#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <glad/gl.h>
#include <vector>
#include <cstdint>

struct VertexAttributes { 
    unsigned int count;
    unsigned int offset;
    bool normalized;
    GLenum type;
};

template <typename T>
struct VertexLayout {
    static std::vector<VertexAttributes> get() {
        return {};
    }
};

struct TexturedVertex {
    float vertex[3];
    float texCoords[2];
};

template<>
struct VertexLayout<TexturedVertex> {
    static std::vector<VertexAttributes> get() {
        return {
            {3, 0, true, GL_FLOAT},
            {2, offsetof(TexturedVertex, texCoords), true, GL_FLOAT}
        };
    }
};

struct ColoredVertex {
    float vertex[3];
    float color[3];
};

template <>
struct VertexLayout<ColoredVertex> {
    static std::vector<VertexAttributes> get() {
        return {
            {3, 0, true, GL_FLOAT},
            {3, offsetof(ColoredVertex, color), true, GL_FLOAT}
        };
    }
};


template<typename T>
concept VertexType = std::is_standard_layout_v<T> && requires {
    { VertexLayout<T>::get() } -> std::same_as<std::vector<VertexAttributes>>;
};

template <VertexType T>
class VertexBuffer {
public:
    VertexBuffer(const std::vector<T>& data) {
        glGenBuffers(1, &m_buffer);
        bind();
        glBufferData(GL_ARRAY_BUFFER, sizeof(T) * data.size(), data.data(), GL_STATIC_DRAW);
        unbind();
    }

    ~VertexBuffer() {
        unbind();
        glDeleteBuffers(1, &m_buffer);
    }

    void bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    }

    void unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

private:
    std::uint32_t m_buffer;
};

#endif