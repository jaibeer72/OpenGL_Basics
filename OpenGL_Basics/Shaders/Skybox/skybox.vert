#version 330 core
  
layout(location=0) in vec3 vVertex; //object space vertex position

//uniform
uniform mat4 VP; //combined modelview projection matrix
uniform mat4 vModel;

//output to fragment shader
smooth out vec3 uv;    //output 3D texture coordinate for the cubemap texture lookup
void main()
{
    //clipspace position by multiplying the MVP matrix with the vertex position
    gl_Position = VP*vModel*vec4(vVertex,1);
    
    //output the object vertex vertex position as the 3D texture coordinate
    uv = vVertex;
}
