//
//  Skybox.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 11/12/2022.
//

#ifndef Skybox_hpp
#define Skybox_hpp

#include "RenderableObjectsBase.hpp"

class Skybox: public IRenderableObject
{
public:
    Skybox(std::string skyBoxPath,const std::string & extention = ".png");
    
    int GetTotalVertices() override;
    
    int GetTotalIndices() override;
    
    GLenum GetPrimitiveType() override;
    
    int GetTotalNormal() override;
    
    void FillVertexBuffer(GLfloat *pBuffer) override;
    
    void FillColorBuffer(GLfloat *pBuffer) override;
    
    void FillIndexBuffer(GLuint *pBuffer) override;
    
    void FillNormalBuffer(GLfloat *pBuffer) override;
    
    void SetCustomUniforms() override;
    
private:
    GLuint texID;
    
};

#endif /* Skybox_hpp */
