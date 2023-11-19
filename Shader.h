﻿
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>

class Shader
{
public:
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~Shader();

    void bind() const;
    void release() const;

    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec2(const std::string& name, const glm::vec2& value);
    void setVec3(const std::string& name, const glm::vec3& value);
    void setVec4(const std::string& name, const glm::vec4& value);

private:
    unsigned int m_shaderId;

    std::string readShaderFile(const std::string& filePath);
    unsigned int compileShader(const std::string& source, GLenum shaderType);
    void linkShaders(unsigned int vertexShader, unsigned int fragmentShader);
};

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) : m_shaderId(0)
{
    try
    {
        std::string vertexShaderSource = vertexShaderPath;//readShaderFile(vertexShaderPath);
        std::string fragmentShaderSource = fragmentShaderPath;//readShaderFile(fragmentShaderPath);

        unsigned int vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
        unsigned int fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

        if (vertexShader == 0 || fragmentShader == 0) {
            // Handle shader compilation error
            std::cerr << "Shader compilation failed" << std::endl;
            // You might want to throw another exception or take appropriate action
            return;
        }

        linkShaders(vertexShader, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    catch (const std::runtime_error& e)
    {
        // Handle the exception here
        std::cerr << "Exception caught: " << e.what() << std::endl;
        // You might want to throw another exception or take appropriate action
    }
}


Shader::~Shader()
{
    glDeleteProgram(m_shaderId);
}

void Shader::bind() const
{
    glUseProgram(m_shaderId);
}

void Shader::release() const
{
    glUseProgram(0);
}

void Shader::setInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(m_shaderId, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(m_shaderId, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value)
{
    glUniform2fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec4(const std::string& name, const glm::vec4& value)
{
    glUniform4fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, glm::value_ptr(value));
}

std::string Shader::readShaderFile(const std::string& filePath)
{
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open())
    {
        throw std::runtime_error("Failed to open shader file: " + filePath);
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();  // Important: Close the file after reading
    return shaderStream.str();
}




unsigned int Shader::compileShader(const std::string& source, GLenum shaderType)
{
    const char* shaderCode = source.c_str();

    unsigned int shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &shaderCode, NULL);
    glCompileShader(shaderId);

    GLint success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);

        // Print shader source and compilation error
        std::cerr << "Shader compilation error for type " << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << ":\n"
            << "Shader source:\n"
            << source << "\n"
            << "Error message:\n"
            << infoLog << std::endl;

        glDeleteShader(shaderId);
        return 0;
    }

    return shaderId;
}

void Shader::linkShaders(unsigned int vertexShader, unsigned int fragmentShader)
{
    m_shaderId = glCreateProgram();
    glAttachShader(m_shaderId, vertexShader);
    glAttachShader(m_shaderId, fragmentShader);
    glLinkProgram(m_shaderId);

    GLint success;
    glGetProgramiv(m_shaderId, GL_LINK_STATUS, &success);

    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_shaderId, 512, NULL, infoLog);
        std::cerr << "Shader program linking error:\n" << infoLog << std::endl;
        glDeleteProgram(m_shaderId);
        m_shaderId = 0;
    }
}