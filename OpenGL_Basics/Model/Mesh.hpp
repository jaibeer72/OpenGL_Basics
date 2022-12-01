//
//  Mesh.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 24/11/2022.
//

#pragma once
#ifndef Mesh_hpp
#define Mesh_hpp

#include "GLSLShader.hpp"
#include "ILight.hpp"

class Mesh
{
public:
    // mesh Data
    std::vector<Vertex>       Vertices;
    std::vector<unsigned int> Indices;
    std::vector<Texture>      Textures;
    
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
        {
            this->Vertices = vertices;
            this->Indices = indices;
            this->Textures = textures;

        }

};
#endif /* Mesh_hpp */
