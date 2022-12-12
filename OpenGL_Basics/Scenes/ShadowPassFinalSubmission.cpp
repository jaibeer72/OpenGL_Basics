//
//  ShadowPassFinalSubmission.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 11/12/2022.
//

#include "ShadowPassFinalSubmission.hpp"
#include "appCongif.h"


void ShadowPassInScene::Init() {
    
    lightPos = glm::vec3(0,1,0);
    m_shadowpassShader.LoadFromFile(GL_VERTEX_SHADER, "/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/Shaders/ShadowMapping/shadowMapping.vert");
    m_shadowpassShader.LoadFromFile(GL_FRAGMENT_SHADER, "/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/Shaders/ShadowMapping/shadowMapping.frag");
    m_shadowpassShader.CreateAndLinkProgram();
    m_shadowpassShader.Use();
    m_shadowpassShader.AddAttribute("vVertex",0);
    m_shadowpassShader.AddUniform("VP");
    m_shadowpassShader.AddUniform("vModel");
    m_shadowpassShader.AddUniform("viewPos");
    m_shadowpassShader.UnUse();
    
    
     glGenFramebuffers(1, &depthMapFBO);
     glGenTextures(1, &ILitObject::depthMap);
     glBindTexture(GL_TEXTURE_2D, ILitObject::depthMap);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
     float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
     glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
     // attach depth texture as FBO's depth buffer
     glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ILitObject::depthMap, 0);
     glDrawBuffer(GL_NONE);
     glReadBuffer(GL_NONE);
     glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    FinalSubmissionBase::Init();
}

void ShadowPassInScene::update(float dt ,CFreeCamera* mainCam) {
    
    // change light position over time
//     lightPos.x = sin(glfwGetTime()) * 3.0f;
//     lightPos.z = cos(glfwGetTime()) * 2.0f;
//     lightPos.y = 5.0 + cos(dt) * 1.0f;
    // 1. render depth of scene to texture (from light's perspective)
            // --------------------------------------------------------------

            float near_plane = 1.0f, far_plane = 7.0f;
            //lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
            lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
            lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
            lightSpaceMatrix = lightProjection * lightView;
            // render scene from light's point of view
            m_shadowpassShader.Use();
            m_shadowpassShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

            glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
            glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
                glClear(GL_DEPTH_BUFFER_BIT);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, plane->checkerTextureID);
                renderScene(m_shadowpassShader,mainCam);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
    m_shadowpassShader.UnUse();
    
//    // reset viewport
    // TODO: Bug this for some reason requires me to double the width and height of the VP this is wierd.
     glViewport(0, 0, AppConfig::Width*2, AppConfig::Height*2);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    
    FinalSubmissionBase::update(dt, mainCam);
}

void ShadowPassInScene::renderScene(GLSLShader &shader,CFreeCamera* mainCam) {
    
    glCullFace(GL_FRONT);
    if(Input::IsKeyDown(GLFW_KEY_LEFT))
    {
        lightPos.x-=0.1;
        std::cout<<"x"<<lightPos.x <<"\n";
    }
    if(Input::IsKeyDown(GLFW_KEY_RIGHT))
    {
        lightPos.x+=0.1;
        std::cout<<"x"<<lightPos.x <<"\n";
    }
    if(Input::IsKeyDown(GLFW_KEY_UP))
    {
        lightPos.y+=0.1;
        std::cout<<"y"<<lightPos.y <<"\n";
    }
    if(Input::IsKeyDown(GLFW_KEY_DOWN))
    {
        lightPos.y-=0.1;
        std::cout<<"y"<<lightPos.y <<"\n";
    }
    if(Input::IsKeyDown(GLFW_KEY_Q))
    {
        lightPos.z-=0.1;
        std::cout<<"z"<<lightPos.y <<"\n";
    }
    if(Input::IsKeyDown(GLFW_KEY_E))
    {
        lightPos.z+=0.1;
        std::cout<<"z"<<lightPos.y <<"\n";
    }
    
    glm::mat4 cV    = mainCam->GetViewMatrix();
    glm::mat4 cP     = mainCam->GetProjectionMatrix();
    glm::mat4 cVP    = cP*cV;
    

    GLSLShader temp;
    
    // Model shadow
    temp = ourShader;
    ourShader = m_shadowpassShader;
    ourShader.Use();
    for(int i = 0 ; i < 3 ; i++)
    {
        ourShader.setMat4("vModel", ourModel[i]->model);
        ourModel[i]->Draw(m_shadowpassShader);
    }
    ourShader.UnUse();
    ourShader = temp;
    
    // set light uniforms
    ourShader.Use();
    ourShader.setVec3("viewPos", mainCam->GetPosition());
    ourShader.setVec3("lightPos", lightPos);
    ourShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
    ourShader.UnUse();
    
    temp = plane->shader;
    plane->shader = m_shadowpassShader;
    plane->Render(glm::value_ptr(cVP),mainCam->GetPosition());
    plane->shader = temp;
    
    // applying shadow stuff to plane texture for next render
    plane->shader.Use();
    plane->shader.setVec3("lightPos", lightPos);
    plane->shader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
    plane->shader.UnUse();
    GL_CHECK_ERRORS;
    
    temp = plane2->shader;
    plane2->shader = m_shadowpassShader;
    plane2->Render(glm::value_ptr(cVP),mainCam->GetPosition());
    plane2->shader = temp;
    
    // applying shadow stuff to plane texture for next render
    plane2->shader.Use();
    plane2->shader.setVec3("lightPos", lightPos);
    plane2->shader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
    plane2->shader.UnUse();

    glCullFace(GL_BACK);
}


