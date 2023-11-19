#pragma once
#include <cstdint>
#include <glad/glad.h>

class Buffer
{
public:
    virtual ~Buffer() = default;

    virtual void create() = 0;
    virtual void destroy() = 0;

    virtual void bind() = 0;
    virtual void release() = 0;

    virtual void allocate(void* data, uint32_t size) = 0;
};

class VertexBuffer
{
public:
    VertexBuffer() : m_id(0) {}

    void create()
    {
        glGenBuffers(1, &m_id);
    }

    void allocate(const void* data, size_t size)
    {
        GLint currentBuffer;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, currentBuffer);
    }


    void bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void release()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void destroy()
    {
        glDeleteBuffers(1, &m_id);
    }

private:
    unsigned int m_id;
};

class IndexBuffer
{
public:
    IndexBuffer() : m_id(0) {}

    void create()
    {
        glGenBuffers(1, &m_id);
    }

    void allocate(const void* data, size_t size)
    {
        GLint currentBuffer;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, currentBuffer);
    }


    void bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    void release()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void destroy()
    {
        glDeleteBuffers(1, &m_id);
    }

private:
    unsigned int m_id;
};
