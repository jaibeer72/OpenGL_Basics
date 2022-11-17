//
//  Time.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 17/11/2022.
//

#include "Time.hpp"

double  Time::GetDeltaTime() {
    currentFrame = glfwGetTime();
    deltatime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    return deltatime;
}

std::tm* Time::GetCurrentTime() {
    time_t now = time(0);
    auto timeinfo = localtime (&now);
    return timeinfo;
}

Time::Time() {
    time(&rawtime);
}


