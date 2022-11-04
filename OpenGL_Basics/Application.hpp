//
//  Application.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 03/11/2022.
//

#ifndef Application_hpp
#define Application_hpp

#include "RenderableObjectsBase.hpp"

class Application {
    
    GLFWwindow* m_Window;
    void initWindow(int width,int height);
    void cleanup();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    std::map<std::string,std::unique_ptr<IRenderableObject>> *RenderPool = new std::map<std::string, std::unique_ptr<IRenderableObject>>();
    
public:
    const char* appName = "Application Name";
    unsigned int width;
    unsigned int height;
    void OnKeyCallback(int keycode);
    
    Application(const char* AppName, int Width, int Height);
    
    void SetRenderPool(std::map<std::string,std::unique_ptr<IRenderableObject>> &renderPool);
 
    void run();
    
};

#endif /* Application_hpp */
