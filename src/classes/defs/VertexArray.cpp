#include "../../utils.h"
#include "../VertexBufferLayout.h"
#include "../VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &this->rendererId);
    glBindVertexArray(this->rendererId);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &this->rendererId);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const {
    this->bind();
    vb.bind();
    unsigned int offset {0};
    for(auto [i, element] : enumerate(layout.getElements())) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i,
            element.count,
            element.type,
            element.normalised,
            layout.getStride(),
            (const void*)offset
        );
        offset += element.count*element.size();
    }
}

void VertexArray::bind() const {
    glBindVertexArray(this->rendererId);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}
