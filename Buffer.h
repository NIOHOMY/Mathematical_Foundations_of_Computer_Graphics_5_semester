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
    VertexBuffer() : m_id_vbo(0), m_id_vao(0) {}

    void create()
    {
        glGenBuffers(1, &m_id_vbo);
        glGenVertexArrays(1, &m_id_vao);
    }

    void allocate(const void* data, size_t size)
    {
        /*GLint previousBuffer;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &previousBuffer);*/

        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

        //glBindBuffer(GL_ARRAY_BUFFER, previousBuffer);
    }


    void bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id_vbo);
        glBindVertexArray(m_id_vao);
    }

    void release()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void destroy()
    {
        glDeleteBuffers(1, &m_id_vbo);
        glDeleteBuffers(1, &m_id_vao);
    }
   /* void setupVertexAttributes()
    {
        bind();

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

        release();
    }*/

private:
    unsigned int m_id_vbo;
    unsigned int m_id_vao;
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
        /*GLint previousBuffer;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &previousBuffer);*/

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

        //glBindBuffer(GL_ARRAY_BUFFER, previousBuffer);
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
