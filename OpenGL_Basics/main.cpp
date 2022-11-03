//
//  main.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 31/10/2022.
//

#include "Application.hpp"


int main(int argc, const char * argv[])
{
    std::map<std::string,IRenderableObject> *renderableObjectsMap = new std::map<std::string, IRenderableObject>();
    
    const char* appname = "trial name";
    Application* app = new Application(appname,300,300, *renderableObjectsMap);
    try {
        app->run();
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    

    return EXIT_SUCCESS;
    
}


