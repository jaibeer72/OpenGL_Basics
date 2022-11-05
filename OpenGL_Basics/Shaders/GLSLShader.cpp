//
//  GLSLShader.cpp
//  OpenGL_Basics
//
//  Created by Jaibeer Dugal on 02/11/2022.
//

#include "GLSLShader.hpp"

GLSLShader::GLSLShader() { 
    _totalShaders = 0;
    _shaders[VERTEX_SHADER] = 0;
    _shaders[FRAGMENT_SHADER] = 0;
    _shaders[GEOMETRY_SHADER] = 0;
    _attributeList.clear();
    _uniformLocationList.clear();
}

void GLSLShader::LoadFromString(GLenum whichShader, const std::string &source) { 
    _attributeList.clear();
    _uniformLocationList.clear();
}

void GLSLShader::LoadFromFile(GLenum type, const std::string &source) {
    GLuint shader = glCreateShader(type);

    const char * ptmp = source.c_str();
        

    //check whether the shader loads fine
    GLint status;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog = new GLchar[infoLogLength];
        glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
        std::cout << "Compile log: " << infoLog << std::endl;
        delete[] infoLog;
    }
    _shaders[_totalShaders++] = shader;
}

void GLSLShader::CreateAndLinkProgram() { 
    m_Program = glCreateProgram();
    if (_shaders[VERTEX_SHADER] != 0) {
        glAttachShader(m_Program, _shaders[VERTEX_SHADER]);
    }
    if (_shaders[FRAGMENT_SHADER] != 0) {
        glAttachShader(m_Program, _shaders[FRAGMENT_SHADER]);
    }
    if (_shaders[GEOMETRY_SHADER] != 0) {
        glAttachShader(m_Program, _shaders[GEOMETRY_SHADER]);
    }

    //link and check whether the program links fine
    GLint status;
    glLinkProgram(m_Program);
    glGetProgramiv(m_Program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;

        glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog = new GLchar[infoLogLength];
        glGetProgramInfoLog(m_Program, infoLogLength, NULL, infoLog);
        std::cerr << "Link log: " << infoLog << std::endl;
        delete[] infoLog;
    }

    glDeleteShader(_shaders[VERTEX_SHADER]);
    glDeleteShader(_shaders[FRAGMENT_SHADER]);
    glDeleteShader(_shaders[GEOMETRY_SHADER]);
}

void GLSLShader::Use() { 
    glUseProgram(m_Program);
}

void GLSLShader::UnUse() { 
    glUseProgram(0);
}

void GLSLShader::AddAttribute(const std::string &attribute) { 
    _attributeList[attribute] = glGetAttribLocation(m_Program, attribute.c_str());
}

void GLSLShader::AddUniform(const std::string &uniform) { 
    _uniformLocationList[uniform] = glGetUniformLocation(m_Program, uniform.c_str());
}

GLuint GLSLShader::operator[](const std::string &attribute) { 
    return _attributeList[attribute];
}

GLuint GLSLShader::operator()(const std::string &uniform) { 
    return _uniformLocationList[uniform];
}

void GLSLShader::DeleteShaderProgram() { 
    glDeleteProgram(m_Program);
}

GLSLShader::~GLSLShader() { 

}











