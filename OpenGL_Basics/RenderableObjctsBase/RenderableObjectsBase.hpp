//
//  RenderableObjectsBase.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 01/11/2022.
//

#pragma once
#ifndef RenderableObjectsBase_hpp
#define RenderableObjectsBase_hpp
#endif /* RenderableObjectsBase_hpp */


#include "Application.hpp" // getting things from here itself.


class IRenderableObject
{
public:
    IRenderableObject(void);
    virtual ~IRenderableObject(void);
    void Render(const float* MVP);

    virtual int GetTotalVertices() = 0;
    virtual int GetTotalIndices() = 0;
    virtual GLenum GetPrimitiveType() = 0;

    virtual void FillVertexBuffer(GLfloat* pBuffer) = 0;
    virtual void FillColorBuffer(GLfloat* pBuffer) = 0;
    virtual void FillIndexBuffer(GLuint* pBuffer) = 0;

    virtual void SetCustomUniforms() {}

    void Init();
    void Destroy();

protected:
    GLuint vaoID;
    GLuint vboVerticesID;
    GLuint vboIndicesID;
    

    GLenum primType;
    int totalVertices, totalIndices;
};
