#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <glad/gl.h>

#include <vector>

#include "indexbuffer.h"
#include "vertexbuffer.h"

class VertexArray {
public:
    VertexArray() {
        glGenVertexArrays(1, &m_vertexarray);
    }

    ~VertexArray() {
        unbind();
        glDeleteVertexArrays(1, &m_vertexarray);
    }
    void bind() const {
        glBindVertexArray(m_vertexarray);
    }
    void unbind() const {
        glBindVertexArray(0);
    }
    
    template <typename T>
    void addlayout(const VertexBuffer<T>& vertexbuffer, const IndexBuffer& indexbuffer) {
        bind();
        vertexbuffer.bind();
        indexbuffer.bind();
        auto layout = VertexLayout<T>::get();
        for(int i = 0; i < layout.size(); i++) {
            glVertexAttribPointer(i, layout[i].count, layout[i].type, layout[i].normalized, sizeof(T), layout[i].offset);
        }

        unbind();
        vertexbuffer.unbind();
        indexbuffer.unbind();
    }
    
private:
    uint32_t m_vertexarray;
};

#endif