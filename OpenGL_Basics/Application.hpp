//
//  Application.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 31/10/2022.
//

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream> 
#include <stdexcept>
#include <map>
#include <string>

#include "RenderableObjctsBase/RenderableObjectsBase.hpp"


class Application {
    
    GLFWwindow* m_Window;
    void initWindow(int width,int height);
    void cleanup();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    
    std::map<std::string , IRenderableObject> m_RenderableObjects;
    
public:
    const char* appName = "Application Name";
    unsigned int width;
    unsigned int height;
    void OnKeyCallback(int keycode);
    Application(const char *AppName, int Width, int Height, std::map<std::string, IRenderableObject> &RenderableObjects);
    
    void run();
    
    
};

