//
//  UnitCube.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 11/11/2022.
//

#include "UnitCube.hpp"



int UnitCube::GetTotalVertices() { 
    return 8;
}


UnitCube::UnitCube(const glm::vec3 &col) {
    color = col;
        //generate the cube object
        shader.LoadFromFile(GL_VERTEX_SHADER, "/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/Shaders/ObjectShaders/UnitCube/UnitCube.vert");
        shader.LoadFromFile(GL_FRAGMENT_SHADER, "/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/Shaders/ObjectShaders/UnitCube/UnitCube.frag");
        shader.CreateAndLinkProgram();
        shader.Use();
            shader.AddAttribute("vVertex");
            shader.AddUniform("VP");
            shader.AddUniform("vColor");
            shader.AddUniform("vModel");
            glUniform3fv(shader("vColor"),1, glm::value_ptr(color));
        shader.UnUse();
         
        Init();
}

void UnitCube::SetCustomUniforms() { 
    glUniform3fv(shader("vColor"),1, glm::value_ptr(color));
}


void UnitCube::FillIndexBuffer(GLuint *pBuffer) { 
    GLuint* id=pBuffer;

    //bottom face
    *id++ = 0;     *id++ = 5;     *id++ = 4;
    *id++ = 5;     *id++ = 0;     *id++ = 1;
    
    //top face
    *id++ = 3;     *id++ = 7;     *id++ = 6;
    *id++ = 3;     *id++ = 6;     *id++ = 2;

    //front face
    *id++ = 7;     *id++ = 4;     *id++ = 6;
    *id++ = 6;     *id++ = 4;     *id++ = 5;

    //back face
    *id++ = 2;     *id++ = 1;     *id++ = 3;
    *id++ = 3;     *id++ = 1;     *id++ = 0;

    //left face
    *id++ = 3;     *id++ = 0;     *id++ = 7;
    *id++ = 7;     *id++ = 0;     *id++ = 4;

    //right face
    *id++ = 6;     *id++ = 5;     *id++ = 2;
    *id++ = 2;     *id++ = 5;     *id++ = 1;
}


void UnitCube::FillColorBuffer(GLfloat *pBuffer) { 
    

}


void UnitCube::FillVertexBuffer(GLfloat *pBuffer) { 
    glm::vec3* vertices = (glm::vec3*)(pBuffer);
    vertices[0]=glm::vec3(-0.5f,-0.5f,-0.5f) ;
    vertices[1]=glm::vec3( 0.5f,-0.5f,-0.5f) ;
    vertices[2]=glm::vec3( 0.5f, 0.5f,-0.5f) ;
    vertices[3]=glm::vec3(-0.5f, 0.5f,-0.5f) ;
    vertices[4]=glm::vec3(-0.5f,-0.5f, 0.5f) ;
    vertices[5]=glm::vec3( 0.5f,-0.5f, 0.5f) ;
    vertices[6]=glm::vec3( 0.5f, 0.5f, 0.5f) ;
    vertices[7]=glm::vec3(-0.5f, 0.5f, 0.5f) ;
}


GLenum UnitCube::GetPrimitiveType() { 
    return GL_TRIANGLES;
}


int UnitCube::GetTotalIndices() { 
    return 6*2*3;
}

