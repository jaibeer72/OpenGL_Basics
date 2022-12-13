//
//  ShadowPassFinalSubmission.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 11/12/2022.
//

#ifndef ShadowPassFinalSubmission_hpp
#define ShadowPassFinalSubmission_hpp

#include "GLSLShader.hpp"
#include "FinalSubmissionBaseScene.hpp"


class ShadowPassInScene : public FinalSubmissionBase
{
public:
    void Init();
    void update(float dt,CFreeCamera* mainCam);
    GLSLShader m_shadowpassShader;
    glm::vec3 lightPos;
protected:
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMapFBO;
    
    void renderScene(GLSLShader &shader,CFreeCamera* mainCam);
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
};

#endif /* ShadowPassFinalSubmission_hpp */
