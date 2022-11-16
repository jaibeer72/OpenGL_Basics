//
//  ILight.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 14/11/2022.
//

#include "ILight.hpp"


void ILitObject::Init() {
    
    //setup vao and vbo stuff
    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboVerticesID);
    
    totalVertices = GetToalVertices();
    primType = GetPrimitiveType();
    FillVertexNormals(objectVertexNormals);
    
    //now allocate buffers
    glBindVertexArray(vaoID);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
    glBufferData(GL_ARRAY_BUFFER, objectVertexNormals.size() *  sizeof(Vertex), &objectVertexNormals[0], GL_STATIC_DRAW);
    
    
    glVertexAttribPointer(shader["vVertex"], 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(shader["vVertex"]);
    
    glEnableVertexAttribArray(shader["vNormal"]);
    glVertexAttribPointer(shader["vNormal"], 3, GL_FLOAT, GL_FALSE,sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, Normal)));
    
}

void ILitObject::Render(const float *VP, glm::vec3 camPos) {
    shader.Use();
    glUniformMatrix4fv(shader("VP"), 1, GL_FALSE, VP);
    glUniform3fv(shader("viewPos"),1,glm::value_ptr(camPos));
    
    SetCustomUniforms();
    glUniformMatrix4fv(shader("vModel"),1,GL_FALSE,glm::value_ptr(model));
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glBindVertexArray(vaoID);
    glDrawArrays(primType,0,totalVertices);
    shader.UnUse();
}

void ILitObject::Destroy() {
}

ILitObject::ILitObject() {
    
}



