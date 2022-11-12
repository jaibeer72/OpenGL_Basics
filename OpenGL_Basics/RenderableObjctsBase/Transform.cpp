//
//  Transform.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 11/11/2022.
//

#include "Transform.hpp"

Transform::Transform() {
    translation =glm::vec3(0);
    speed = 0.5f; // 0.5 m/s
    Update();
}

void Transform::Walk(const float dt) {
    translation += (look*speed*dt);
    Update();
}

void Transform::Strafe(const float dt) {
    translation += (right*speed*dt);
    Update();
}

void Transform::Lift(const float dt) {
    translation += (up*speed*dt);
    Update();
}

void Transform::SetTranslation(const glm::vec3 &t) {
    translation = t;
    Update();
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
    yaw = glm::radians(Yaw);
    pitch = glm::radians(Pitch);
    roll = glm::radians(Roll);
    Update();
}

const glm::vec3 Transform::GetPosition() const {
    return Postion;
}

const glm::vec3 Transform::GetRotation() const {
    return glm::vec3(yaw,pitch,roll);
}

void Transform::Update() {
    
    Postion+=translation;
    
    translation=glm::vec3(0);
    
    model = glm::mat4(1.0f);
    model = glm::translate(model, Postion);
    model = glm::scale(model, Scale);
    model = glm::rotate(model, glm::radians(yaw), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(pitch), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(roll), glm::vec3(0.0f, 0.0f, 1.0f));
}












