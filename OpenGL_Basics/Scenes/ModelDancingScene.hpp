//
//  ModelDancingScene.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 30/11/2022.
//

#ifndef ModelDancingScene_hpp
#define ModelDancingScene_hpp

#include "Model.hpp"
#include "Animator.hpp"

class ModelDancingScene
{
public:
    ModelDancingScene();
    void Initialize();
    void Update(const float* VP,glm::vec3 camPos);
    void Destroy();

private:
    void RenderObjects(const float *VP, const glm::vec3 &camPos);
    Model* DancingModel;
    Animation* DancingAnimation;
    Animator* DancingAnimator;
};

#endif /* ModelDancingScene_hpp */
