#include <glad/glad.h>
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

//const char* vertexShaderSource = R"(
//    #version 330 core
//    layout (location = 0) in vec3 aPos;
//
//    uniform mat4 model;
//    uniform mat4 view;
//    uniform mat4 projection;
//
//    void main()
//    {
//        gl_Position = projection * view * model * vec4(aPos, 1.0);
//    }
//)";
//
//const char* fragmentShaderSource = R"(
//    #version 330 core
//    out vec4 FragColor;
//
//    void main()
//    {
//        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
//    }
//)";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Cube", nullptr, nullptr);
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

    //// Compile vertex shader
    //unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    //glCompileShader(vertexShader);

    //// Compile fragment shader
    //unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    //glCompileShader(fragmentShader);

    //// Link shaders
    //unsigned int shaderProgram = glCreateProgram();
    //glAttachShader(shaderProgram, vertexShader);
    //glAttachShader(shaderProgram, fragmentShader);
    //glLinkProgram(shaderProgram);

    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShader);
    Shader sh;
    sh.createByShaders("shader.vert.txt", "shader.frag.txt");
    

    std::vector<Vertex> V;

    // Define cube vertices and indices
    std::vector<float> vertices = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        0, 3, 7,
        7, 4, 0,
        1, 2, 6,
        6, 5, 1,
        2, 3, 7,
        7, 6, 2,
        0, 1, 5,
        5, 4, 0
    };
    for (size_t i = 0; i < 8; i++)
    {
        Vertex v;
        for (int j=0; j < 3; j++)
        {
            v.vertex[j] = vertices[i];
        }
        V.push_back(v);
    }
    // Create VAO, VBO, and EBO
    /*unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);*/
    VertexBuffer vb;
    IndexBuffer ib;
    vb.create();
    ib.create();

    // Bind VAO
    /*glBindVertexArray(VAO);

    // Bind VBO and copy vertices data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);*/

    ModelLoader mL;
    mL.loadModel("obj.txt");

    vb.bind();
    vb.allocate(/*vertices.data()*/mL.getVertices().data(), mL.getVertices().size() * sizeof(float));

    // Bind EBO and copy indices data
    /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()* sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);*/
    ib.bind();
    ib.allocate(mL.getIndices().data(), mL.getIndices().size() * sizeof(unsigned int));

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO, VBO, and EBO
    /*glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
    vb.release();
    ib.release();

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use shader program
        /*glUseProgram(shaderProgram);*/
        sh.bind();

        // Set view matrix (move the camera back along the z-axis)
        glm::mat4 view = glm::lookAt(glm::vec3(1.0f, -3.0f, 3.0f),  // camera position
            glm::vec3(0.0f, 0.0f, 0.0f),  // look at origin
            glm::vec3(0.0f, 1.0f, 0.0f)); // up vector

        unsigned int viewLoc = glGetUniformLocation(/*shaderProgram*/sh.get(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        // Set model, view, and projection matrices (for simplicity, use identity matrices)
        glm::mat4 model = glm::mat4(1.0f);
        //glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(/*shaderProgram*/sh.get(), "model");
        //unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        unsigned int projectionLoc = glGetUniformLocation(/*shaderProgram*/sh.get(), "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Draw cube
        //glBindVertexArray(VAO);
        vb.bind();
        glDrawElements(GL_TRIANGLES, mL.getIndices().size(), GL_UNSIGNED_INT, 0);
        vb.release();
        //glBindVertexArray(0);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    /*glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);*/
    vb.destroy();
    ib.destroy();
    sh.release();

    glfwTerminate();
    return 0;
}
