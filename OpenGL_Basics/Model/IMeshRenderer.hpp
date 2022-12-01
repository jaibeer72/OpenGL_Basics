//
//  IMeshRenderer.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 24/11/2022.
//

#pragma once
#ifndef IMeshRenderer_hpp
#define IMeshRenderer_hpp

#include "GLSLShader.hpp"
#include "Transform.hpp"
#include "ILight.hpp"
#include "Mesh.hpp"

struct BoneInfo
{
    /*id is index in finalBoneMatrices*/
    int id;

    /*offset matrix transforms vertex from model space to bone space*/
    glm::mat4 offset;

};

class IMeshRendeer : public Transform
{
public:
    IMeshRendeer();
    std::vector<Mesh> MeshBuffer;
    virtual void FillMeshBuffer(std::vector<Mesh> & VertexNormals) = 0;
    virtual int GetToalVertices()=0;
    virtual GLenum GetPrimitiveType()=0;
    virtual void SetCustomUniforms() =0;
    virtual void DrawStyle()=0;
    
    void Init();
    void Render(const float* VP , glm::vec3 camPos);
    void Destroy();
    IMeshRendeer* ReturnMeshRendere(){return this;}
    Material mat;
    Light lit;
protected:
    GLuint vaoID;
    GLuint vboVerticesID;
    GLuint vboIndicesID;
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

#endif /* IMeshRenderer_hpp */
