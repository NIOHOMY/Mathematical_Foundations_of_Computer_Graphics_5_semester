#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

//GLFWwindow  *window;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;
        /* case GLFW_KEY_SPACE:
             cur_icon_color = (cur_icon_color + 1) % 5;
             set_icon(window, cur_icon_color);
             break;
         case GLFW_KEY_X:
             glfwSetWindowIcon(window, 0, NULL);
             break;*/
    }
}

void triang()
{
    GLuint vbo = 0;
    GLuint vao = 0;
    float points[] = {
       0.0f,  0.5f,  0.0f,
       0.5f, -0.5f,  0.0f,
      -0.5f, -0.5f,  0.0f
    };
    const char* vertex_shader =
        "#version 400\n"
        "in vec3 vp;"
        "void main() {"
        "  gl_Position = vec4(vp, 1.0);"
        "}";
    const char* fragment_shader =
        "#version 400\n"
        "out vec4 frag_colour;"
        "void main() {"
        "  frag_colour = vec4(0.2, 0.0, 0.5, 1.0);"
        "}";
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint shader_programme = glCreateProgram();
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);


    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);

    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);

    glUseProgram(shader_programme);
    glBindVertexArray(vao);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // update other events like input handling 
}

// Когда пользователь меняет размер окна, окно просмотра также должно быть скорректировано, требуя функцию обратного вызова
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // Первые два параметра функции glViewport управляют положением нижнего левого угла окна, а третий и четвертый параметры контролируют ширину и высоту окна рендеринга
    glfwSetKeyCallback(window, key_callback);
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}
// Объявляем функцию, чтобы определить, нажата ли конкретная клавиша
void processInput(GLFWwindow* window) {
    // Проверка, нажимает ли пользователь клавишу возврата (Esc) (если не нажата, glfwGetKey вернет GLFW_RELEASE, если нажата, GLFW_PRESS)
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, char** argv)
{ // Инициализация GLFW
    glfwInit();

    // Установить номер основной версии OpenGL (Major) и номер вспомогательной версии (Minor) в 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Использование режима ядра (Core-profile)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Если это система MacOS, вам понадобится следующая строка кода для работы конфигурации
//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

     // Создать объект окна
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW + GLAD", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    // Уведомить GLFW, чтобы установить контекст нашего окна в качестве основного контекста текущего потока
    glfwMakeContextCurrent(window);

    // GLAD используется для управления указателем функции OpenGL, нам нужно инициализировать GLAD перед вызовом любой функции OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // Зарегистрируем определенную функцию обратного вызова и сообщаем GLFW вызывать эту функцию при каждом изменении размера окна
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



    // Визуализация цикла
    while (!glfwWindowShouldClose(window)) {

        // Проверить, нажата ли конкретная клавиша, и обрабатывать ее каждый кадр
        processInput(window);

        // функция glClearColor - это функция установки состояния, используемая для установки цвета, используемого для очистки экрана
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // Функция glClear - это функция использования состояния, которая использует текущее состояние для очистки экрана с указанным цветом
        glClear(GL_COLOR_BUFFER_BIT);
        //triang(); - запускаем отрисовку треугольника. Работает именно в этом месте!
        triang();
        // Функция glfwSwapBuffers будет обмениваться цветовыми буферами
        glfwSwapBuffers(window);
        // Функция glfwPollEvents проверяет, запущены ли какие-либо события
        glfwPollEvents();
    }


    // Освободить все ресурсы, выделенные ранее
    glfwTerminate();

    return 0;
}