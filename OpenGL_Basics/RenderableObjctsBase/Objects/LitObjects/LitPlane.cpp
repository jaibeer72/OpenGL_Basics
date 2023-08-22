//
//  LitPlane.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 12/12/2022.
//

#include "LitPlane.hpp"
#include "TexLoading.hpp"


LitTexPlane::LitTexPlane(const int w, const int d) {
    width = w;
    depth = d;
    
    //setup shader
    shader.LoadFromFile(GL_VERTEX_SHADER, "/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/Shaders/LightingShaders/Lit_Plane/LitTexPlane.");
    shader.LoadFromFile(GL_FRAGMENT_SHADER, "/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/Shaders/LightingShaders/Lit_Plane/LitTexPlane.frag");
    shader.CreateAndLinkProgram();
    shader.Use();
        shader.AddAttribute("vVertex",0);
        shader.AddAttribute("vNormal", 1);
        shader.AddAttribute("vTexCoords", 2);
        shader.AddUniform("VP");
        shader.AddUniform("diffuseTexture");
        shader.AddUniform("vModel");
        shader.AddUniform("viewPos");
        glUniform1i(shader("diffuseTexture"), 0);
    shader.UnUse();
    

    //generate texture object
    checkerTextureID = TexLoading::loadTexture("/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/assets/Skybox/cubemap_night/night_posx.png");
    
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, checkerTextureID);
    
    SetPosition(glm::vec3(0,0,0)) ;
    UpdateTransform();
}

void LitTexPlane::FillVertexNormals(std::vector<VertexLit> &VertexNormals) {
    float width_2 = width/2;
    float depth_2 = depth/2;
    glm::vec3 pos[] = {
        { -width_2, 0,-depth_2},
        { width_2,0,  -depth_2},
        { width_2, 0, depth_2},
        
        {-width_2, 0,  -depth_2},
        {width_2, 0, depth_2},
        {-width_2, 0, depth_2}
    };
    glm::vec3 nor[]= {
        {0.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 0.0f}
    };
    
    glm::vec2 tex[]={
        {-1,  0.0f},
        {1,  0.0f},
        {1, 0.0f},
        {-1,  0.0f},
        {1, 0.0f},
        {-1, 0.0f}
    };
    
    VertexNormals.resize(6);
    
    for(int i = 0 ; i < 6 ; i++)
    {
        VertexLit v ;
        v.Position = pos[i];
        v.Normal = nor[i];
        v.TexCoords = tex[i];
        VertexNormals[i]=v;
    }
}

int LitTexPlane::GetToalVertices() { 
    return 6;
}

GLenum LitTexPlane::GetPrimitiveType() { 
    return GL_TRIANGLES;
}

void LitTexPlane::SetCustomUniforms() {
    glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, checkerTextureID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);
}

void LitTexPlane::DrawStyle() { 
    glDrawArrays(GL_TRIANGLES,0,totalVertices);
}





