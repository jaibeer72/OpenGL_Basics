//
//  FPlane.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 09/11/2022.
//

#include "FPlane.hpp"

const float EPSILON= 0.0001f;

float FPlane::GetDistance(const glm::vec3 &p) { 
    return glm::dot(N,p)+d;
}


FPlane FPlane::FromPoints(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3) { 
    FPlane temp;
    glm::vec3 e1 = v2-v1;
    glm::vec3 e2 = v3-v1;
    temp.N = glm::normalize(glm::cross(e1,e2));
    temp.d = -glm::dot(temp.N, v1);
    return temp;
}


FPlane::Where FPlane::Classify(const glm::vec3 &p) { 
    float res = GetDistance(p);
    if( res > EPSILON)
        return FRONT;
    else if(res < EPSILON)
        return BACK;
    else
        return COPLANAR;
}


FPlane::FPlane(const glm::vec3 &normal, const glm::vec3 &p) {
    N = normal;
    d = -glm::dot(N,p);
}


FPlane::FPlane(void) {
}

FPlane::~FPlane(void)  {
}

