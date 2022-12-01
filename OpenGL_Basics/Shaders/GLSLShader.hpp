//
//  GLSLShader.hpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 02/11/2022.
//

#pragma once
#ifndef GLSLSHADER_H
#define GLSLSHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <map>
#include <string>
#include <iterator>
#include <vector>

// file systems
#include<fstream>
#include<algorithm>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GL_CHECK_ERRORS assert(glGetError()== GL_NO_ERROR);


class GLSLShader
{
public:
    GLSLShader();
    ~GLSLShader();
    void LoadFromString(GLenum ShaderType, const std::string& source);
    void LoadFromFile(GLenum ShaderType, const std::string& filename);
    void CreateAndLinkProgram();
    void Use();
    void UnUse();
    void AddAttribute(const std::string& attribute, GLuint location);
    void AddUniform(const std::string& uniform);
    GLuint operator[](const std::string& attribute);
    GLuint operator()(const std::string& uniform);
    void DeleteShaderProgram();
    void PrintGLerror();
    GLuint  m_Program;

private:
    enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER };
    int _totalShaders;
    GLuint _shaders[3];
    std::map<std::string, GLuint> _attributeList;
    std::map<std::string, GLuint> _uniformLocationList;
};

#endif

