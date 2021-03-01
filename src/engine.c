#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "models/fullblock.h"
#include "shaders/terrain.h"
#include "shaderInit.h"

int* nptr = NULL;



int main(void)
{
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

    unsigned int program = shaderInit();

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

    shaderCleanup(program);

    glfwTerminate();
    return 0;
}