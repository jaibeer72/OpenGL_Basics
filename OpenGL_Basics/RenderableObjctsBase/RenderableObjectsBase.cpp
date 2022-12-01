//
//  RenderableObjectsBase.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 01/11/2022.
//

#include "RenderableObjectsBase.hpp"


IRenderableObject::IRenderableObject() {
}

IRenderableObject::~IRenderableObject() { 
    Destroy();
}

void IRenderableObject::IRenderableObject::Render(const float *VP) {
    shader.Use();
    glUniformMatrix4fv(shader("VP"), 1, GL_FALSE, VP);
    glUniformMatrix4fv(shader("vModel"),1,GL_FALSE,glm::value_ptr(model));
    SetCustomUniforms();
    glBindVertexArray(vaoID);
    glDrawElements(primType, totalIndices, GL_UNSIGNED_INT, 0);
    shader.UnUse();
}

void IRenderableObject::IRenderableObject::Init() {
        
        //setup vao and vbo stuff
        glGenVertexArrays(1, &vaoID);
        glGenBuffers(1, &vboVerticesID);
        glGenBuffers(1, &vboIndicesID);

        //get total vertices and indices
        totalVertices = GetTotalVertices();
        totalIndices = GetTotalIndices();
        primType = GetPrimitiveType();

        //now allocate buffers
        glBindVertexArray(vaoID);

        glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
        glBufferData(GL_ARRAY_BUFFER, totalVertices * sizeof(glm::vec3), 0, GL_STATIC_DRAW);

        GLfloat* pBuffer = static_cast<GLfloat*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        FillVertexBuffer(pBuffer);
    
        glUnmapBuffer(GL_ARRAY_BUFFER);

        glEnableVertexAttribArray(shader["vVertex"]);
        glVertexAttribPointer(shader["vVertex"], 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalIndices * sizeof(GLuint), 0, GL_STATIC_DRAW);

        GLuint* pIBuffer = static_cast<GLuint*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
        FillIndexBuffer(pIBuffer);
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D,0);
}

void IRenderableObject::IRenderableObject::Destroy() {
    
}




