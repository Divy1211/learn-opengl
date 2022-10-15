#include "../VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout(): stride(0), elements({}) {}

VertexBufferLayout::~VertexBufferLayout() = default;

template<typename T>
void VertexBufferLayout::push(int count) {
    static_assert(false);
}

template<>
void VertexBufferLayout::push<float>(int count) {
    this->elements.push_back({GL_FLOAT, count, GL_FALSE});
    this->stride += this->elements.back().size()*count;
}

template<>
void VertexBufferLayout::push<unsigned int>(int count) {
    this->elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    this->stride += this->elements.back().size()*count;
}

template<>
void VertexBufferLayout::push<unsigned char>(int count) {
    this->elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    this->stride += this->elements.back().size()*count;
}

std::vector<VertexBufferElement> VertexBufferLayout::getElements() const {
    return this->elements;
}
int VertexBufferLayout::getStride() const {
    return this->stride;
}