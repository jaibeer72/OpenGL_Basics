//
//  FinalSubmissionBaseScene.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 11/12/2022.
//

#ifndef FinalSubmissionBaseScene_hpp
#define FinalSubmissionBaseScene_hpp

#include "FreeCamera.hpp"
#include "Model.hpp"
#include "Animator.hpp"
#include "FreeCamera.hpp"

// input system
#include "Input.hpp"
#include "RenderableObjectsBase.hpp"

// Object to render
#include "Skybox.hpp"
#include "LitPlane.hpp"
#include "Lit_UnitCube.hpp"

class FinalSubmissionBase
{
public:
    void Init();
    void update(float dt,CFreeCamera* mainCamera);
    
    Skybox* m_skybox;
    Skybox* m_indoor;
    GLSLShader ourShader;
    Animation* danceAnimation[3];
    Animator* animator[3];
    Model* ourModel[3];
    LitTexPlane* plane;
    LitTexPlane* plane2;
    Lit_UnitCube* cube;
};

#endif /* FinalSubmissionBaseScene_hpp */
