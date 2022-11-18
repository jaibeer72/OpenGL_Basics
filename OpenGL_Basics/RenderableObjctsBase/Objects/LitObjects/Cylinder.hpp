//
//  Cylinder.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 17/11/2022.
//

#ifndef Cylinder_hpp
#define Cylinder_hpp

#include "ILight.hpp"

class Cylinder : public ILitObject {

public:
    Cylinder();
    
    void FillVertexNormals(std::vector<Vertex> &VertexNormals) override;
    
    int GetToalVertices() override;
    
    GLenum GetPrimitiveType() override;
    
    void SetCustomUniforms() override;
    
    void DrawStyle() override;
    
    
    GLfloat radius, length;
    GLuint definition;
    GLuint numberOfvertices;
    
};

#endif /* Cylinder_hpp */
