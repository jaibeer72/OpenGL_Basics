//
//  main.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 31/10/2022.
//

#include "Application.hpp"

#include "Triangle.hpp"
#include "Plane.hpp"
#include "UnitCube.hpp"
#include "Skybox.hpp"

#include "appCongif.h"


int main(int argc, const char * argv[])
{
    const char* appname = "trial name";

    Application* app = new Application(appname,AppConfig::Width,AppConfig::Height);
    
    app->init();
    
    std::map<std::string,std::unique_ptr<IRenderableObject>> *renderableObjectsMap = new std::map<std::string, std::unique_ptr<IRenderableObject>>();
    
    
    //renderableObjectsMap->insert({"triangle", std::unique_ptr<IRenderableObject>(new Triangle())});
    //renderableObjectsMap->insert({"textured Plane", std::unique_ptr<IRenderableObject>(new CTexturedPlane(500,500))});
    //renderableObjectsMap->insert({"SkyBox", std::unique_ptr<IRenderableObject>(new Skybox("/Users/jaibeerdugal/Documents/simpleCpp/SimpleerCpp/HelloOpenGl/OpenGl_Basics/OpenGL_Basics/OpenGL_Basics/assets/Skybox/leanOpenGLSkyBox/l"))});
    //renderableObjectsMap->insert({"cube", std::unique_ptr<IRenderableObject>(new UnitCube())});
    
    
    try {
        app->SetRenderPool(*renderableObjectsMap);
        app->run();
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    

    return EXIT_SUCCESS;
    
}


