//
//  Lit_UnitCube.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 16/11/2022.
//

#ifndef Lit_UnitCube_hpp
#define Lit_UnitCube_hpp

#include "ILight.hpp"

class Lit_UnitCube : public ILitObject
{
    
public:
    Lit_UnitCube(glm::vec3 position , glm::vec3 S, glm::vec3 R);
    
    void FillVertexNormals(std::vector<VertexLit> &VertexNormals) override;
    
    int GetToalVertices() override;
    
    GLenum GetPrimitiveType() override;
    
    void SetCustomUniforms() override;
    
    void DrawStyle() override {
        glDrawArrays(primType,0,totalVertices);
    }
    
    
};

#endif /* Lit_UnitCube_hpp */
