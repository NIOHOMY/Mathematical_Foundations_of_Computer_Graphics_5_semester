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
#include "BoundingBox.h"

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
        glm::vec3 minPoint(std::numeric_limits<float>::max());
        glm::vec3 maxPoint(std::numeric_limits<float>::lowest());

        for (const Vertex& vertex : Model) {
            if (vertex.vertex[0] < minPoint.x) minPoint.x = vertex.vertex[0];
            if (vertex.vertex[1] < minPoint.y) minPoint.y = vertex.vertex[1];
            if (vertex.vertex[2] < minPoint.z) minPoint.z = vertex.vertex[2];

            if (vertex.vertex[0] > maxPoint.x) maxPoint.x = vertex.vertex[0];
            if (vertex.vertex[1] > maxPoint.y) maxPoint.y = vertex.vertex[1];
            if (vertex.vertex[2] > maxPoint.z) maxPoint.z = vertex.vertex[2];
        }
        box = { minPoint, maxPoint };
        nVertices_ = indices.size()/3;

        // eebo create
        // bind
        // allocate
        // release
        
        // vb.create
        // bind
        // allocate
        // release


        ebo.create();
        ebo.bind();
        ebo.allocate(indices.data(), indices.size() * sizeof(unsigned int));
        ebo.release();


        vb.create();   
        vb.bind();
        vb.allocate(Model.data(), Model.size() * sizeof(float)*8);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, vertex));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(2);
        vb.release();
        
    }
    virtual int nVertices() {
        return nVertices_;
    }
    virtual void bind(Shader& shader) override {
        shader.bind();
        vb.bind();
        ebo.bind();

        glm::mat4 modelMatrix = transformationMatrix();
        shader.setMat4("matrix4", modelMatrix);
    }

    virtual void release(Shader& shader) override {
        ebo.release();
        vb.release();
        shader.release();
    }

    void destroy()
    {
        vb.release();
        ebo.release();
        vb.destroy();
        ebo.destroy();
    }
    BoundingBox getBoundingBox() const {
        return box;
    }
private:
    int nVertices_;
    VertexBuffer vb;
    IndexBuffer ebo;
    BoundingBox box;
};

