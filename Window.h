#pragma once
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>
using EventCallbackFn = std::function<void(GLFWwindow*, int, int, int, int)>;

class Window {
public:
    Window(unsigned int width, unsigned int height, const std::string& name)
        : m_width(width), m_height(height), m_window(nullptr) {
        // Создание окна
        glfwInit();
        m_window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        if (!m_window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }

        // Связывание структуры WindowEvent с окном GLFW.
        glfwSetWindowUserPointer(m_window, &m_windowEvent);
        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
            WindowEvent& eventCallback = *(WindowEvent*)glfwGetWindowUserPointer(window);
            // Код обработки события закрытия окна
            });
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
            WindowEvent& eventCallback = *(WindowEvent*)glfwGetWindowUserPointer(window);
            // Код обработки события изменения размера окна
            });
        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowEvent& eventCallback = *(WindowEvent*)glfwGetWindowUserPointer(window);
            // Код обработки события движения курсора
            });
        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowEvent& eventCallback = *(WindowEvent*)glfwGetWindowUserPointer(window);
            // Код обработки события прокрутки колесика мыши
            });
        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowEvent& eventCallback = *(WindowEvent*)glfwGetWindowUserPointer(window);
            // Код обработки события нажатия/отпускания кнопки мыши
            });
        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowEvent& eventCallback = *(WindowEvent*)glfwGetWindowUserPointer(window);
            // Код обработки события нажатия/отпускания клавиши
            });
    }

    ~Window() {
        glfwTerminate();
    }

    unsigned int width() const {
        return m_width;
    }

    unsigned int height() const {
        return m_height;
    }

    void update() {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    void setEventCallback(const EventCallbackFn& eventCallbackFn) {
        m_windowEvent.eventCallbackFn = eventCallbackFn;
    }

private:
    unsigned int m_width;
    unsigned int m_height;

    struct WindowEvent {
        EventCallbackFn eventCallbackFn;
    } m_windowEvent;

    GLFWwindow* m_window;
};

