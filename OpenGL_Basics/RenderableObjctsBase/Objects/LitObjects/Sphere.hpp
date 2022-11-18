//
//  Sphere.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 18/11/2022.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include "ILight.hpp"
class Sphere: public ILitObject
{
public:
    Sphere(float radius, unsigned int slices, unsigned int stacks);
    
    void FillVertexNormals(std::vector<Vertex> &VertexNormals) override;
    
    int GetToalVertices() override;
    
    GLenum GetPrimitiveType() override;
    
    void SetCustomUniforms() override;
    
    void DrawStyle() override;
    
};

#endif /* Sphere_hpp */
