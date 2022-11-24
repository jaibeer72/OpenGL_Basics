//
//  Model.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 24/11/2022.
//

#ifndef Model_hpp
#define Model_hpp
#include "Mesh.hpp"
#include "IMeshRenderer.hpp"

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model : public IMeshRendeer
{
public:
    // model data
    std::vector<Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh>    meshes;
    std::string directory;
    bool gammaCorrection;
    
    Model(std::string const &path, bool gamma = false);
    
};

#endif /* Model_hpp */
