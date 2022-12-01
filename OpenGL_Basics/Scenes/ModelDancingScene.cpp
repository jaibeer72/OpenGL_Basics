//
//  ModelDancingScene.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 30/11/2022.
//

#include "ModelDancingScene.hpp"


ModelDancingScene::ModelDancingScene() {
    const std::string path = "../../../OpenGL_Basics/assets/Capoeira.dae";
    DancingModel = new Model(path,false);
    //Animation danceAnimation(path,&DancingModel);
    //Animator animator(&danceAnimation);
    DancingModel->Scale(5, 5, 5);
    
}

void ModelDancingScene::Initialize() {
    DancingModel->Init();
    
}

void ModelDancingScene::Update(const float *VP, glm::vec3 camPos) {
    RenderObjects(VP, camPos);
    float currentFrame = glfwGetTime();
    //deltaTime = currentFrame - lastFrame;
    //lastFrame = currentFrame;
    
}

void ModelDancingScene::RenderObjects(const float *VP, const glm::vec3 &camPos) {
    DancingModel->Render(VP, camPos);
    
}



