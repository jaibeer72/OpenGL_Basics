//
//  UnitCube.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 11/11/2022.
//

#ifndef UnitCube_hpp
#define UnitCube_hpp

#include "RenderableObjectsBase.hpp"

class UnitCube: public IRenderableObject
{
public:
    UnitCube(const glm::vec3& color=glm::vec3(1,0,0));
    
    int GetTotalVertices() override;
    
    int GetTotalIndices() override;
    
    GLenum GetPrimitiveType() override;
    
    void FillVertexBuffer(GLfloat *pBuffer) override;
    
    void FillColorBuffer(GLfloat *pBuffer) override;
    
    void FillIndexBuffer(GLuint *pBuffer) override;
    
    void SetCustomUniforms() override;
    glm::vec3 color;
    
};

#endif /* UnitCube_hpp */
