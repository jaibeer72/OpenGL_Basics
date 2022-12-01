//
//  AssImpGLMHelper.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 28/11/2022.
//

#pragma once
#ifndef AssImpGLMHelper_hpp
#define AssImpGLMHelper_hpp

#include<assimp/quaternion.h>
#include<assimp/vector3.h>
#include<assimp/matrix4x4.h>
#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>


class AssimpGLMHelpers
{
public:

    static glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4& from);

    static glm::vec3 GetGLMVec(const aiVector3D& vec);

    static glm::quat GetGLMQuat(const aiQuaternion& pOrientation);
};

#endif /* AssImpGLMHelper_hpp */
