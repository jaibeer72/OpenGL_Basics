//
//  ClockScene.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 17/11/2022.
//

#include "ClockScene.hpp"
#include "Input.hpp"

void ClockScene::SetCylenderTransformations(ClockScene &object) {
    object.cylender->mat.diffuse = glm::vec3(0,0,1);
    object.cylender->mat.specular = glm::vec3(0,0,1);
    object.cylender->mat.shininess = 35;
    object.cylender->lit.ambient= glm::vec3(0,0,1);
    glm::vec3 c_scale,c_pos,c_rot;
    c_pos = glm::vec3(1,10,1);
    c_scale = glm::vec3(7,0.5,7);
    c_rot = glm::vec3(90,0,0);
    
    object.cylender->SetPosition(c_pos);
    object.cylender->SetScale(c_scale.x, c_scale.y, c_scale.z);
    object.cylender->SetRotation(c_rot.x, c_rot.y, c_rot.z);
    object.cylender->UpdateTransform();
    
}

void ClockScene::MessWithMaterials(ILitObject* obj, bool isIn)
{
    Material objMat = obj->mat;
    if (isIn) {
        objMat.ambient+=0.1;
        objMat.diffuse+=0.1;
        objMat.specular+=0.1;
        objMat.shininess+=0.1;
    }
    else
    {
        objMat.ambient-=0.1;
        objMat.diffuse-=0.1;
        objMat.specular-=0.1;
        objMat.shininess-=0.1;
    }
    obj->mat = objMat;
}

ClockScene::ClockScene() {
    glm::vec3 sec_scale,sec_pos,sec_rot;
    sec_pos = glm::vec3(1,13,0);
    sec_scale = glm::vec3(0.01,6,0.1);
    sec_rot = glm::vec3(0,0,0);

    glm::vec3 hour_scale = glm::vec3(0.1,4,0.1);
    glm::vec3 hour_pos = glm::vec3(1,12,0);
    glm::vec3 min_scale = glm::vec3(0.1,6,0.1);
    
    
    
    secArm = new Lit_UnitCube(sec_pos,sec_scale,sec_rot);
    minArm = new Lit_UnitCube(sec_pos,min_scale,sec_rot);
    hourArm = new Lit_UnitCube(hour_pos,hour_scale,sec_rot);
    
    cylender = new Cylinder();
    SetCylenderTransformations(*this);
    
    // setting material and lights
    Material mat;
    mat.ambient = glm::vec3(1.0f, 0.5f, 0.31f);
    mat.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
    mat.specular = glm::vec3(0.5f, 0.5f, 0.5f);
    mat.shininess = 32.0f;
    
    Light lit;
    lit.position = glm::vec3(0,6,-2);
    lit.ambient = glm::vec3( 0.2f, 0.2f, 0.2f);
    lit.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    lit.specular = glm::vec3( 1.0f, 1.0f, 1.0f);
    
    cylender->lit = lit;
    cylender->mat = mat;
    secArm->lit = lit;
    minArm->lit = lit;
    hourArm->lit = lit;

}

void ClockScene::Initialize() {
    secArm->Init();
    minArm->Init();
    hourArm->Init();
    cylender->Init();
    std::cout<< secArm->GetPosition().x;
}

void ClockScene::RenderObjects(const float *VP, const glm::vec3 &camPos) {
    secArm->Render(VP,camPos);
    minArm->Render(VP,camPos);
    hourArm->Render(VP,camPos);
    cylender->Render(VP, camPos);
}

void ClockScene::Update(const float *VP, glm::vec3 camPos) {
    RenderObjects(VP, camPos);
    
    info = T_Time.GetCurrentTime();
    
    // Seconds Arm
    secArm->Lift(-secArm->GetScale().y/2);
    secArm->SetRotation(0, 0, (360/60)*info->tm_sec);
    secArm->UpdateTransform();
    secArm->Lift(secArm->GetScale().y/2);
    
    // Minutes Arm
    minArm->Lift(-minArm->GetScale().y/2);
    minArm->SetRotation(0, 0, (360/60)*info->tm_min);
    minArm->UpdateTransform();
    minArm->Lift(minArm->GetScale().y/2);
    
    // hours Arm
    hourArm->Lift(-hourArm->GetScale().y/2);
    hourArm->SetRotation(0, 0, (360/60)*info->tm_hour);
    hourArm->UpdateTransform();
    hourArm->Lift(hourArm->GetScale().y/2);
    
    if(Input::IsKeyDown(GLFW_KEY_Q))
    {
        MessWithMaterials(cylender, true);
        MessWithMaterials(secArm, true);
        MessWithMaterials(minArm, true);
        MessWithMaterials(hourArm, true);
    }
    if(Input::IsKeyDown(GLFW_KEY_E))
    {
        MessWithMaterials(cylender, false);
        MessWithMaterials(secArm, false);
        MessWithMaterials(minArm, false);
        MessWithMaterials(hourArm, false);
    }
    if(Input::IsKeyDown(GLFW_KEY_LEFT))
    {
        MessWithLight(cylender, true);
        MessWithLight(secArm, true);
        MessWithLight(minArm, true);
        MessWithLight(hourArm, true);
    }
    if(Input::IsKeyDown(GLFW_KEY_RIGHT))
    {
        MessWithLight(cylender, false);
        MessWithLight(secArm, false);
        MessWithLight(minArm, false);
        MessWithLight(hourArm, false);
    }
    if(Input::IsKeyDown(GLFW_KEY_UP))
    {
        cylender->lit.specular+=0.1f;
        secArm->lit.specular+=0.1f;
        minArm->lit.specular+=0.1f;
        hourArm->lit.specular+=0.1f;
    }
    if(Input::IsKeyDown(GLFW_KEY_DOWN))
    {
        cylender->lit.specular-=0.1f;
        secArm->lit.specular-=0.1f;
        minArm->lit.specular-=0.1f;
        hourArm->lit.specular-=0.1f;
    }
    
}

void ClockScene::Destroy() {
}

void ClockScene::MessWithLight(ILitObject *obj, bool isIn) {
    Light lit = obj->lit;
    if(isIn)
    {
        lit.position.x += 0.1;
//        lit.ambient += 0.1;
//        lit.diffuse += 0.1;
//        lit.specular += 0.1;
    }
    else
    {
        lit.position.x -= 0.1;
//        lit.ambient -= 0.1;
//        lit.diffuse -= 0.1;
//        lit.specular -= 0.1;
    }
    obj->lit = lit;
}






