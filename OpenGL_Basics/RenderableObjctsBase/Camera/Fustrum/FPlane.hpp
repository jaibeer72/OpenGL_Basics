//
//  FPlane.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 09/11/2022.
//

#pragma once
#ifndef FPlane_hpp
#define FPlane_hpp

#include <glm/glm.hpp>

class FPlane {
    enum Where {COPLANAR, FRONT, BACK};
    
public:
    FPlane(void);
    FPlane(const glm::vec3& N, const glm::vec3& p);
    ~FPlane(void);
    
    static FPlane FromPoints(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3);
    Where Classify(const glm::vec3& p);
    float GetDistance(const glm::vec3& p);


    glm::vec3 N;
    float d;
};

#endif /* FPlane_hpp */
