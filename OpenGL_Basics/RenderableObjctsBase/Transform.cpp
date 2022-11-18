//
//  Transform.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 11/11/2022.
//

#include "Transform.hpp"

#include <glm/gtx/euler_angles.hpp>

Transform::Transform() {
    translation = Postion;
    speed = 1.0f; // 0.5 m/s
    UpdateTransform();
}

void Transform::Walk(const float dt) {
    translation += (look*speed*dt);
    UpdateTransform();
}

void Transform::Strafe(const float dt) {
    translation += (right*dt);
    UpdateTransform();
}

void Transform::Lift(const float dt) {
    translation += (up*speed*dt);
    UpdateTransform();
}

void Transform::SetTranslation(const glm::vec3 &t) {
    translation = t;
    UpdateTransform();
}

glm::vec3 Transform::GetTranslation() const {
    return translation;
}

void Transform::SetSpeed(const float Speed) {
    speed = Speed;
}

const float Transform::GetSpeed() const {
    return speed;
}

void Transform::SetPosition(const glm::vec3 &v) {
    Postion = v;
}

void Transform::Rotate(const float Yaw, const float Pitch, const float Roll) {
    yaw += glm::radians(Yaw);
    pitch += glm::radians(Pitch);
    roll += glm::radians(Roll);
    UpdateTransform();
}

const glm::vec3 Transform::GetPosition() const {
    return Postion;
}

const glm::vec3 Transform::GetRotation() const {
    return glm::vec3(yaw,pitch,roll);
}

void Transform::UpdateTransform() {
    
    glm::mat4 R = glm::yawPitchRoll(yaw,pitch,roll);
    
    Postion+=translation;
    
    translation=glm::vec3(0);
    
    model = glm::mat4(1.0f);
    model = glm::translate(model, Postion);
    
    model = glm::rotate(model, yaw, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, pitch, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, roll, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, m_scale);
    
    look = glm::vec3(R*glm::vec4(0,0,1,0));
    up   = glm::vec3(R*glm::vec4(0,1,0,0));
    right = glm::cross(look, up);

}

void Transform::Scale(const float x, const float y, const float z) {
    m_scale.x += x;
    m_scale.y += y;
    m_scale.z += z;
    UpdateTransform();
}

const glm::vec3 Transform::GetScale() const { 
    return m_scale;
}

void Transform::SetScale(const float x, const float y, const float z) {
    m_scale = glm::vec3(x,y,z);
}

void Transform::SetRotation(const float Yaw, const float Pitch, const float Roll) {
    yaw = glm::radians(Yaw);
    pitch = glm::radians(Pitch);
    roll = glm::radians(Roll);
}

std::ostream& operator<<(std::ostream& os, const Transform& dt)
{
    os <<" Scale X :" <<dt.GetScale().x << "Y : " << dt.GetScale().y << "Z : " << dt.GetScale().z << std::endl;
    os <<" Pos X :" <<dt.GetPosition().x << "Y : " << dt.GetPosition().y << "Z : " << dt.GetPosition().z << std::endl;
    os <<" Rot X :" <<dt.GetRotation().x << "Y : " << dt.GetRotation().y << "Z : " << dt.GetRotation().z << std::endl;
    return os;
}














