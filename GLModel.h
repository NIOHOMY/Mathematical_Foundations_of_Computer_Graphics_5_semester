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


class GLModel : public DrawableObject {
public:
    GLModel(std::vector<float> vertices,
    std::vector<float> textureCoords,
    std::vector<float> normals,
    std::vector<unsigned int> indices)
    {

        nVertices_ = indices.size()/3;
        Model.resize(indices.size() / 3);
        int i = 0;
        while (i < indices.size())
        {
            Vertex new_v;
            _indices.push_back(indices[i]);
            new_v.vertex[0] = vertices[indices[i] * 3];
            new_v.vertex[1] = vertices[indices[i] * 3 + 1];
            new_v.vertex[2] = vertices[indices[i] * 3 + 2];
            new_v.texture[0] = textureCoords[indices[i + 1] * 2];
            new_v.texture[1] = textureCoords[indices[i + 1] * 2 + 1];
            new_v.normal[0] = normals[indices[i + 2] * 3];
            new_v.normal[1] = normals[indices[i + 2] * 3 + 1];
            new_v.normal[2] = normals[indices[i + 2] * 3 + 2];
            Model[indices[i]] = (new_v);
            i += 3;
        }


        vb.create();
        ebo.create();
        
        vb.bind();
        vb.allocate(Model.data(), Model.size() * sizeof(float)*8);

        ebo.bind();
        ebo.allocate(_indices.data(), _indices.size() * sizeof(unsigned int));


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, vertex));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(2);
        

        vb.release();
        ebo.release();

    }
    virtual int nVertices() {
        return nVertices_;
    }
    virtual void bind() override {
        vb.bind();
    }

    virtual void release() override {
        vb.release();
    }

    void destroy()
    {
        vb.release();
        ebo.release();
        vb.destroy();
        ebo.destroy();
    }
private:
    int nVertices_;
    VertexBuffer vb;
    IndexBuffer ebo;

    std::vector<unsigned int> _indices;
    std::vector<Vertex> Model;
};

