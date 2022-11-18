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
#include "Cylinder.hpp"
#include "Time.hpp"

class ClockScene
{
public:
    Cylinder *extracted();
    
    ClockScene();
    void Initialize();
    void extracted(const float *VP, const glm::vec3 &camPos);
    
    void Update(const float* VP,glm::vec3 camPos);
    void Destroy();
    
    // objects required
    Lit_UnitCube* secArm;
    Lit_UnitCube* minArm;
    Lit_UnitCube* hourArm;
    Cylinder* cylender;
    
    Material secArmMat, minArmMat,HourArmMat;
    Light secArmLight, minArmLight , hourArmLight;
    
private:
    void RenderObjects(const float *VP, const glm::vec3 &camPos);
     void MessWithMaterials(ILitObject* obj, bool isIn);
     void SetCylenderTransformations(ClockScene &object);
    void MessWithLight(ILitObject* obj, bool isIn);
    
    
    Time T_Time;
    struct tm *info;
};

#endif /* ClockScene_hpp */
