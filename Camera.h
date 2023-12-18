#pragma once
#include "Transform.h"
#include <glm/ext/matrix_float4x4.hpp>

class Camera : public Transform {
public:
    Camera(float fovY, float near, float far)
        : m_width(0), m_height(0), m_fovY(fovY), m_near(near), m_far(far) {}

    void setViewportSize(unsigned int width, unsigned int height) {
        m_width = width;
        m_height = height;
    }

    glm::mat4 projectionMatrix() const {
        return glm::perspective(glm::radians(m_fovY), static_cast<float>(m_width) / m_height, m_near, m_far);
    }

    glm::mat4 viewMatrix() const {
        // Реализация функции viewMatrix
        return glm::mat4(1.0f);
    }

private:
    unsigned int m_width;
    unsigned int m_height;
    float m_fovY;
    float m_near;
    float m_far;
};


