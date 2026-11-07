#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <glad/gl.h>
#include <cstdint>

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
            glVertexAttribPointer(i, layout[i].count, layout[i].type, layout[i].normalized, sizeof(T), reinterpret_cast<const void*>(static_cast<uintptr_t>(layout[i].offset)));
            glEnableVertexAttribArray(i);
        }

        unbind();
        vertexbuffer.unbind();
        indexbuffer.unbind();
    }

    template <typename T>
    void addlayout(const VertexBuffer<T>& vertexbuffer) {
        bind();
        vertexbuffer.bind();
        auto layout = VertexLayout<T>::get();
        for(int i = 0; i < layout.size(); i++) {
            glVertexAttribPointer(i, layout[i].count, layout[i].type, layout[i].normalized, sizeof(T), reinterpret_cast<const void*>(static_cast<uintptr_t>(layout[i].offset)));
            glEnableVertexAttribArray(i);
        }
        unbind();
        vertexbuffer.unbind();
    }
    
private:
    std::uint32_t m_vertexarray;
};

#endif