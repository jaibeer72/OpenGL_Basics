//
//  Plane.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 10/11/2022.
//

#include "Plane.hpp"

#include <glm/glm.hpp>

CTexturedPlane::CTexturedPlane(const int w, const int d)
{
    width = w;
    depth = d;
    
    //setup shader
    shader.LoadFromFile(GL_VERTEX_SHADER, "../../../OpenGL_Basics/Shaders/ObjectShaders/TexturedPlane/checkeredPlane.vert");
    shader.LoadFromFile(GL_FRAGMENT_SHADER, "../../../OpenGL_Basics/Shaders/ObjectShaders/TexturedPlane/checkeredPlane.frag");
    shader.CreateAndLinkProgram();
    shader.Use();
        shader.AddAttribute("vVertex",0);
        shader.AddUniform("VP");
        shader.AddUniform("textureMap");
        shader.AddUniform("vModel");
        glUniform1i(shader("textureMap"), 0);
    shader.UnUse();
    
    //generate the checker texture
    for(int j=0;j<128;j++) {
        for(int i=0;i<128;i++) {
            data[i][j]=((i<=64 && j<=64) || (i>64 && j>64) )?255:0;
        }
    }
    
    //generate texture object
    glGenTextures(1, &checkerTextureID);
    glBindTexture(GL_TEXTURE_2D, checkerTextureID);

    //set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    //set maximum aniostropy setting
    GLfloat largest_supported_anisotropy;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest_supported_anisotropy);

    //set mipmap base and max level
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);

    //allocate texture object
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED, 128, 128, 0, GL_RED, GL_UNSIGNED_BYTE, data);

    //generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, checkerTextureID);
    
    SetPosition(glm::vec3(0,0,0)) ;
    UpdateTransform();
}


int CTexturedPlane::GetTotalVertices() {
    return 4;
}

int CTexturedPlane::GetTotalIndices() {
    return 6;
}

GLenum CTexturedPlane::GetPrimitiveType() {
    return GL_TRIANGLES;
}

void CTexturedPlane::FillVertexBuffer(GLfloat* pBuffer) {
    glm::vec3* vertices = (glm::vec3*)(pBuffer);
    
    float width_2 = width/2;
    float depth_2 = depth/2;
     
    vertices[0] = glm::vec3( -width_2, 0,-depth_2);
    vertices[1] = glm::vec3( width_2,0, -depth_2);

    vertices[2] = glm::vec3( width_2,0,depth_2);
    vertices[3] = glm::vec3( -width_2,0,depth_2);
}

void CTexturedPlane::FillIndexBuffer(GLuint* pBuffer) {
    
    //fill indices array
    GLuint* id=pBuffer;
    *id++ = 0;
    *id++ = 1;
    *id++ = 2;
    *id++ = 0;
    *id++ = 2;
    *id++ = 3;
}

void CTexturedPlane::SetCustomUniforms(){
    glBindTexture(GL_TEXTURE_2D, checkerTextureID);
    
}

void CTexturedPlane::FillColorBuffer(GLfloat *pBuffer)
{
    
}
