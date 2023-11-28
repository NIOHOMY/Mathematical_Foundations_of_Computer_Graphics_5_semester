#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Buffer.h"
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class DrawableObject
{
public:
    virtual void bind() = 0;
    virtual void release() = 0;
    virtual int nVertices() = 0;
};

class GLModel : public DrawableObject {
public:
    void bind() override {
        m_vertexBuffer.bind();
        m_texCoordBuffer.bind();
        m_indexBuffer.bind();
    }

    void release() override {
        m_vertexBuffer.release();
        m_texCoordBuffer.release();
        m_indexBuffer.release();
    }

    int nVertices() override {
        return m_numVertices;
    }

    void setVertices(const std::vector<glm::vec3>& vertices) {
        
        m_vertexBuffer.create();
        m_vertexBuffer.bind();
        m_vertexBuffer.allocate(vertices.data(), vertices.size() * sizeof(glm::vec3));
        m_numVertices = vertices.size();
    }

    void setTextureCoords(const std::vector<glm::vec2>& textureCoords) {
        
        m_texCoordBuffer.create();
        m_texCoordBuffer.bind();
        m_texCoordBuffer.allocate(textureCoords.data(), textureCoords.size() * sizeof(glm::vec2));
    }

    void setNormals(const std::vector<glm::vec3>& normals) {
        
        m_normalBuffer.create();
        m_normalBuffer.bind();
        m_normalBuffer.allocate(normals.data(), normals.size() * sizeof(glm::vec3));
    }

private:
    VertexBuffer m_vertexBuffer;     
    VertexBuffer m_texCoordBuffer;   
    VertexBuffer m_normalBuffer;     
    IndexBuffer m_indexBuffer;

    int m_numVertices;               
};


