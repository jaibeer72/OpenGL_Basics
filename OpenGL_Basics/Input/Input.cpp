//
//  Input.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 10/11/2022.
//

#include "Input.hpp"


Input::Input() {
 
    
}

void Input::setKeyCallback(GLFWwindow *winddow) {
    glfwSetKeyCallback(winddow, Input::processInput);
}

void Input::processInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
    setKeyIsDown(key, action != GLFW_RELEASE);
}

void Input::setKeyIsDown(int key, bool isDown) { 
    
    auto it = keyMapList.find(key);
    if(it != keyMapList.end())
    {
        keyMapList[key] = isDown;
    }
}

bool Input::IsKeyDown(int key) {
    bool result = false;
    
    auto it = keyMapList.find(key);
    if(it != keyMapList.end())
    {
        result= keyMapList[key];
    }
    
    return result;
}

void Input::setMouseCallback(GLFWwindow *window) { 
    glfwSetCursorPosCallback(window, mouse_callback);
}

void Input::SetMousePos(double xoffset, double yoffset) {
    
    Mouse_XPos = static_cast<float>(-xoffset);
    Mouse_YPos = static_cast<float>(yoffset);
}

void Input::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    SetMousePos(xpos, ypos);
}

glm::vec2 Input::GetmousePos() {
    return  glm::vec2(Mouse_XPos * 0.5f,Mouse_YPos * 0.5f);
}









