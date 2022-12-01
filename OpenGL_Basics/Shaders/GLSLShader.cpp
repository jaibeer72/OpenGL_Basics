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

void GLSLShader::LoadFromString(GLenum type, const std::string &source) {
    GLuint shader = glCreateShader(type);

    const char * ptmp = source.c_str();
    
    glShaderSource(shader,1,&ptmp,NULL); 
        
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
    GL_CHECK_ERRORS;
}

void GLSLShader::LoadFromFile(GLenum type, const std::string &filename) {
    std::ifstream fp;
    
    
    fp.open(filename.c_str(), std::ios_base::in);
    if (fp) {
        std::string line, buffer;
        while (getline(fp, line)) {
            buffer.append(line);
            buffer.append("\r\n");
        }
        //copy to source
        LoadFromString(type, buffer);
    }
    else {
        std::cerr << "Error loading shader: " << filename << std::endl;
    }
    GL_CHECK_ERRORS;
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
    GL_CHECK_ERRORS;

    glDeleteShader(_shaders[VERTEX_SHADER]);
    glDeleteShader(_shaders[FRAGMENT_SHADER]);
    glDeleteShader(_shaders[GEOMETRY_SHADER]);
    GL_CHECK_ERRORS;
}

void GLSLShader::Use() {
    GL_CHECK_ERRORS;
    glUseProgram(m_Program);
}

void GLSLShader::UnUse() { 
    glUseProgram(0);
    //PrintGLerror();
    GL_CHECK_ERRORS;
}

void GLSLShader::AddAttribute(const std::string &attribute, GLuint location) {
    glBindAttribLocation(m_Program, location , attribute.c_str());
    _attributeList[attribute] = location; 
}

void GLSLShader::AddUniform(const std::string &uniform) { 
    _uniformLocationList[uniform] = glGetUniformLocation(m_Program, uniform.c_str());
    GL_CHECK_ERRORS;
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

void GLSLShader::PrintGLerror() { 

        GLenum err = glGetError();
        
        switch (err) {
            case GL_STACK_OVERFLOW:
                std::cout<< "overflow";
                throw std::runtime_error("Problem");
                break;
            case GL_INVALID_ENUM:
                std::cout<< "invalidenum";
                throw std::runtime_error("Problem");
                break;
            case GL_INVALID_VALUE:
                std::cout<< "invalid value";
                throw std::runtime_error("Problem");
                break;
            case GL_INVALID_OPERATION:
                std::cout<< "Invalid operation";
                throw std::runtime_error("Problem");
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                std::cout<< "Framebuff fail";
                throw std::runtime_error("Problem");
                break;
            case GL_OUT_OF_MEMORY:
                std::cout<< "out of mem";
                throw std::runtime_error("Problem");
                break;
            case GL_STACK_UNDERFLOW:
                std::cout<< "underflow";
                throw std::runtime_error("Problem");
                break;
            default:
                break;
        
           
    }
}












