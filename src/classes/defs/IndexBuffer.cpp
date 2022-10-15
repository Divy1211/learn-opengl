#include "glad/gl.h"

#include "../../Renderer.h"
#include "../IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count): count(count) {
    GLCALL(glGenBuffers(1, &this->rendererId));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->rendererId));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GLCALL(glDeleteBuffers(1, &this->rendererId))
}

void IndexBuffer::bind() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->rendererId));
}

void IndexBuffer::unbind() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
