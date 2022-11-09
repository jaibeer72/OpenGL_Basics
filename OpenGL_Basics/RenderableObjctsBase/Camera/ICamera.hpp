//
//  ICamera.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 09/11/2022.
//

#pragma once
#ifndef ICamera_hpp
#define ICamera_hpp

#include "Fustrum/FPlane.hpp"
#include <glm/gtc/matrix_transform.hpp>

class ICamera
{
public: 
    ICamera(void);
    ~ICamera(void);
    
    void SetupProjection(const float fovy, const float aspectRatio, const float near=0.1f, const float far=1000.0f);
    
    virtual void Update() = 0;
    virtual void Rotate(const float yaw, const float pitch, const float roll);

    const glm::mat4 GetViewMatrix() const;
    const glm::mat4 GetProjectionMatrix() const;

    void SetPosition(const glm::vec3& v);
    const glm::vec3 GetPosition() const;
     

    void SetFOV(const float fov);
    const float GetFOV() const;
    const float GetAspectRatio() const;
    
    
    void CalcFrustumPlanes();
    bool IsPointInFrustum(const glm::vec3& point);
    bool IsSphereInFrustum(const glm::vec3& center, const float radius);
    bool IsBoxInFrustum(const glm::vec3& min, const glm::vec3& max);
    void GetFrustumPlanes(glm::vec4 planes[6]);

    //frustum points
    glm::vec3 farPts[4];
    glm::vec3 nearPts[4];
    
protected:
    float yaw, pitch, roll, FieldOfView, aspect_ratio, Znear, Zfar;
    static glm::vec3 UP;
    glm::vec3 look;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 Postion;
    glm::mat4 V; //view matrix
    glm::mat4 P; //projection matrix
    
    //Frsutum planes
    FPlane planes[6];
};

#endif /* ICamera_hpp */
