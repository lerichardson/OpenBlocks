#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "models/fullblock.h"
#include "shaders/terrain.h"
#include "shaderInit.h"

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

unsigned int shaderInit()
{
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

    return program;
}

void shaderCleanup(unsigned int program)
{
    glDeleteProgram(program);
}

