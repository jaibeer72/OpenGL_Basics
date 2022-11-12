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
#include <glm/glm.hpp>

class Input
{
public:
    // Keyboard check
    static bool IsKeyDown(int key);
    static void setKeyCallback(GLFWwindow* window);
    // Check move scroll
    static void setMouseCallback(GLFWwindow* window);
    static glm::vec2 GetmousePos();
    
    static Input GetInstance(){
        return m_Input;
    }
protected:
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    //static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void processInput(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
    static void setKeyIsDown(int key , bool isDown);
    inline static std::map<int, bool> keyMapList = {
        {GLFW_KEY_W,false},
        {GLFW_KEY_A, false},
        {GLFW_KEY_S, false},
        {GLFW_KEY_D, false},
        {GLFW_KEY_Q, false},
        {GLFW_KEY_E,false},
        {GLFW_KEY_ESCAPE,false}
    };
    // Mouse Movement
    static void SetMousePos(double xoffset, double yoffset);
    inline static float Mouse_XPos ,Mouse_YPos ;
    Input();
    static Input m_Input;
};

#endif /* Input_hpp */
