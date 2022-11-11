//
//  ICamera.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 09/11/2022.
//

#include "ICamera.hpp"


ICamera::ICamera(void) {
    Znear = 0.1f;
    Zfar  = 1000;
}

void ICamera::GetFrustumPlanes(glm::vec4 fp[6]) {
    for(int i=0;i<6;i++)
        fp[i]=glm::vec4(planes[i].N, planes[i].d);
}


bool ICamera::IsBoxInFrustum(const glm::vec3 &min, const glm::vec3 &max) { 
    
    for(int i=0; i < 6; i++)
    {
        glm::vec3 p=min, n=max;
        glm::vec3 N = planes[i].N;
        if(N.x>=0) {
            p.x = max.x;
            n.x = min.x;
        }
        if(N.y>=0) {
            p.y = max.y;
            n.y = min.y;
        }
        if(N.z>=0) {
            p.z = max.z;
            n.z = min.z;
        }

        if ( planes[i].GetDistance(p) < 0 ) {
            return false;
        }
    }
    return true;
}


bool ICamera::IsSphereInFrustum(const glm::vec3 &center, const float radius) { 
    for(int i=0; i < 6; i++)
    {
        float d = planes[i].GetDistance(center);
        if ( d < -radius)
            return false;
    }
    return true;
}


bool ICamera::IsPointInFrustum(const glm::vec3 &point) { 
    for(int i=0; i < 6; i++)
    {
        if (planes[i].GetDistance(point) < 0)
            return false;
    }
    return true;
}


void ICamera::CalcFrustumPlanes() { 
    glm::vec3 cN = Postion + look*Znear;
    glm::vec3 cF = Postion + look*Zfar;

    float Hnear = 2.0f * tan(glm::radians(FieldOfView / 2.0f) ) * Znear;
    float Wnear = Hnear * aspect_ratio;
    float Hfar = 2.0f * tan(glm::radians(FieldOfView / 2.0f)) * Zfar;
    float Wfar = Hfar * aspect_ratio;
    float hHnear = Hnear/2.0f;
    float hWnear = Wnear/2.0f;
    float hHfar = Hfar/2.0f;
    float hWfar = Wfar/2.0f;


    farPts[0] = cF + up*hHfar - right*hWfar;
    farPts[1] = cF - up*hHfar - right*hWfar;
    farPts[2] = cF - up*hHfar + right*hWfar;
    farPts[3] = cF + up*hHfar + right*hWfar;

    nearPts[0] = cN + up*hHnear - right*hWnear;
    nearPts[1] = cN - up*hHnear - right*hWnear;
    nearPts[2] = cN - up*hHnear + right*hWnear;
    nearPts[3] = cN + up*hHnear + right*hWnear;

    planes[0] = FPlane::FromPoints(nearPts[3],nearPts[0],farPts[0]);
    planes[1] = FPlane::FromPoints(nearPts[1],nearPts[2],farPts[2]);
    planes[2] = FPlane::FromPoints(nearPts[0],nearPts[1],farPts[1]);
    planes[3] = FPlane::FromPoints(nearPts[2],nearPts[3],farPts[2]);
    planes[4] = FPlane::FromPoints(nearPts[0],nearPts[3],nearPts[2]);
    planes[5] = FPlane::FromPoints(farPts[3] ,farPts[0] ,farPts[1]);
}


const float ICamera::GetAspectRatio() const { 
    return aspect_ratio;
}


const float ICamera::GetFOV() const { 
    return FieldOfView;
}


void ICamera::SetFOV(const float fov) {
    
    FieldOfView = fov;
    P = glm::perspective(fov, aspect_ratio, Znear, Zfar);
}


const glm::vec3 ICamera::GetPosition() const { 
    return Postion;;
}


void ICamera::SetPosition(const glm::vec3 &postion) {
    Postion = postion;
}


const glm::mat4 ICamera::GetProjectionMatrix() const { 
    return P;
}


const glm::mat4 ICamera::GetViewMatrix() const { 
    return V;
}


void ICamera::SetupProjection(const float fovy, const float aspectRatio, const float near, const float far) { 
    P = glm::perspective(fovy, aspectRatio, near, far);
        Znear = near;
        Zfar = far;
        FieldOfView = fovy;
        aspect_ratio = aspectRatio;
}

void ICamera::Rotate(const float y, const float p, const float r) {
    yaw=glm::radians(y);
  pitch=glm::radians(p);
   roll=glm::radians(r);
  Update();
}

ICamera::~ICamera() { 
}

const glm::vec3 ICamera::GetRotation() const { 
    return glm::vec3(yaw,pitch,roll);
}




