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
    Lit_UnitCube();
    
    void FillVertexNormals(std::vector<Vertex> &VertexNormals) override;
    
    int GetToalVertices() override;
    
    GLenum GetPrimitiveType() override;
    
    void SetCustomUniforms() override;
    
};

#endif /* Lit_UnitCube_hpp */
