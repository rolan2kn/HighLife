//
// Created by rkindela on 01-10-19.
//


#include "shader_controller.h"
//#include <GL/glew.h>
#include <exception>
using namespace std;

#include <cstring>
#include "util.hpp"
#include <fstream>
#include <sstream>


/**
 * constructor de Shader
 * */

Shader::Shader(SHADER_TYPE sType, const GLchar* src)
{

    size_t len = strlen(src);
    this->src = new char[len+1];
    this->src[len] = '\0';
    strncpy(this->src, src, len);

    this->setType(string(src));
    this->create();

    string prefix;
    string extension = this->getTypeNameAndExtension(prefix);

    string name = generar_nombre_archivo(directorio_actual() + "/shader_files/", prefix);
    this->toFile(name+extension);
}

/**
 * destructor de Shader
 * */

Shader::~Shader()
{
    this->src = nullptr;
    glDeleteShader(this->id);
}

/**
 * Shader::create()
 * crea el shader y lo compila
 * */
GLuint Shader::create()
{
    this->id = glCreateShader(this->type);
    glShaderSource(this->id, 1, &this->src, nullptr);
    glCompileShader(this->id);
    string strType = "";
    this->getTypeNameAndExtension(strType);
    checkCompileErrors(this->id, strType);
}

void Shader::setType(Shader::SHADER_TYPE sType)
{
    switch (sType)
    {
        case VERTEX:
            this->type = GL_VERTEX_SHADER;
            break;
        case FRAGMENT:
            this->type = GL_FRAGMENT_SHADER;
            break;
        case GEOMETRY:
            this->type = GL_GEOMETRY_SHADER;
            break;
    }
}

void Shader::setType(GLuint _type)
{
    this->type = _type;
}

void Shader::setType(const string& _type)
{
    if(_type.find(".vs") != -1)
        this->type = GL_VERTEX_SHADER;
    else if(_type.find(".fs") != -1)
        this->type = GL_FRAGMENT_SHADER;
    else
        this->type = GL_GEOMETRY_SHADER;
}

/**
 * Shader::fromFile(SHADER_TYPE sType, const string& filename)
 * carga el shader de un fichero
 * */
void Shader::fromFile(const string& filename)
{
    if(!existe_archivo(filename))
        throw NewException("Se esperaba un archivo");

    ifstream shaderfile(filename, ios::in);
    if(shaderfile.is_open())
    {
        std::stringstream shaderStream;
        shaderStream << shaderfile.rdbuf();
        string p = shaderStream.str();

        size_t len = p.length();
        this->src = new char[len+1];
        this->src[len] = '\0';
        strncpy(this->src, p.c_str(), len);

        this->setType(filename);

        this->create();
    }
    shaderfile.close();

}

/**
 * Shader::toFile(const string& filename)
 * guarda el shader en un fichero
 * */
void Shader::toFile(const string& filename)
{
    std::string basen = basename(filename);
    std::string path = directorio_actual() + "/shader_files/";
    std::string ext = ".vsh";
    if(this->type == GL_FRAGMENT_SHADER)
        ext = ".fsh";
    else if(this->type == GL_GEOMETRY_SHADER)
        ext = ".gsh";

    ofstream shaderfile(path + basen + ext, ios::out);
    if(shaderfile.is_open())
    {
        size_t len = strlen(this->src);

        shaderfile.write( (char *) this->src, sizeof(char)*len );
        shaderfile.close();
    }
}

string Shader::getTypeNameAndExtension(string& typeName)
{
    switch (this->type)
    {
        case GL_VERTEX_SHADER:
            typeName = "VERTEX";
            return ".vsh";
        case GL_GEOMETRY_SHADER:
            typeName = "GEOMETRY";
            return ".gsh";
        case GL_FRAGMENT_SHADER:
            typeName = "FRAGMENT";
            return ".fsh";
    }
}

