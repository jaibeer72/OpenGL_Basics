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
    GLuint m_Program;
    // utility uniform functions
       // ------------------------------------------------------------------------
       void setBool(const std::string &name, bool value) const
       {
           glUniform1i(glGetUniformLocation(m_Program, name.c_str()), (int)value);
       }
       // ------------------------------------------------------------------------
       void setInt(const std::string &name, int value) const
       {
           glUniform1i(glGetUniformLocation(m_Program, name.c_str()), value);
       }
       // ------------------------------------------------------------------------
       void setFloat(const std::string &name, float value) const
       {
           glUniform1f(glGetUniformLocation(m_Program, name.c_str()), value);
       }
       // ------------------------------------------------------------------------
       void setVec2(const std::string &name, const glm::vec2 &value) const
       {
           glUniform2fv(glGetUniformLocation(m_Program, name.c_str()), 1, &value[0]);
       }
       void setVec2(const std::string &name, float x, float y) const
       {
           glUniform2f(glGetUniformLocation(m_Program, name.c_str()), x, y);
       }
       // ------------------------------------------------------------------------
       void setVec3(const std::string &name, const glm::vec3 &value) const
       {
           glUniform3fv(glGetUniformLocation(m_Program, name.c_str()), 1, &value[0]);
       }
       void setVec3(const std::string &name, float x, float y, float z) const
       {
           glUniform3f(glGetUniformLocation(m_Program, name.c_str()), x, y, z);
       }
       // ------------------------------------------------------------------------
       void setVec4(const std::string &name, const glm::vec4 &value) const
       {
           glUniform4fv(glGetUniformLocation(m_Program, name.c_str()), 1, &value[0]);
       }
       void setVec4(const std::string &name, float x, float y, float z, float w) const
       {
           glUniform4f(glGetUniformLocation(m_Program, name.c_str()), x, y, z, w);
       }
       // ------------------------------------------------------------------------
       void setMat2(const std::string &name, const glm::mat2 &mat) const
       {
           glUniformMatrix2fv(glGetUniformLocation(m_Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
       }
       // ------------------------------------------------------------------------
       void setMat3(const std::string &name, const glm::mat3 &mat) const
       {
           glUniformMatrix3fv(glGetUniformLocation(m_Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
       }
       // ------------------------------------------------------------------------
       void setMat4(const std::string &name, const glm::mat4 &mat) const
       {
           glUniformMatrix4fv(glGetUniformLocation(m_Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
       }


private:
    enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER };
    int _totalShaders;
    GLuint _shaders[3];
    std::map<std::string, GLuint> _attributeList;
    std::map<std::string, GLuint> _uniformLocationList;
};

#endif

