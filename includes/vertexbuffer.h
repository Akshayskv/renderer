#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <glad/gl.h>

#include <vector>

struct VertexAttributes { 
    unsigned int count;
    unsigned int offset;
    bool normalized;
    GLenum type;
};

template <typename T>
struct VertexLayout {
    static std::vector<VertexAttributes> get() {

    }
};

struct VertexB {
   float vertex[3]; 
};

template <>
struct VertexLayout<VertexB> {
    static std::vector<VertexAttributes> get() {
        return {
            {3, 0, true, GL_FLOAT}
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
        glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(T) * data.size(), data.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
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
    uint32_t m_buffer;
};

#endif