//
//  Input.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 10/11/2022.
//

#pragma once
#ifndef Input_hpp
#define Input_hpp

#include <GLFW/glfw3.h>
#include <map>

class Input
{
public:
    static bool IsKeyDown(int key);
    static void setKeyCallback(GLFWwindow* winddow);
protected:
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void processInput(GLFWwindow *window);
private:
    static void setKeyIsDown(int key , bool isDown);
    static std::map<int, bool> keyMapList;
    Input();
};

#endif /* Input_hpp */
