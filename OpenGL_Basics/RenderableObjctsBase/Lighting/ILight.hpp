//
//  ILight.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 14/11/2022.
//

#pragma once
#ifndef ILight_hpp
#define ILight_hpp

#include "GLSLShader.hpp"
#include "Transform.hpp"


struct Vertex{
    glm::vec3 Position, Normal;
};

struct Material
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

struct Light{
    glm::vec3 position = glm::vec3(10,10,10);
    glm::vec3 ambient = glm::vec3(1.0,1.0,0.0);
    glm::vec3 diffuse = glm::vec3(1.0,1.0,0.7);
    glm::vec3 specular = glm::vec3(1,1,0.25);
};

class ILitObject : public Transform
{
public:
    ILitObject();
    std::vector<Vertex> objectVertexNormals;
    virtual void FillVertexNormals(std::vector<Vertex> & VertexNormals) = 0;
    virtual int GetToalVertices()=0;
    virtual GLenum GetPrimitiveType()=0;
    virtual void SetCustomUniforms() =0;
    virtual void DrawStyle()=0;
    
    void Init();
    void Render(const float* VP , glm::vec3 camPos);
    void Destroy();
    ILitObject* ReturnLitObject(){return this;}
    Material mat;
    Light lit;
protected:
    GLuint vaoID;
    GLuint vboVerticesID;
    GLSLShader shader;
    GLenum primType;
    int totalVertices , totalNormals;
    const std::string Mat_Ambient = "material.ambient";
    const std::string Mat_Diffuse = "material.diffuse";
    const std::string Mat_Specular = "material.specular";
    const std::string Mat_Shininess = "material.shininess";
    
    const std::string Light_Position = "light.position";
    const std::string Light_Ambient = "light.ambient";
    const std::string Light_Diffuse = "light.diffuse";
    const std::string Light_Specular = "light.specular";
    
};


#endif /* ILight_hpp */
