//
//  Mesh.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 24/11/2022.
//

#pragma once
#ifndef Mesh_hpp
#define Mesh_hpp

#include "IMeshRenderer.hpp"

class Mesh
{
public:
    // mesh Data
    std::vector<Vertex>       Vertices;
    std::vector<unsigned int> Indices;
    std::vector<Texture>      Textures;
    
};
#endif /* Mesh_hpp */
