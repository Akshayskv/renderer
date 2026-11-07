#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <glad/gl.h>

#include <vector>

class IndexBuffer {
public:
    IndexBuffer(const std::vector<unsigned int>& data);
    ~IndexBuffer();
    inline int getCount() const { return m_count; }
    void bind() const;
    void unbind() const;
private:
    int m_count;
    uint32_t m_buffer;
};

#endif