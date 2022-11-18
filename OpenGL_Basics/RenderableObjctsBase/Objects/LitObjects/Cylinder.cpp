//
//  Cylinder.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 17/11/2022.
//

#include "Cylinder.hpp"

const float PI = 3.141592653589f;

Cylinder::Cylinder()
{
    this->definition = 100;
    this->radius = 1.0f;
    this->length = 1.0f;
    numberOfvertices = definition*4+2;
    
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
    
    glUniform3fv(shader(Light_Position),1,glm::value_ptr(lit.position));
    glUniform3fv(shader(Light_Ambient),1,glm::value_ptr(lit.ambient));
    glUniform3fv(shader(Light_Diffuse),1,glm::value_ptr(lit.diffuse));
    glUniform3fv(shader(Light_Specular),1,glm::value_ptr(lit.specular));
            
    shader.UnUse();

    GL_CHECK_ERRORS;
}

void Cylinder::FillVertexNormals(std::vector<Vertex> &VertexNormals){
    glm::vec3 vertices[402];
    glm::vec3 normals[402];
    
    GLuint pindices[406]; //204 //201
    for (int i = 0; i < 101; i++)
    {
        pindices[i] = i;
    }
    pindices[101] = 1;
    for (int i = 102; i < 203; i++)
    {
        pindices[i] = i -1;
    }
    pindices[203] = 102;

    for (int i = 204; i < 404; i++)
    {
        pindices[i] = i - 2;
    }
    pindices[404] = 202;
    pindices[405] = 203;
    
    //number of pVertieces is total points * 3;
    GLfloat halfLength = this->length / 2;
    
    vertices[0] = glm::vec3(0, halfLength, 0);
    normals[0] = glm::vec3(0.0, 1.0, 0.0);
    
    for (int i = 1; i < this->definition +1; i++)
    {
        GLfloat theta = (2 * PI) / this->definition * i;

        GLfloat x = radius * cos(theta);
        GLfloat y = halfLength;
        GLfloat z = radius*sin(theta);

        vertices[i] = glm::vec3(x, y, z);
        normals[i] = glm::vec3(0.0, 1.0, 0.0);
    }
    vertices[101] = glm::vec3(0, -halfLength, 0);
    normals[101] = glm::vec3(0.0, -1.0, 0.0);
    
    
    //for every point around the circle
    for (int i = 102; i < (this->definition*2) + 2; i++)
    {
        GLfloat theta = (2 * PI) / this->definition * (i - 102);
        
        GLfloat x = radius * cos(theta);
        GLfloat y = -halfLength;
        GLfloat z = radius* sin(theta);

        vertices[i] = glm::vec3(x, y, z);
        normals[i] = glm::vec3(0.0, -1.0, 0.0);
    }
    //sides                202                                402
    int top = 1;
    int bottom = 102;
    for (int i = ((this->definition * 2) + 2); i < numberOfvertices; i += 2)
    {
        vertices[i] = vertices[top];
        normals[i] = glm::vec3(vertices[top].x, 0.0, vertices[top].z);
        vertices[i + 1] = vertices[bottom];
        normals[i + 1] = glm::vec3(vertices[bottom].x, 0.0, vertices[bottom].z);
        top++;
        bottom++;
    }
    int size = (sizeof(pindices)/sizeof(GLuint));
    VertexNormals.resize(size);
    for(int i = 0 ; i < size ; i++)
    {
        Vertex v ;
        v.Position = vertices[pindices[i]];
        v.Normal = normals[pindices[i]];
        VertexNormals[i]=v;
    }
}

int Cylinder::GetToalVertices()
{
    return numberOfvertices ;
}

GLenum Cylinder::GetPrimitiveType()
{
    return GL_TRIANGLE_FAN;
}

void Cylinder::SetCustomUniforms()
{
    glUniform3fv(shader(Mat_Ambient),1,glm::value_ptr(mat.ambient));
    glUniform3fv(shader(Mat_Diffuse),1,glm::value_ptr(mat.diffuse));
    glUniform3fv(shader(Mat_Specular),1,glm::value_ptr(mat.specular));
    glUniform1f(shader(Mat_Shininess),mat.shininess);

    
    glUniform3fv(shader(Light_Position),1,glm::value_ptr(lit.position));
    glUniform3fv(shader(Light_Ambient),1,glm::value_ptr(lit.ambient));
    glUniform3fv(shader(Light_Diffuse),1,glm::value_ptr(lit.diffuse));
    glUniform3fv(shader(Light_Specular),1,glm::value_ptr(lit.specular));
    GL_CHECK_ERRORS;
}

void Cylinder::DrawStyle() {
    int numfanvertices = definition + 2;
    int numsidevertices = numfanvertices * 2;
    int side_offset = definition * 2 + 2;
    
    //glDrawArrays(GL_TRIANGLE_FAN,0,numberOfvertices);
    // Draw the top lid
    glDrawArrays(GL_TRIANGLE_FAN, 0,numfanvertices);
    glDrawArrays(GL_TRIANGLE_FAN, numfanvertices  ,numfanvertices);
    glDrawArrays(GL_TRIANGLE_STRIP,side_offset,numsidevertices);
}
