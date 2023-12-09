#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Buffer.h"
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Buffer.h"
#include "GLModel.h"
#include "Vertex.h"

class DrawableObject
{
public:
    virtual void bind() = 0;
    virtual void release() = 0;
    virtual int nVertices() = 0;
};

//class GLModel : public DrawableObject {
//public:
//    void bind() override {
//        m_vertexBuffer.bind();
//        m_texCoordBuffer.bind();
//        m_indexBuffer.bind();
//    }
//
//    void release() override {
//        m_vertexBuffer.release();
//        m_texCoordBuffer.release();
//        m_indexBuffer.release();
//    }
//
//    int nVertices() override {
//        return m_numVertices;
//    }
//
//    void setVertices(const std::vector<glm::vec3>& vertices) {
//        
//        m_vertexBuffer.create();
//        m_vertexBuffer.bind();
//        m_vertexBuffer.allocate(vertices.data(), vertices.size() * sizeof(glm::vec3));
//        m_numVertices = vertices.size();
//    }
//
//    void setTextureCoords(const std::vector<glm::vec2>& textureCoords) {
//        
//        m_texCoordBuffer.create();
//        m_texCoordBuffer.bind();
//        m_texCoordBuffer.allocate(textureCoords.data(), textureCoords.size() * sizeof(glm::vec2));
//    }
//
//    void setNormals(const std::vector<glm::vec3>& normals) {
//        
//        m_normalBuffer.create();
//        m_normalBuffer.bind();
//        m_normalBuffer.allocate(normals.data(), normals.size() * sizeof(glm::vec3));
//    }
//    void setIndices(const std::vector<unsigned int>& indices) {
//        m_indexBuffer.create();
//        m_indexBuffer.bind();
//        m_indexBuffer.allocate(indices.data(), indices.size() * sizeof(unsigned int));
//        m_numIndices = indices.size();
//    }
//
//private:
//    VertexBuffer m_vertexBuffer;     
//    VertexBuffer m_texCoordBuffer;   
//    VertexBuffer m_normalBuffer;     
//    IndexBuffer m_indexBuffer;
//
//    int m_numVertices;               
//    int m_numIndices;
//};

//class GLModel {
//public:
//    void loadModel(const std::string& path) {
//        ModelLoader loader;
//        if (!loader.isLoad(path)) {
//            std::cout << "Failed to load model: " << path << std::endl;
//            return;
//        }
//
//        // Получить массивы вершин, текстурных координат и нормалей из загрузчика моделей
//        std::vector<glm::vec3> vertices = loader.getVertices();
//        std::vector<glm::vec2> textureCoords = loader.getTextureCoords();
//        std::vector<glm::vec3> normals = loader.getNormals();
//
//        // Инициализировать буферы вершин, текстурных координат и нормалей
//        glGenVertexArrays(1, &vao);
//        glBindVertexArray(vao);
//
//        glGenBuffers(1, &vbo);
//        glBindBuffer(GL_ARRAY_BUFFER, vbo);
//        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//        glEnableVertexAttribArray(0);
//
//        glGenBuffers(1, &tbo);
//        glBindBuffer(GL_ARRAY_BUFFER, tbo);
//        glBufferData(GL_ARRAY_BUFFER, textureCoords.size() * sizeof(glm::vec2), textureCoords.data(), GL_STATIC_DRAW);
//        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
//        glEnableVertexAttribArray(1);
//
//        glGenBuffers(1, &nbo);
//        glBindBuffer(GL_ARRAY_BUFFER, nbo);
//        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
//        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//        glEnableVertexAttribArray(2);
//
//        glBindVertexArray(0);
//        countTriangles = vertices.size() * sizeof(glm::vec3);
//    }
//
//    void draw() {
//        glBindVertexArray(vao);
//        glDrawElements(GL_TRIANGLES, countTriangles, GL_UNSIGNED_INT, 0);
//        //glDrawArrays(GL_TRIANGLES, 0, countTriangles * 3);
//        glBindVertexArray(0);
//    }
//
//private:
//    GLuint vao;
//    GLuint vbo;
//    GLuint tbo;
//    GLuint nbo;
//
//    int countTriangles;
//};



class GLModel : public DrawableObject {
public:
    GLModel(std::vector<float> vertices,
    std::vector<float> textureCoords,
    std::vector<float> normals,
    std::vector<unsigned int> indices)
    {

        nVertices_ = indices.size()/3;
        
        int i = 0;
        while (i < indices.size())
        {
            Vertex new_v;
            _indices.push_back(indices[i]);
            new_v.vertex[0] = vertices[indices[i] * 3];
            new_v.vertex[1] = vertices[indices[i] * 3 + 1];
            new_v.vertex[2] = vertices[indices[i] * 3 + 2];
            new_v.texture[0] = textureCoords[indices[i + 1] * 2];
            new_v.texture[1] = textureCoords[indices[i + 1] * 2+1];
            new_v.normal[0] = normals[indices[i + 2] * 3];
            new_v.normal[1] = normals[indices[i + 2] * 3 + 1];
            new_v.normal[2] = normals[indices[i + 2] * 3 + 2];
            i += 3;
            Model.push_back(new_v);
        }


        vb.create();
        vb.bind();
        ebo.create();
        vb.allocate(Model.data(), Model.size() * sizeof(Vertex));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, vertex));
        
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
        
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));


        vb.release();
        
        ebo.bind();
        ebo.allocate(_indices.data(), _indices.size() * sizeof(unsigned int));

        ebo.release();

    }
    virtual int nVertices() {
        return nVertices_;
    }
    virtual void bind() override {
        vb.bind();
        ebo.bind();
    }

    virtual void release() override {
        vb.release();
        ebo.release();
    }

    void destroy()
    {
        vb.release();
        ebo.release();
    }
private:
    int nVertices_;
    VertexBuffer vb;
    IndexBuffer ebo;

    std::vector<unsigned int> _indices;
    std::vector<Vertex> Model;
};

