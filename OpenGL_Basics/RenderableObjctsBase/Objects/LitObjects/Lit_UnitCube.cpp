//
//  Lit_UnitCube.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 16/11/2022.
//


#include "Lit_UnitCube.hpp"

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
    
    shader.LoadFromFile(GL_VERTEX_SHADER, "../../../OpenGL_Basics/Shaders/LightingShaders/Lit_Cube/Lit_Cube.vert");
    shader.LoadFromFile(GL_FRAGMENT_SHADER, "../../../OpenGL_Basics/Shaders/LightingShaders/Lit_Cube/Lit_Cube.frag");
    shader.CreateAndLinkProgram();
    shader.Use();
    shader.AddAttribute("vVertex", 0);
    shader.AddAttribute("vNormal", 1);
    shader.AddUniform("VP");
    
    shader.AddUniform("vModel");
    shader.AddUniform("viewPos");
    
    shader.AddUniform(Mat_Ambient);
    shader.AddUniform(Mat_Diffuse);
    shader.AddUniform(Mat_Specular);
    shader.AddUniform(Mat_Shininess);
    
    
    shader.AddUniform(Light_Position);
    shader.AddUniform(Light_Ambient);
    shader.AddUniform(Light_Diffuse);
    shader.AddUniform(Light_Specular);

    glUniform3fv(shader(Mat_Ambient),1,glm::value_ptr(mat.ambient));
    glUniform3fv(shader(Mat_Diffuse),1,glm::value_ptr(mat.diffuse));
    glUniform3fv(shader(Mat_Specular),1,glm::value_ptr(mat.specular));
    glUniform1f(shader(Mat_Shininess),mat.shininess);
    
    glUniform3fv(shader(Light_Position),1,glm::value_ptr(lPos));
    glUniform3fv(shader(Light_Ambient),1,glm::value_ptr(lambient));
    glUniform3fv(shader(Light_Diffuse),1,glm::value_ptr(ldiffuse));
    glUniform3fv(shader(Light_Specular),1,glm::value_ptr(lspecular));
    // Material uniform
    shader.UnUse();

    GL_CHECK_ERRORS;
}

void Lit_UnitCube::FillVertexNormals(std::vector<Vertex> &VertexNormals) { 
    
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
        
        {0.0f, -1.0f,  0.0f},
        {0.0f, -1.0f,  0.0f},
        {0.0f, -1.0f,  0.0f},
        {0.0f, -1.0f,  0.0f},
        {0.0f, -1.0f,  0.0f},
        {0.0f, -1.0f,  0.0f},
        
        {0.0f,  1.0f,  0.0f},
        {0.0f,  1.0f,  0.0f},
        {0.0f,  1.0f,  0.0f},
        {0.0f,  1.0f,  0.0f},
        {0.0f,  1.0f,  0.0f},
        {0.0f,  1.0f,  0.0f}
    };
    
    VertexNormals.resize(36);
    
    for(int i = 0 ; i < 36 ; i++)
    {
        Vertex v ;
        v.Position = pos[i];
        v.Normal = nor[i];
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
    glUniform3fv(shader(Mat_Ambient),1,glm::value_ptr(mat.ambient));
    glUniform3fv(shader(Mat_Diffuse),1,glm::value_ptr(mat.diffuse));
    glUniform3fv(shader(Mat_Specular),1,glm::value_ptr(mat.specular));
    glUniform1f(shader(Mat_Shininess),mat.shininess);

    
    glUniform3fv(shader(Light_Position),1,glm::value_ptr(lPos));
    glUniform3fv(shader(Light_Ambient),1,glm::value_ptr(lambient));
    glUniform3fv(shader(Light_Diffuse),1,glm::value_ptr(ldiffuse));
    glUniform3fv(shader(Light_Specular),1,glm::value_ptr(lspecular));

    GL_CHECK_ERRORS;
    
    
}




