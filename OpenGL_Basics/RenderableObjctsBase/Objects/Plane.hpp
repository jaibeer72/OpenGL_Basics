//
//  Plane.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 10/11/2022.
//

#pragma once
#ifndef Plane_hpp
#define Plane_hpp

#include "RenderableObjectsBase.hpp"

class CTexturedPlane : public IRenderableObject
{
public:
    CTexturedPlane(const int width=1000, const int depth=1000);
    int GetTotalVertices() override;
    int GetTotalIndices() override;
    GLenum GetPrimitiveType() override;

    void FillVertexBuffer( GLfloat* pBuffer) override;
    void FillIndexBuffer( GLuint* pBuffer) override;
    
    void FillColorBuffer(GLfloat *pBuffer) override ;
    
    void SetCustomUniforms() override;
    
    void FillNormalBuffer(GLfloat *pBuffer) override {
        
    }
    
    int GetTotalNormal() override {
        return 0;
    }
    
    
    
    
    //floor checker texture ID
    GLuint checkerTextureID;
    GLubyte data[128][128]={0};
     
private:
    int width, depth;
};

#endif /* Plane_hpp */
