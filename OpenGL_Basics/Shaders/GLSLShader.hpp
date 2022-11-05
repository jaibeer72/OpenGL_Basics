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

// file systems
#include<fstream>
#include<algorithm>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    void AddAttribute(const std::string& attribute);
    void AddUniform(const std::string& uniform);
    GLuint operator[](const std::string& attribute);
    GLuint operator()(const std::string& uniform);
    void DeleteShaderProgram();

private:
    enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER };
    GLuint  m_Program;
    int _totalShaders;
    GLuint _shaders[3];
    std::map<std::string, GLuint> _attributeList;
    std::map<std::string, GLuint> _uniformLocationList;
};
#endif

