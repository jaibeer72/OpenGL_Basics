//
//  FreeCamera.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 09/11/2022.
//

#pragma once
#ifndef FreeCamera_hpp
#define FreeCamera_hpp

#include "ICamera.hpp"

class CFreeCamera : public ICamera
{
public:
    CFreeCamera(void);
    ~CFreeCamera(void);

    void Update();
     
    void Walk(const float dt);
    void Strafe(const float dt);
    void Lift(const float dt);
      
    void SetTranslation(const glm::vec3& t);
    glm::vec3 GetTranslation() const;

    void SetSpeed(const float speed);
    const float GetSpeed() const;

protected:
    
    float speed =0.5;            //move speed of camera in m/s
    glm::vec3 translation;
};


#endif /* FreeCamera_hpp */
