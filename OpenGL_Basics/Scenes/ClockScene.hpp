//
//  ClockScene.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 17/11/2022.
//

#pragma once
#ifndef ClockScene_hpp
#define ClockScene_hpp

#include "Lit_UnitCube.hpp"
#include "Time.hpp"

class ClockScene
{
public:
    ClockScene();
    void Initialize();
    void extracted(const float *VP, const glm::vec3 &camPos);
    
    void Update(const float* VP,glm::vec3 camPos);
    void Destroy();
    
    // objects required
    Lit_UnitCube* secArm;
    
private:
    void RenderObjects(const float *VP, const glm::vec3 &camPos);
    Time T_Time;
    struct tm *info;
};

#endif /* ClockScene_hpp */
