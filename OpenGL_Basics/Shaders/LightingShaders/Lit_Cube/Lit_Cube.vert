#version 330 core
layout (location = 0) in vec3 vVector;
layout (location = 1) in vec3 vNormal;

uniform mat4 VP;
uniform mat4 vModel;

out vec3 FragPos;
out vec3 Normal;

void main()
{
    FragPos = vec3(vModel * vec4(vVector.xyz, 1.0));
    Normal = mat3(transpose(inverse(vModel))) * vNormal;
    
    gl_Position = VP*vec4(FragPos, 1.0);
}
