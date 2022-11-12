//
//  Triangle.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 03/11/2022.
//

#include "Triangle.hpp"



int Triangle::GetTotalVertices() { 
    return 3;
}

GLenum Triangle::GetPrimitiveType() { 
    return GL_TRIANGLES;
}


void Triangle::FillColorBuffer(GLfloat *pCBuffer) {
    
    glm::vec3* vertices = (glm::vec3*)(pCBuffer);

    vertices[0] = { 1.0f, 0.0f, 0.0f};
    vertices[1] = { 1.0f, 1.0f, 0.0f};
    vertices[2] = { 0.0f,  1.0f, 0.0f};
}

int Triangle::GetTotalIndices() { 
    return 3;
}

void Triangle::FillVertexBuffer(GLfloat *pBuffer) {
    
    glm::vec3* vertices = (glm::vec3*)(pBuffer);
    
    float scale = 100.0f;
    vertices[0] = { -0.5f, -0.5f, 0.0f};
    vertices[1] = { 0.5f, -0.5f, 0.0f};
    vertices[2] = { 0.0f,  0.5f, 0.0f};
    
}

void Triangle::FillIndexBuffer(GLuint *pBuffer) {
    GLuint* id = pBuffer;
    
    *id++ = 0;
    *id++ = 1;
    *id++ = 2;
}

void Triangle::SetCustomUniforms() {
}

Triangle::Triangle() {
    shader.LoadFromFile(GL_VERTEX_SHADER, "/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/Shaders/ObjectShaders/Triangle/Triangle.vert");
    shader.LoadFromFile(GL_FRAGMENT_SHADER, "/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/Shaders/ObjectShaders/Triangle/Triangle.frag");
    std::cout << "Load Sucessful";
    shader.CreateAndLinkProgram();
    std::cout << "Link sucessful";
    shader.Use();
    shader.AddAttribute("vVertex");
    shader.AddAttribute("vColor");
    shader.UnUse();
}







