#version 330 core

layout(location=0) out vec4 vFragColor;    //fragment shader output
    
//uniform
uniform samplerCube cubeMap;    //cubemap texture sampler

//input from the vertex shader
smooth in vec3 uv;    //interpolated 3D texture coordinate

void main()
{
    vec3 texColor = texture(cubeMap, normalize(uv)).rgb;
    texColor = pow( texColor, vec3(1.0/2.2));
    vFragColor = vec4(texColor,1);
}
