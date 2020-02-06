//
// Created by rkindela on 01-10-19.
//

#ifndef PAIRWISEDISTANCEOPENGLSHADERS_SHADER_CONTROLLER_H
#define PAIRWISEDISTANCEOPENGLSHADERS_SHADER_CONTROLLER_H

#include <glad/glad.h>

#include <vector>
#include <iostream>
using namespace std;

class Shader
{
public:
    enum SHADER_TYPE {VERTEX, FRAGMENT, GEOMETRY};
private:
    GLenum type;
    GLuint id;
    GLchar* src;
protected:

public:
    Shader(){}
    Shader(SHADER_TYPE sType, const GLchar* src);
    ~Shader();
    void fromFile(const string& filename);
    void toFile(const string& filename);
    void setType(Shader::SHADER_TYPE _type);
    void setType(GLuint _type);
    void setType(const string& _type);
    GLuint create();
    GLenum getType() {return type;}
    GLuint getId() {return id;}
    string getTypeNameAndExtension(string& typeName);
};




#endif //PAIRWISEDISTANCEOPENGLSHADERS_SHADER_CONTROLLER_H
