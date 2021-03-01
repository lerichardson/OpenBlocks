const char VertexShader[] =
"#version 330 core\n"\
"layout(location = 0) in vec4 position;\n"\
"void main()\n"\
"{\n"\
"	gl_Position = position;\n"\
"};";

const char FragmentShader[] =
"#version 330 core\n"\
"layout(location = 0) out vec4 color;\n"\
"void main()\n"\
"{\n"\
"	color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"\
"};";