#version 330 core
layout (location = 0) in vec3 vVertex;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

uniform mat4 lightSpaceMatrix;
uniform mat4 vModel;
uniform mat4 VP; //combined modelview projection
out vec2 TexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

void main()
{
    vs_out.FragPos = vec3(vModel * vec4(vVertex, 1.0));
    vs_out.Normal = vNormal;
    vs_out.TexCoords = vTexCoords;
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
    gl_Position = VP*vModel*vec4(vVertex.xyz,1);
}
