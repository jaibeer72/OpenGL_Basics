//
//  IMeshRenderer.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 24/11/2022.
//

#include "IMeshRenderer.hpp"


void IMeshRendeer::Init() {
    
    FillMeshBuffer(MeshBuffer);
    
    for( Mesh m : MeshBuffer)
    {
        // create buffers/arrays
        glGenVertexArrays(1, &vaoID);
        glGenBuffers(1, &vboVerticesID);
        glGenBuffers(1, &vboIndicesID);
        
        //now allocate buffers
        glBindVertexArray(vaoID);

        glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
        glBufferData(GL_ARRAY_BUFFER, m.Vertices.size() *sizeof(Vertex), &m.Vertices[0], GL_STATIC_DRAW);
        
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.Indices.size() * sizeof(unsigned int), &m.Indices[0], GL_STATIC_DRAW);
        
        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        // vertex tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
        // vertex bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, BitTangent));
        // ids
        glEnableVertexAttribArray(5);
        glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

        // weights
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
        
        glBindVertexArray(0);
        
    }
}

void IMeshRendeer::Render(const float *VP, glm::vec3 camPos) {
    
    shader.Use();
    glUniformMatrix4fv(shader("VP"), 1, GL_FALSE, VP);
    glUniform3fv(shader("viewPos"),1,glm::value_ptr(camPos));
    glUniformMatrix4fv(shader("vModel"),1,GL_FALSE,glm::value_ptr(model));
    for(Mesh m : MeshBuffer)
    {
        // for meshes
        unsigned int diffuseNr  = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr   = 1;
        unsigned int heightNr   = 1;
        for(unsigned int i = 0; i < m.Textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 +i ); // active proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = m.Textures[i].type;
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to string
            else if(name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to string
             else if(name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to string

            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, m.Textures[i].id);
            SetCustomUniforms();
        }
        glBindVertexArray(vaoID);
        DrawStyle();
        glDrawElements(primType,  static_cast<unsigned int>(m.Indices.size()), GL_UNSIGNED_INT, 0);
        //shader.PrintGLerror();
    }
    shader.UnUse();
}

void IMeshRendeer::Destroy() { 

}

IMeshRendeer::IMeshRendeer() {
}



