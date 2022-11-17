//
//  ClockScene.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 17/11/2022.
//

#include "ClockScene.hpp"
#include "Input.hpp"

ClockScene::ClockScene() {
    glm::vec3 sec_scale,sec_pos,sec_rot;
    sec_scale = glm::vec3(0.1,6,0.1);
    sec_pos = glm::vec3(2,6,0);
    sec_rot = glm::vec3(0,0,0);
    
    secArm = new Lit_UnitCube(sec_pos,sec_scale,sec_rot);
    
}

void ClockScene::Initialize() {
    secArm->Init();
    std::cout<< secArm->GetPosition().x;
}

void ClockScene::RenderObjects(const float *VP, const glm::vec3 &camPos) {
    secArm->Render(VP,camPos);
}

void ClockScene::Update(const float *VP, glm::vec3 camPos) {
    RenderObjects(VP, camPos);
    
    info = T_Time.GetCurrentTime();
    secArm->Lift(-secArm->GetScale().y/2);
    secArm->SetRotation(0, 0, (360/60)*info->tm_sec);
    secArm->Update();
    std::cout<<asctime(info);
    secArm->Lift(secArm->GetScale().y/2);
    
}

void ClockScene::Destroy() {
}





