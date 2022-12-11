//
//  TexLoading.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 28/11/2022.
//

#pragma once
#ifndef TexLoading_hpp
#define TexLoading_hpp

#include <stb_image.h>
#include "ILight.hpp"
#include <assimp/scene.h>

class TexLoading {
public:
    static GLuint loadTexture( const std::string & fName );
    static GLuint loadCubeMap(const std::string & baseName, const std::string & extention = ".png",bool flip = false);
    static GLuint loadHdrCubeMap( const std::string & baseName );
    static unsigned char * loadPixels( const std::string & fName, int & w, int & h, bool flip = true );
    static void deletePixels( unsigned char * data);
};

#endif /* TexLoading_hpp */
