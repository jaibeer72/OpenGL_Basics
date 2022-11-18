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
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    Time t;
    // reder loop
    while(!glfwWindowShouldClose(m_Window))
    {
        t.GetDeltaTime();
        
        glm::mat4 V    = MainCamera.GetViewMatrix();
        glm::mat4 P     = MainCamera.GetProjectionMatrix();
        glm::mat4 VP    = P*V;
        

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        for (auto iter = begin; iter != end ; ++iter )
        {
            iter->second->Render(glm::value_ptr(VP));
        }
        
        clockScene->Update(glm::value_ptr(VP),MainCamera.GetPosition());
        
        MainCamera.Rotate(Input::GetInstance().GetmousePos().x, Input::GetInstance().GetmousePos().y,0);
        
        //std::cout<<"x :" << MainCamera.GetRotation().x<< "y : "<<MainCamera.GetRotation().y << "z : "<<MainCamera.GetRotation().z << std::endl;
        
        if(Input::GetInstance().IsKeyDown(GLFW_KEY_W))
        {
            MainCamera.Walk(1.0f);
        }
        
        if(Input::GetInstance().IsKeyDown(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(m_Window, true);
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
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
    Input::GetInstance().setKeyCallback(m_Window);
    Input::GetInstance().setMouseCallback(m_Window);
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw std::runtime_error("Glad failed to load");
    }
    
    std::cout<<"\n" <<glGetString(GL_VERSION);
    // configure global opengl state
     // -----------------------------
     glEnable(GL_DEPTH_TEST);
}



void Application::cleanup() {
    glfwTerminate();
}

// This has to always be static hence it works
void Application::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
   
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //setup the camera projection matrix
    MainCamera.SetupProjection(45, (GLfloat)width/height);
    
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
    
    glm::vec3 p = glm::vec3(1);
    MainCamera.SetPosition(p);
    
    
    initWindow(width, height);
    
    //rotate the camera for proper orientation
    MainCamera.Rotate(0.0f, 0.0f, 0.0f);
    
    //setup the camera projection matrix
    MainCamera.SetupProjection(45, (GLfloat)width/height);
    
    clockScene = new ClockScene();
    clockScene->Initialize();
    
}
