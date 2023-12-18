#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Buffer.h"
#include "GLModel.h"
#include "Vertex.h"
#include "Shader.h"

#include "Transform.h"

class DrawableObject
{
public:
    virtual void bind(Shader& shader) = 0;
    virtual void release(Shader& shader) = 0;
    virtual int nVertices() = 0;
};


class GLModel : public DrawableObject, public Transform {
public:
    GLModel(std::vector<Vertex> Model,
    std::vector<unsigned int> indices)
    {

        nVertices_ = indices.size()/3;

        // vb.create
        // bind
        // allocate
        // release

        // eebo create
        // bind
        // allocate
        // release

        vb.create();
        ebo.create();
        
        vb.bind();
        vb.allocate(Model.data(), Model.size() * sizeof(float)*8);

        ebo.bind();
        ebo.allocate(indices.data(), indices.size() * sizeof(unsigned int));


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
    virtual void bind(Shader& shader) override {
        shader.bind();
        vb.bind();
    }

    virtual void release(Shader& shader) override {
        vb.release();
        //shader.release();
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

};

