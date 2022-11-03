//
//  Application.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 31/10/2022.
//

#include "Application.hpp"

Application::Application(const char *AppName, int Width, int Height, std::map<std::string, std::unique_ptr<IRenderableObject>> &RenderableObjects) {
    m_RenderableObjects(*RenderableObjects);
    appName = AppName;
    width = Width;
    height = Height;
}


void framebuffer_size_callback1(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


void Application::run() {
    initWindow(width, height);
    // reder loop
    while(!glfwWindowShouldClose(m_Window))
    {
        OnKeyCallback(0);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
    cleanup();
}


void Application::initWindow(int width, int height) {
    if(!glfwInit())
    {
        std::cout<< "Failed to init GLFW";
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    m_Window = glfwCreateWindow(width, height, appName, NULL, NULL);
    if (m_Window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        
        throw std::runtime_error("GLFW init failed");
    }
    glfwMakeContextCurrent(m_Window);
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw std::runtime_error("Glad failed to load");
    }
}



void Application::cleanup() {
    glfwTerminate();
}

void Application::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Application::OnKeyCallback(int keycode) {
    
    if(glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, true);
}










