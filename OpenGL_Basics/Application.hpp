//
//  Application.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 03/11/2022.
//

#pragma once
#ifndef Application_hpp
#define Application_hpp

#include "FreeCamera.hpp"
#include "RenderableObjectsBase.hpp"

// input system
#include "Input.hpp"
#include "ClockScene.hpp"
#include "Model.hpp"

#include "Animator.hpp"

class Application {
    
    GLFWwindow* m_Window;
    void initWindow(int width,int height);
    void cleanup();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    std::map<std::string,std::unique_ptr<IRenderableObject>> *RenderPool = new std::map<std::string, std::unique_ptr<IRenderableObject>>();
    
public:
    const char* appName = "Application Name";
    int width;
    int height;
    inline static CFreeCamera MainCamera;
    
    Application(const char* AppName, int Width, int Height);
    
    void SetRenderPool(std::map<std::string,std::unique_ptr<IRenderableObject>> &renderPool);
    
    void init();
    void run();
    
    ClockScene* clockScene;
    
    GLSLShader ourShader;
    Animation* danceAnimation;
    Animator* animator;
    Model* ourModel;
    
};

#endif /* Application_hpp */
