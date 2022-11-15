#version 330 core
  
layout(location = 0) in vec3 vVertex;  //object space vertex position
layout(location = 1) in vec3 vNormal;

uniform mat4 VP;  //combind view projection matrix
uniform mat4 vModel;

void main()
{
    //get clipspace position
    gl_Position = VP*vModel*vec4(vVertex.xyz,1);
}

