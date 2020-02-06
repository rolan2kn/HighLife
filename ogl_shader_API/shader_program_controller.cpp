//
// Created by rkindela on 02-10-19.
//

#include "shader_program_controller.h"
#include "util.hpp"


/**
 * constructor de ShaderProgram
 * */
ShaderProgramController::ShaderProgramController() : shaderList()
{
    this->programId = glCreateProgram();
}

/**
 * Destructor de ShaderProgram
 * */
ShaderProgramController::~ShaderProgramController()
{
    glDeleteProgram(this->programId);
}

/**
 * ShaderProgramController::getId()
 *
 * retorna el programID
 *
 * */
GLuint ShaderProgramController::getId() const
{
    return this->programId;
}

/**
 * ShaderProgramController::addShader(Shader::SHADER_TYPE shaderType, const GLchar* src)
 * añade un shader al programa y lo configura
 * */
void ShaderProgramController::addShader(Shader::SHADER_TYPE shaderType, const GLchar* src)
{
    this->shaderList.push_back(new Shader(shaderType, src));
}
void ShaderProgramController::addShaderFromFile(const string& filename)
{
    Shader* sh = new Shader();
    sh->fromFile(filename);
    this->shaderList.push_back(sh);
}

/**
 * ShaderProgramController::configure()
 * prepara los shaders agregados y lo deja listos para ejecutar
 * */
void ShaderProgramController::configure()
{
    for(Shader* sh: shaderList)
    {
        glAttachShader(this->programId, sh->getId());
    }

    glLinkProgram(this->programId);
    checkCompileErrors(this->programId, "PROGRAM");
    glUseProgram(this->programId);
    checkCompileErrors(this->programId, "PROGRAM");
}

/**
 * Shader::setBool(const std::string &name, bool value) const
 * modifica la variable name
 * */
void ShaderProgramController::setBool(const std::string &name, bool value) const
{
    glUniform1i(this->getUniformPosition(name.c_str()), (int)value);
}

void ShaderProgramController::setInt(const std::string &name, int value) const
{
    glUniform1i(this->getUniformPosition(name.c_str()), value);
}

void ShaderProgramController::setFloat(const std::string &name, float value) const
{
    glUniform1f(this->getUniformPosition(name.c_str()), value);
}

void ShaderProgramController::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(this->getUniformPosition(name.c_str()), 1, &value[0]);
}

void ShaderProgramController::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(this->getUniformPosition(name.c_str()), x, y);
}

void ShaderProgramController::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(this->getUniformPosition(name.c_str()), 1, &value[0]);
}

void ShaderProgramController::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(this->getUniformPosition(name.c_str()), x, y, z);
}

void ShaderProgramController::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(this->getUniformPosition(name.c_str()), 1, &value[0]);
}

void ShaderProgramController::setVec4(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(this->getUniformPosition(name.c_str()), x, y, z, w);
}

void ShaderProgramController::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(this->getUniformPosition(name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgramController::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(this->getUniformPosition(name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgramController::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(this->getUniformPosition(name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

/**
 * ShaderProgramController::getUniformPosition(const std::string &name) const
 * retorna la posicion global del parametro
 * */
GLuint ShaderProgramController::getUniformPosition(const std::string &name) const
{
    return glGetUniformLocation(this->programId, name.c_str());
}
