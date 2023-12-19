﻿#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Buffer.h"
#include "Shader.h"
#include "Vertex.h"
#include "ModelLoader.h"
#include "GLModel.h"
Shader sh;
bool isRightMouseButtonPressed = false;
bool isLeftMouseButtonPressed = false;

float scaleRatio = 1.2f;
bool scaleRatioFlag = false;
GLModel* _model;

float rotationAngle = 10.0f;
float translationSpeed = 0.01f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void windowSizeCallback(GLFWwindow* window, int width, int height)
{
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    unsigned int projectionLoc = glGetUniformLocation(sh.get(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (yoffset > 0 && !scaleRatioFlag) {
        _model->setScale(glm::vec3(scaleRatio)* _model->scale());
    }
    else {
        _model->setScale(_model->scale()/glm::vec3(scaleRatio));
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_RIGHT:
        if (action == GLFW_PRESS) {
            isRightMouseButtonPressed = true;
        }
        if (action == GLFW_RELEASE) {
            isRightMouseButtonPressed = false;
        }
        break;
    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS) {
            isLeftMouseButtonPressed = true;
        }
        if (action == GLFW_RELEASE) {
            isLeftMouseButtonPressed = false;
        }
        break;
    default:
        break;
    }
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL 3DDD", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetScrollCallback(window, scrollCallback);

   
    sh.createByShaders("shader.vert.txt", "shader.frag.txt");
    

    if (ModelLoader::isLoad("obj2.txt"))
    {
        ModelLoader mL;
        mL.loadModel("obj2.txt");
        _model = new GLModel(mL.getModel(), mL.getIndices());


        glEnable(GL_DEPTH_TEST);

        glm::vec2 lastCursorPosition;
        
        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        while (!glfwWindowShouldClose(window))
        {

            double x, y;
            glfwGetCursorPos(window, &x, &y);
            glm::vec2 currentCursorPosition(x, y);
             
            if (isRightMouseButtonPressed) {
                glm::vec2 cursorPositionDelta = currentCursorPosition - lastCursorPosition;
                glm::vec3 translationOffset(-cursorPositionDelta.x * translationSpeed, -cursorPositionDelta.y * translationSpeed, 0.0f);
                _model->setPosition(_model->position() + translationOffset);
            }
            lastCursorPosition = currentCursorPosition;
            if (isLeftMouseButtonPressed) {
                _model->setRotation(_model->rotation() + rotationAngle* translationSpeed);
            }

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            BoundingBox bbox = _model->getBoundingBox();
            glm::vec3 objectPosition = (_model->position() + bbox.minPoint + bbox.maxPoint) * _model->scale() / 2.0f;
            glm::vec3 objectSize = (bbox.maxPoint - bbox.minPoint) * _model->scale();

            float distance = glm::length(glm::vec3(0.0f, 0.0f, -10.0f) - objectPosition);
            scaleRatioFlag = (distance - glm::length(objectSize) <= 0);

            
            _model->bind(sh);

            unsigned int viewLoc = glGetUniformLocation(sh.get(), "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            unsigned int projectionLoc = glGetUniformLocation(sh.get(), "projection");
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
            
            glDrawElements(GL_TRIANGLES, mL.getIndices().size(), GL_UNSIGNED_INT, 0);
            _model->release(sh);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        _model->destroy();
    }

    glfwTerminate();
    return 0;
}
