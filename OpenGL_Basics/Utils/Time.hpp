//
//  Time.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 17/11/2022.
//

#ifndef Time_hpp
#define Time_hpp

#include <time.h>
#include <GLFW/glfw3.h>
#include <iostream>


class Time
{
public:
    Time(); 
    static double GetDeltaTime();
    std::tm* GetCurrentTime();
private:
    inline static double currentFrame =0 , lastFrame =0;
    inline static double deltatime =0 ;
    time_t rawtime;
};


#endif /* Time_hpp */
