#include "glad/gl.h"

#include "../../Renderer.h"
#include "../VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    GLCALL(glGenBuffers(1, &this->rendererId));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, this->rendererId));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    GLCALL(glDeleteBuffers(1, &this->rendererId))
}

void VertexBuffer::bind() const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, this->rendererId));
}

void VertexBuffer::unbind() const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
