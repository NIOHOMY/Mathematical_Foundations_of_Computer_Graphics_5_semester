#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "AffineTransform3D.h"

class Transform {
public:
    Transform() : m_position(glm::vec3(0.0f)), m_rotation(0.0f), m_scale(glm::vec3(1.0f)) {}

    void setPosition(const glm::vec3& position) {
        m_position = position;
    }

    void setRotation(const float& angle) {
        m_rotation = angle;
    }


    void setScale(const glm::vec3& scale) {
        m_scale = scale;
    }

    glm::vec3 position() const {
        return m_position;
    }

    float rotation() const {
        return m_rotation;
    }

    glm::vec3 scale() const {
        return m_scale;
    }

    glm::mat4 transformationMatrix() const {
        glm::mat4 translationMatrix = Translation(m_position.x, m_position.y);//glm::translate(glm::mat4(1.0f), m_position);
        glm::mat4 rotationMatrix = Rotation(m_rotation, glm::vec3(0.0f, 1.0f, 0.0f));//glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 scaleMatrix = Scaling(m_scale.x, m_scale.y, m_scale.z);//glm::scale(glm::mat4(1.0f), m_scale);

        return translationMatrix * rotationMatrix * scaleMatrix;
    }


private:
    glm::vec3 m_position;
    float m_rotation;
    glm::vec3 m_scale;
};

