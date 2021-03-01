#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "shaders/terrain.h"

int* nptr = NULL;

unsigned int CompileShader(unsigned int type, const char source[])
{
    unsigned int id = glCreateShader(type);
    const char* src = source;
    glShaderSource(id, 1, &src, nptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    return id;
}

int main(void)
{
    printf(VertexShader);

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "OpenBlocks", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();

    float position[] = {

        -0.5f, -0.5f, // 0
         0.5f, -0.5f, // 1
         0.5f,  0.5f, // 2
        -0.5f,  0.5f  // 3

    };

    unsigned int indices[] = {

        0, 1, 2,
        2, 3, 0

    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), position, GL_STATIC_DRAW);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int program = glCreateProgram();

    glAttachShader(program, CompileShader(GL_VERTEX_SHADER, VertexShader));
    glAttachShader(program, CompileShader(GL_FRAGMENT_SHADER, FragmentShader));
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(CompileShader(GL_VERTEX_SHADER, VertexShader));
    glDeleteShader(CompileShader(GL_FRAGMENT_SHADER, FragmentShader));

    glUseProgram(program);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(0.4f, 0.7f, 1.0f, 1);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(program);

    glDeleteShader(CompileShader(GL_VERTEX_SHADER, VertexShader));
    glDeleteShader(CompileShader(GL_FRAGMENT_SHADER, FragmentShader));

    glfwTerminate();
    return 0;
}