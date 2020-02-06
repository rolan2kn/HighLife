//
// Created by rkindela on 02-10-19.
//

#ifndef PAIRWISEDISTANCEOPENGLSHADERS_DATA_BUFFER_H
#define PAIRWISEDISTANCEOPENGLSHADERS_DATA_BUFFER_H

#include <glad/glad.h>

#include <iostream>
using namespace std;


class DataBuffer {
private:
    GLuint vertexArrayObject;
    GLuint bufferObject;
    GLuint bufferPos;
    GLuint shaderProgram;
public:
    DataBuffer(GLuint _bufferPos, GLuint shaderProgram);
    void generate(GLuint glDataType, size_t size_data, void* firstDataPointer, bool createVertexArray = true);
    void enableAttributeArrayByName(const GLchar* attribName, GLuint vertexSize, bool normalized, size_t vertexPadding, void* offset);
    void enableAttributeArrayByPosition(GLuint attribPos, GLuint vertexSize, bool normalized, size_t vertexPadding, void* offset);
    GLuint getAttribPosition(const GLchar* attribName) const;
    void setVertexArrayObject(GLuint VAO);
    GLuint getVertexArrayObject() const { return  vertexArrayObject;}

    void bindVertexArray(GLuint pos);


};


#endif //PAIRWISEDISTANCEOPENGLSHADERS_DATA_BUFFER_H
