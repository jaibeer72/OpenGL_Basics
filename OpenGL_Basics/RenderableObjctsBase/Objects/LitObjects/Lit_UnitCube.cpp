//
//  Lit_UnitCube.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 16/11/2022.
//


#include "Lit_UnitCube.hpp"
#include "Input.hpp"

glm::vec3 lPos = glm::vec3(5, 5, 5);
glm::vec3 lambient = glm::vec3(1.0,1.0,0.0);
glm::vec3 ldiffuse = glm::vec3(1.7,0.7,0.7);
glm::vec3 lspecular = glm::vec3(1,0.5,0.25);

Lit_UnitCube::Lit_UnitCube(glm::vec3 position , glm::vec3 S, glm::vec3 R) {
    
    SetPosition(position);
    //scale(S.x,S.y,S.z);
    Rotate(R.x, R.y, R.z);
    
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
    
    shader.AddUniform("material.ambient");
    shader.AddUniform("material.diffuse");
    shader.AddUniform("material.specular");
    shader.AddUniform("material.shininess");
    
    
    shader.AddUniform("light.position");
    shader.AddUniform("light.ambient");
    shader.AddUniform("light.diffuse");
    shader.AddUniform("light.specular");

    glUniform3fv(shader(Mat_Ambient),1,glm::value_ptr(mat.ambient));
    glUniform3fv(shader(Mat_Diffuse),1,glm::value_ptr(mat.diffuse));
    glUniform3fv(shader(Mat_Specular),1,glm::value_ptr(mat.specular));
    glUniform1f(shader(Mat_Shininess),mat.shininess);
    
    glUniform3fv(shader("light.position"),1,glm::value_ptr(lPos));
    glUniform3fv(shader("light.ambient"),1,glm::value_ptr(lambient));
    glUniform3fv(shader("light.diffuse"),1,glm::value_ptr(ldiffuse));
    glUniform3fv(shader("light.specular"),1,glm::value_ptr(lspecular));
    // Material uniform
    GLenum err = glGetError();
            
    shader.UnUse();

    GL_CHECK_ERRORS;
    std::cout<<"\n x : "<<GetPosition().x<<"y : "<<GetPosition().y<<"z : "<<GetPosition().z;
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

    
    glUniform3fv(shader("light.position"),1,glm::value_ptr(lPos));
    glUniform3fv(shader("light.ambient"),1,glm::value_ptr(lambient));
    glUniform3fv(shader("light.diffuse"),1,glm::value_ptr(ldiffuse));
    glUniform3fv(shader("light.specular"),1,glm::value_ptr(lspecular));
    GL_CHECK_ERRORS;
    
    if(Input::GetInstance().IsKeyDown(GLFW_KEY_A))
    {
        Rotate(10, 0, 0);
    }
    if(Input::GetInstance().IsKeyDown(GLFW_KEY_S))
    {
        Rotate(0, 10, 0);
    } if(Input::GetInstance().IsKeyDown(GLFW_KEY_D))
    {
        Strafe(-GetScale().x/2);
        std::cout<<"\n x : "<<GetPosition().x<<"y : "<<GetPosition().y<<"z : "<<GetPosition().z;
        Rotate(0, 0, 10);
        Strafe(GetScale().x/2);
        std::cout<<"\n x : "<<GetPosition().x<<"y : "<<GetPosition().y<<"z : "<<GetPosition().z;
     }
    if(Input::GetInstance().IsKeyDown(GLFW_KEY_Q))
    {
        scale(1, 0, 0);
        //std::cout<<"\n x : "<<GetScale().x<<"y : "<<GetScale().y<<"z : "<<GetScale().z;
    }
    
}




