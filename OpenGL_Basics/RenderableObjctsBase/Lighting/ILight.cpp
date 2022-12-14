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
    glBufferData(GL_ARRAY_BUFFER, objectVertexNormals.size() *  sizeof(VertexLit), &objectVertexNormals[0], GL_STATIC_DRAW);
    
    
    glVertexAttribPointer(shader["vVertex"], 3, GL_FLOAT, GL_FALSE, sizeof(VertexLit), 0);
    glEnableVertexAttribArray(shader["vVertex"]);
    
    glEnableVertexAttribArray(shader["vNormal"]);
    glVertexAttribPointer(shader["vNormal"], 3, GL_FLOAT, GL_FALSE,sizeof(VertexLit), (const GLvoid*)(offsetof(VertexLit, Normal)));
    
    if(objectVertexNormals[0].TexCoords.length()>0)
    {
        glEnableVertexAttribArray(shader["vTexCoords"]);
        glVertexAttribPointer(shader["vTexCoords"], 3, GL_FLOAT, GL_FALSE,sizeof(VertexLit), (const GLvoid*)(offsetof(VertexLit,TexCoords)));
    }
    GL_CHECK_ERRORS;
    
}

void ILitObject::Render(const float *VP, glm::vec3 camPos) {
    shader.Use();
    GL_CHECK_ERRORS;
    glUniformMatrix4fv(shader("VP"), 1, GL_FALSE, VP);
    GL_CHECK_ERRORS;
    glUniform3fv(shader("viewPos"),1,glm::value_ptr(camPos));
    GL_CHECK_ERRORS;
    glUniformMatrix4fv(shader("vModel"),1,GL_FALSE,glm::value_ptr(model));
    GL_CHECK_ERRORS;
    
    SetCustomUniforms();
    GL_CHECK_ERRORS;
    glBindVertexArray(vaoID);
    GL_CHECK_ERRORS;
    DrawStyle();
   
    //shader.PrintGLerror();
    shader.UnUse();
}

void ILitObject::Destroy() {
}

ILitObject::ILitObject() {
    
}



