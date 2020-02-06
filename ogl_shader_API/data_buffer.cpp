//
// Created by rkindela on 02-10-19.
//

#include "data_buffer.h"



DataBuffer::DataBuffer(GLuint _bufferPos, GLuint _shaderProgram)
: bufferPos(_bufferPos), shaderProgram(_shaderProgram)
{

}

void DataBuffer::setVertexArrayObject(GLuint VAO)
{
    this->vertexArrayObject = VAO;
}

void DataBuffer::generate(GLuint glDataType, size_t size_data, void* firstDataPointer, bool createVertexArray)
{
    // Create a vertex array object
    if(createVertexArray)
    {
        glGenVertexArrays(this->bufferPos, &this->vertexArrayObject);
        glBindVertexArray(this->vertexArrayObject);
    }

    // Create and initialize a buffer object
    glGenBuffers( this->bufferPos, &this->bufferObject );
    glBindBuffer( glDataType, this->bufferObject );

    glBufferData( glDataType, size_data, firstDataPointer, GL_STATIC_DRAW );
}

void DataBuffer::enableAttributeArrayByName(const GLchar *attribName, GLuint vertexSize, bool normalized,
                                            size_t vertexPadding, void *offset)
{
    // Specify layout of point data
    int posAttrib = glGetAttribLocation(this->shaderProgram, attribName);
    glEnableVertexAttribArray(posAttrib);
    if (!normalized)
    {
        glVertexAttribPointer(posAttrib, vertexSize, GL_FLOAT, GL_FALSE, vertexPadding, offset);
    }
    else
    {
        glVertexAttribPointer(posAttrib, vertexSize, GL_FLOAT, GL_TRUE, vertexPadding, offset);
    }

}

void DataBuffer::enableAttributeArrayByPosition(GLuint posAttrib, GLuint vertexSize, bool normalized, size_t vertexPadding, void* offset)
{
    // Specify layout of point data
    glEnableVertexAttribArray(posAttrib);
    if (!normalized)
    {
        glVertexAttribPointer(posAttrib, vertexSize, GL_FLOAT, GL_FALSE, vertexPadding, offset);
    }
    else
    {
        glVertexAttribPointer(posAttrib, vertexSize, GL_FLOAT, GL_TRUE, vertexPadding, offset);
    }
}

GLuint DataBuffer::getAttribPosition(const GLchar* attribName) const
{
    return glGetAttribLocation(this->shaderProgram, attribName);
}

void DataBuffer::bindVertexArray(GLuint pos)
{
    glBindVertexArray(pos);
}


