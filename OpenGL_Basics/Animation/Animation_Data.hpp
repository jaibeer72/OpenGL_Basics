//
//  Animation_Data.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 01/12/2022.
//

#pragma once
#ifndef Animation_Data_hpp
#define Animation_Data_hpp

#include<glm/glm.hpp>

struct BoneInfo
{
    /*id is index in finalBoneMatrices*/
    int id;

    /*offset matrix transforms vertex from model space to bone space*/
    glm::mat4 offset;

};

#endif /* Animation_Data_hpp */
