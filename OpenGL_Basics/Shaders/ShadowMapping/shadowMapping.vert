#version 330 core
layout (location = 0) in vec3 vVertex;

uniform mat4 lightSpaceMatrix;
uniform mat4 VP;
uniform mat4 vModel;

void main()
{
    gl_Position = VP*lightSpaceMatrix * vModel * vec4(vVertex, 1.0);
}
