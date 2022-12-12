//
//  FinalSubmissionBaseScene.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 11/12/2022.
//

#include "FinalSubmissionBaseScene.hpp"
#include "Input.hpp"


void FinalSubmissionBase::Init() {
    // model loading
    ourShader.LoadFromFile(GL_VERTEX_SHADER, "/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/Shaders/model_loading.vert");
    ourShader.LoadFromFile(GL_FRAGMENT_SHADER, "/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/Shaders/model_loading.frag");
    ourShader.CreateAndLinkProgram();
    for(int i =0 ; i<3 ; i++)
    {
        ourModel[i] = new Model("/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/assets/Capoeira.dae");
        
        danceAnimation[i] = new Animation("/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/assets/Capoeira.dae",ourModel[i]);
        animator[i] = new Animator(danceAnimation[i]);
    }
    ourModel[1]->SetPosition(glm::vec3(2,0,0));
    ourModel[1]->UpdateTransform();
    ourModel[2]->SetPosition(glm::vec3(-2,0,0));
    ourModel[2]->UpdateTransform();
    m_skybox = new Skybox("/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/assets/Skybox/leanOpenGLSkyBox/l");
    m_skybox->Init();
    
    plane = new LitTexPlane(10,10);
    plane->Init();
    plane->Rotate(180, 0, 0);
    
    plane2 = new LitTexPlane(10,10);
    plane2->Init();
    plane2->SetPosition(glm::vec3(0,5,0));
    plane2->UpdateTransform();

}

void FinalSubmissionBase::update(float dt,CFreeCamera* mainCamera) {
    
    glm::mat4 V    = mainCamera->GetViewMatrix();
    glm::mat4 P     = mainCamera->GetProjectionMatrix();
    glm::mat4 VP    = P*V;
    
    mainCamera->Rotate(Input::GetInstance().GetmousePos().x, Input::GetInstance().GetmousePos().y,0);
    
    m_skybox->Render(glm::value_ptr(VP));
    plane->Render(glm::value_ptr(VP),mainCamera->GetPosition());
    plane2->Render(glm::value_ptr(VP),mainCamera->GetPosition());
    
    GL_CHECK_ERRORS;
    ourShader.Use();
    ourShader.setMat4("projection", P);
    ourShader.setMat4("view", V);
    GL_CHECK_ERRORS;
    
    for(int i = 0 ; i< 3 ; i++)
    {
        
        auto transforms = animator[i]->GetFinalBoneMatrices();
        for (int i = 0; i < transforms.size(); ++i)
            ourShader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
        
        animator[i]->UpdateAnimation(dt);
        ourShader.setMat4("model", ourModel[i]->model);
        ourModel[i]->Draw(ourShader);
    }
    ourShader.UnUse();
    
    // Camera movement
    if(Input::GetInstance().IsKeyDown(GLFW_KEY_W))
    {
        mainCamera->Walk(1.0f);
    }
    if(Input::GetInstance().IsKeyDown(GLFW_KEY_S))
    {
        mainCamera->Walk(-1.0f);
    }
    if(Input::GetInstance().IsKeyDown(GLFW_KEY_A))
    {
        mainCamera->Strafe(-1.0f);
    }
    if(Input::GetInstance().IsKeyDown(GLFW_KEY_D))
    {
        mainCamera->Strafe(1.0f);
    }
}

