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

class VertexBuffer : public Buffer
{
public:
    VertexBuffer();
    ~VertexBuffer() override;

    void create() override;
    void destroy() override;

    void bind() override;
    void release() override;

    void allocate(void* data, uint32_t size) override;

private:
    GLuint m_vbo;
};

VertexBuffer::VertexBuffer() : m_vbo(0) {}

VertexBuffer::~VertexBuffer()
{
    destroy();
}

void VertexBuffer::create()
{
    glGenBuffers(1, &m_vbo);
}

void VertexBuffer::destroy()
{
    if (m_vbo != 0)
    {
        glDeleteBuffers(1, &m_vbo);
        m_vbo = 0;
    }
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void VertexBuffer::release()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::allocate(void* data, uint32_t size)
{
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

class IndexBuffer : public Buffer
{
public:
    IndexBuffer();
    ~IndexBuffer() override;

    void create() override;
    void destroy() override;

    void bind() override;
    void release() override;

    void allocate(void* data, uint32_t size) override;

private:
    GLuint m_ebo;
};

IndexBuffer::IndexBuffer() : m_ebo(0) {}

IndexBuffer::~IndexBuffer()
{
    destroy();
}

void IndexBuffer::create()
{
    glGenBuffers(1, &m_ebo);
}

void IndexBuffer::destroy()
{
    if (m_ebo != 0)
    {
        glDeleteBuffers(1, &m_ebo);
        m_ebo = 0;
    }
}

void IndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
}

void IndexBuffer::release()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::allocate(void* data, uint32_t size)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}