#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Shader.h"
#include "ModelLoader.h"
#include "GLModel.h"

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Camera", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::vector<float> vertices = {
         1.0f, 1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 1.0f,
         -1.0f, 1.0f, -1.0f,
         -1.0f, -1.0f, -1.0f,
         -1.0f, 1.0f, 1.0f,
         -1.0f, -1.0f, 1.0f
    };

    std::vector<unsigned int> indices = {
        
        4,0,0, 2,1,0, 0,2,0,
        2,1,1, 7,3,1, 3,4,1,
        6,5,2, 5,6,2, 7,7,2,
        1,8,3, 7,9,3, 5,10,3,
        0,2,4, 3,4,4, 1,8,4,
        4,11,5, 1,8,5, 5,6,5,
        4,0,0, 6,12,0, 2,1,0,
        2,1,1, 6,13,1, 7,3,1,
        6,5,2, 4,11,2, 5,6,2,
        1,8,3, 3,4,3, 7,9,3,
        0,2,4, 2,1,4, 3,4,4,
        4,11,5, 0,2,5, 1,8,5
    };

    
    

    Shader sh;

    sh.createByShaders("shader.vert.txt", "shader.frag.txt");

    ModelLoader modelLoader;
    modelLoader.loadModel("obj.txt");
    GLModel c_model(modelLoader.getVertices(), modelLoader.getTextureCoords(), modelLoader.getNormals(), modelLoader.getIndices());


    int i = -5;

    glEnable(GL_DEPTH_TEST);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    while (!glfwWindowShouldClose(window))
    {
        /*if (i==5)
        {
            i = -5;
        }*/
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        sh.bind();

        
        glm::mat4 projection = glm::perspective(glm::radians(75.f), (float)width / (float)height, 0.1f, 100.0f);
        unsigned int projectionLoc = glGetUniformLocation(sh.get(), "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        
        glm::mat4 view = glm::lookAt(glm::vec3(3.0f, -3.0f/*(float)i*/, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        unsigned int viewLoc = glGetUniformLocation(sh.get(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));


        c_model.bind();
        glDrawElements(GL_TRIANGLES, c_model.nVertices(), GL_UNSIGNED_INT, 0);
        c_model.release();
        

        glfwSwapBuffers(window);
        glfwPollEvents();
        //i++;
    }

    
    
   
    sh.release();

    glfwTerminate();
    return 0;

}
