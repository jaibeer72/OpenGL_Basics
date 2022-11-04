//
//  Triangle.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 03/11/2022.
//

#pragma once
#ifndef Triangle_hpp
#define Triangle_hpp

#include <stdio.h>
#include "RenderableObjectsBase.hpp"

class Triangle : public IRenderableObject
{
    
    int GetTotalVertices() override;
    
    int GetTotalIndices() override;
    
    GLenum GetPrimitiveType() override;
    
    void FillVertexBuffer(GLfloat *pBuffer) override;
    
    void FillColorBuffer(GLfloat *pBuffer) override;
    
    void FillIndexBuffer(GLuint *pBuffer) override;
    
    void SetCustomUniforms() override ;
    
    
};

#endif /* Triangle_hpp */
