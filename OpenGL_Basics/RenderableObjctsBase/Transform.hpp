//
//  Transform.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 11/11/2022.
//

#pragma once
#ifndef Transform_hpp
#define Transform_hpp

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Transform
{
    float yaw, pitch, roll;
    glm::vec3 Postion = glm::vec3(1.0f,2.0f,5.0f);
    glm::vec3 m_scale = glm::vec3(1.0f,1.0f,1.0f);
    glm::vec3 translation;
    
    glm::vec3 look = glm::vec3(0,0,1); // forward
    glm::vec3 up = glm::vec3(0,1,0);
    glm::vec3 right = glm::vec3(1,0,0);
    
public:
    Transform();
    void Walk(const float dt);
    void Strafe(const float dt);
    void Lift(const float dt);
      
    void SetTranslation(const glm::vec3& t);
    glm::vec3 GetTranslation() const;

    void SetSpeed(const float Speed);
    const float GetSpeed() const;
    
    void SetPosition(const glm::vec3& v);
    void Rotate(const float yaw, const float pitch, const float roll);
    
    void SetRotation(const float yaw, const float pitch, const float roll);
    
    void Scale(const float x, const float y , const float z);
    void SetScale(const float x, const float y , const float z);
    
    const glm::vec3 GetPosition() const;
    
    const glm::vec3 GetRotation() const;
    const glm::vec3 GetScale() const;
    
    friend std::ostream& operator <<(std::ostream& os, const Transform& dt);
    
    void UpdateTransform();
    
    // model matrix
    glm::mat4 model;
    
    
protected:
    float speed = 0.5f;
};

#endif /* Transform_hpp */
