//
//  Lit_UnitCube.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 16/11/2022.
//


#include "Lit_UnitCube.hpp"
#include "TexLoading.hpp"

glm::vec3 lPos = glm::vec3(5, 5, 5);
glm::vec3 lambient = glm::vec3(1.0,1.0,0.0);
glm::vec3 ldiffuse = glm::vec3(1.7,0.7,0.7);
glm::vec3 lspecular = glm::vec3(1,0.5,0.25);

Lit_UnitCube::Lit_UnitCube(glm::vec3 position , glm::vec3 S, glm::vec3 R) {
    
    SetPosition(position);
    SetScale(S.x,S.y,S.z);
    SetRotation(R.x, R.y, R.z);
    UpdateTransform(); 
    
    mat.ambient = glm::vec3(1,0.35,1);
    mat.diffuse = glm::vec3(1,0.5,1);
    mat.specular = glm::vec3(1,1,1);
    mat.shininess = 35.0f;
    
    shader.LoadFromFile(GL_VERTEX_SHADER, "/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/Shaders/LightingShaders/Lit_Plane/LitTexPlane.vert");
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
    
    //generate texture object
    texID = TexLoading::loadTexture("/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/assets/Skybox/cubemap_night/night_posx.png");
    
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texID);
    // Material uniform
    shader.UnUse();

    GL_CHECK_ERRORS;
}

void Lit_UnitCube::FillVertexNormals(std::vector<VertexLit> &VertexNormals) { 
    
    glm::vec3 pos[] = {
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f, -0.5f},
        
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f},
        {-0.5f, -0.5f,  0.5f},
        
        {-0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f, -0.5f},
        {-0.5f, -0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f},
        
        { 0.5f,  0.5f,  0.5f},
        { 0.5f,  0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        {-0.5f, -0.5f,  0.5f},
        {-0.5f, -0.5f, -0.5f},
        
        {-0.5f,  0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        { 0.5f,  0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f, -0.5f}
    };
    
    glm::vec3 nor[36]= {
        {0.0f,  0.0f, -1.0f},
        {0.0f,  0.0f, -1.0f},
        {0.0f,  0.0f, -1.0f},
        {0.0f,  0.0f, -1.0f},
        {0.0f,  0.0f, -1.0f},
        {0.0f,  0.0f, -1.0f},
        
        {0.0f,  0.0f,  1.0f},
        {0.0f,  0.0f,  1.0f},
        {0.0f,  0.0f,  1.0f},
        {0.0f,  0.0f,  1.0f},
        {0.0f,  0.0f,  1.0f},
        {0.0f,  0.0f,  1.0f},
        
        {-1.0f,  0.0f,  0.0f},
        {-1.0f,  0.0f,  0.0f},
        {-1.0f,  0.0f,  0.0f},
        {-1.0f,  0.0f,  0.0f},
        {-1.0f,  0.0f,  0.0f},
        {-1.0f,  0.0f,  0.0f},
        
        {1.0f,  0.0f,  0.0f},
        {1.0f,  0.0f,  0.0f},
        {1.0f,  0.0f,  0.0f},
        {1.0f,  0.0f,  0.0f},
        {1.0f,  0.0f,  0.0f},
        {1.0f,  0.0f,  0.0f},
        
        {0.0f,  1.0f,  0.0f},
        {0.0f,  1.0f,  0.0f},
        {0.0f,  1.0f,  0.0f},
        {0.0f,  1.0f,  0.0f},
        {0.0f,  1.0f,  0.0f},
        {0.0f,  1.0f,  0.0f},
        
        {0.0f, -1.0f,  0.0f},
        {0.0f, -1.0f,  0.0f},
        {0.0f, -1.0f,  0.0f},
        {0.0f, -1.0f,  0.0f},
        {0.0f, -1.0f,  0.0f},
        {0.0f, -1.0f,  0.0f}
        
    };
    
    VertexNormals.resize(36);
    
    for(int i = 0 ; i < 36 ; i++)
    {
        VertexLit v ;
        v.Position = pos[i];
        v.Normal = nor[i];
        v.TexCoords= glm::vec2(pos[i].x,pos[i].y);
        VertexNormals[i]=v;
    }
    
}

int Lit_UnitCube::GetToalVertices() { 
    return 36;
}

GLenum Lit_UnitCube::GetPrimitiveType() { 
    return GL_TRIANGLES;
}

void Lit_UnitCube::SetCustomUniforms() {
    
    glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, texID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);

    GL_CHECK_ERRORS;
    
    
}




