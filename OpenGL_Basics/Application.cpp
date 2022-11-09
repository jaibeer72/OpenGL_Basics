//
//  Application.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 03/11/2022.
//

#include "Application.hpp"


Application::Application(const char *AppName, int Width, int Height): width(Width), height(Height)
{
}

void Application::run() {
    
    auto begin = RenderPool->begin();
    auto end = RenderPool->end();
    for (auto iter = begin; iter != end ; ++iter )
    {
        iter->second->Init();
        std::cout<< "Initalized----" << iter->first << std::endl;
    }
    
    // reder loop
    while(!glfwWindowShouldClose(m_Window))
    {
        OnKeyCallback(0);
        
        glm::mat4 MV    = MainCamera.GetViewMatrix();
        glm::mat4 P     = MainCamera.GetProjectionMatrix();
        glm::mat4 MVP    = P*MV;
        

        //clear color buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f,1.0f,1.0f,1.0f);
        
        for (auto iter = begin; iter != end ; ++iter )
        {
            iter->second->Render(glm::value_ptr(MVP));
        }
        
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

// This has to always be static hence it works
void Application::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
   
    //set the viewport
    glViewport (0, 0, (GLsizei) width, (GLsizei) height);
    
    //setup the camera projection matrix
    MainCamera.SetupProjection(45, (GLfloat)width/height);
    
}

void Application::OnKeyCallback(int keycode) {
    
    if(glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, true);
}

void Application::SetRenderPool(std::map<std::string, std::unique_ptr<IRenderableObject>> &renderPool)
{
    auto begin = renderPool.begin();
    auto end = renderPool.end();
    for (auto iter = begin; iter != end ; ++iter )
    {
        std::cout<< iter->first;
        
        RenderPool->insert({iter->first, std::unique_ptr<IRenderableObject>(iter->second->ReturnRenderObject())
        });
    }
    
}

void Application::init() {
    //setup camera
    //setup the camera position and look direction
    
    glm::vec3 p = glm::vec3(5);
    MainCamera.SetPosition(p);
    glm::vec3 look =  glm::normalize(p);
    
    //rotate the camera for proper orientation
    float yaw = glm::degrees(float(atan2(look.z, look.x)+M_PI));
    float pitch = glm::degrees(asin(look.y));
    MainCamera.Rotate(yaw, pitch, 0);
    
    initWindow(width, height);
}





