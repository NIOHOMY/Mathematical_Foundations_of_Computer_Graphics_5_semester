#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Buffer.h"
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "ModelLoader.h"

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
    GLModel()
        : vao_(0)
        , vboVertices_(0)
        , vboTextureCoords_(0)
        , vboNormals_(0)
        , ebo_(0)
        , nVertices_(0)
    {
    }

    virtual void bind() override {
        glBindVertexArray(vao_);
    }

    virtual void release() override {
        glBindVertexArray(0);
    }

    virtual int nVertices() override {
        return nVertices_;
    }

    bool loadModel(const std::string& path) {
        std::ifstream file(path);
        if (!file.good()) {
            return false;
        }
        ModelLoader modelLoader;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> textureCoords;
        std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;

        std::string line;
        while (std::getline(file, line)) {
            if (line.find("v ") == 0) {
                glm::vec3 vertex;
                if (!modelLoader.parseVertices(line.substr(2), vertex)) {
                    return false;
                }
                vertices.push_back(vertex);
            }
            else if (line.find("vt ") == 0) {
                glm::vec2 textureCoordinate;
                if (!modelLoader.parseTextureCoords(line.substr(3), textureCoordinate)) {
                    return false;
                }
                textureCoords.push_back(textureCoordinate);
            }
            else if (line.find("vn ") == 0) {
                glm::vec3 normal;
                if (!modelLoader.parseNormal(line.substr(3), normal)) {
                    return false;
                }
                normals.push_back(normal);
            }
            else if (line.find("f ") == 0) {
                std::stringstream ss(line.substr(2));
                std::string s;
                while (std::getline(ss, s, ' ')) {
                    if (!s.empty()) {
                        std::stringstream ssIndex(s);
                        std::string sIndex;
                        std::vector<std::string> tokensIndex;
                        while (std::getline(ssIndex, sIndex, '/')) {
                            if (!sIndex.empty()) {
                                tokensIndex.push_back(sIndex);
                            }
                        }
                        if (tokensIndex.size() != 3) {
                            return false;
                        }
                        unsigned int indexVertex = std::stoi(tokensIndex[0]) - 1;
                        unsigned int indexTextureCoord = std::stoi(tokensIndex[1]) - 1;
                        unsigned int indexNormal = std::stoi(tokensIndex[2]) - 1;
                        indices.push_back(indexVertex);
                        indices.push_back(indexTextureCoord);
                        indices.push_back(indexNormal);
                    }
                }
            }
        }

        nVertices_ = indices.size() / 3;

        glGenVertexArrays(1, &vao_);
        glGenBuffers(1, &vboVertices_);
        glGenBuffers(1, &vboTextureCoords_);
        glGenBuffers(1, &vboNormals_);
        glGenBuffers(1, &ebo_);

        glBindVertexArray(vao_);

        glBindBuffer(GL_ARRAY_BUFFER, vboVertices_);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, vboTextureCoords_);
        glBufferData(GL_ARRAY_BUFFER, textureCoords.size() * sizeof(glm::vec2), textureCoords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, vboNormals_);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);

        return true;
    }

private:
    unsigned int vao_;
    unsigned int vboVertices_;
    unsigned int vboTextureCoords_;
    unsigned int vboNormals_;
    unsigned int ebo_;
    int nVertices_;
};
