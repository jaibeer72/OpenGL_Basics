//
//  Skybox.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 11/12/2022.
//

#include "Skybox.hpp"
#include "TexLoading.hpp"


Skybox::Skybox(std::string skyBoxPath) { 
    //generate the cube object
    shader.LoadFromFile(GL_VERTEX_SHADER, "/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/Shaders/Skybox/skybox.vert");
    shader.LoadFromFile(GL_FRAGMENT_SHADER, "/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/Shaders/Skybox/skybox.frag");
    //compile and link shader
    shader.CreateAndLinkProgram();
    shader.Use();
        //add shader attributes and uniforms
        shader.AddAttribute("vVertex",0);
        shader.AddUniform("VP");
        shader.AddUniform("vModel");
        shader.AddUniform("cubeMap");
        //set constant shader uniforms at initialization
        glUniform1i(shader("cubeMap"),0);
    shader.UnUse();
    
    texID = TexLoading::loadCubeMap(skyBoxPath,".jpg");
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
    
    GL_CHECK_ERRORS;
    
    SetPosition(glm::vec3(1,1,1)) ;
    UpdateTransform();
    SetScale(1000, 1000, 1000);
    UpdateTransform();
    
}

int Skybox::GetTotalVertices() { 
    return 8;
}

int Skybox::GetTotalIndices() { 
    //6 faces with 2 triangles each with 3 vertices
        return 6*2*3;
}

GLenum Skybox::GetPrimitiveType() { 
    return GL_TRIANGLES;
}

int Skybox::GetTotalNormal() { 
    return 0;
}

void Skybox::FillVertexBuffer(GLfloat *pBuffer) { 
    glm::vec3* vertices = (glm::vec3*)(pBuffer);
    vertices[0]=glm::vec3(-0.5f,-0.5f,-0.5f);
    vertices[1]=glm::vec3( 0.5f,-0.5f,-0.5f);
    vertices[2]=glm::vec3( 0.5f, 0.5f,-0.5f);
    vertices[3]=glm::vec3(-0.5f, 0.5f,-0.5f);
    vertices[4]=glm::vec3(-0.5f,-0.5f, 0.5f);
    vertices[5]=glm::vec3( 0.5f,-0.5f, 0.5f);
    vertices[6]=glm::vec3( 0.5f, 0.5f, 0.5f);
    vertices[7]=glm::vec3(-0.5f, 0.5f, 0.5f);
}

void Skybox::FillColorBuffer(GLfloat *pBuffer) { 
    
}

void Skybox::FillIndexBuffer(GLuint *pBuffer) { 
    GLuint* id=pBuffer;

    //bottom face
    *id++ = 0;     *id++ = 4;     *id++ = 5;
    *id++ = 5;     *id++ = 1;     *id++ = 0;
    
    //top face
    *id++ = 3;     *id++ = 6;     *id++ = 7;
    *id++ = 3;     *id++ = 2;     *id++ = 6;

    //front face
    *id++ = 7;     *id++ = 6;     *id++ = 4;
    *id++ = 6;     *id++ = 5;     *id++ = 4;

    //back face
    *id++ = 2;     *id++ = 3;     *id++ = 1;
    *id++ = 3;     *id++ = 0;     *id++ = 1;

    //left face
    *id++ = 3;     *id++ = 7;     *id++ = 0;
    *id++ = 7;     *id++ = 4;     *id++ = 0;

    //right face
    *id++ = 6;     *id++ = 2;     *id++ = 5;
    *id++ = 2;     *id++ = 1;     *id++ = 5;
}

void Skybox::FillNormalBuffer(GLfloat *pBuffer) { 
    
}

void Skybox::SetCustomUniforms() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
}









