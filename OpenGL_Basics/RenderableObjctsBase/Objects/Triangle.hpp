//
//  Triangle.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 03/11/2022.
//

#pragma once
#ifndef Triangle_hpp
#define Triangle_hpp

#include "RenderableObjectsBase.hpp"

class Triangle : public IRenderableObject
{
public:
    Triangle();
    
    int GetTotalVertices() override;
    
    int GetTotalIndices() override;
    
    GLenum GetPrimitiveType() override;
    
    void FillVertexBuffer(GLfloat *pBuffer) override;
    
    void FillColorBuffer(GLfloat *pBuffer) override;
    
    void FillIndexBuffer(GLuint *pBuffer) override;
    
    void SetCustomUniforms() override ;
    
    int GetTotalNormal() override {
        return 0;
    }
    
    void FillNormalBuffer(GLfloat *pBuffer) override {
        
    }
    
    
};

#endif /* Triangle_hpp */
