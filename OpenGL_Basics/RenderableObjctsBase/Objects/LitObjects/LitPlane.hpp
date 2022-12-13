//
//  LitPlane.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 12/12/2022.
//

#ifndef LitPlane_hpp
#define LitPlane_hpp

#include "ILight.hpp"

class LitTexPlane : public ILitObject
{
public:
    LitTexPlane(const int width = 1000,const int depth = 1000);
    void FillVertexNormals(std::vector<VertexLit> &VertexNormals) override;
    
    int GetToalVertices() override;
    
    GLenum GetPrimitiveType() override;
    
    void SetCustomUniforms() override;
    
    void DrawStyle() override;
    
    //floor checker texture ID
    GLuint checkerTextureID;
    GLubyte data[128][128]={0};
    
private:
    int width, depth;
};

#endif /* LitPlane_hpp */
