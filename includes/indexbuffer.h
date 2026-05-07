#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <glad/gl.h>

#include <vector>

class IndexBuffer {
public:
    IndexBuffer(const std::vector<unsigned int>& data);
    ~IndexBuffer();
    void bind() const;
    void unbind() const;
private:
    uint32_t m_buffer;
};

#endif