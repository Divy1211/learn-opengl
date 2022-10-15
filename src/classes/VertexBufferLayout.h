#pragma once

#include "glad/gl.h"

#include <vector>

struct VertexBufferElement {
    unsigned int type;
    int count;
    unsigned char normalised;

    [[nodiscard]] int size() const {
        switch(this->type) {
            case GL_FLOAT: return sizeof(float);
            case GL_UNSIGNED_INT: return sizeof(unsigned int);
            case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
        }
        return 0;
    }
};

class VertexBufferLayout {
private:
    int stride;
    std::vector<VertexBufferElement> elements;
public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    template<typename T>
    void push(int count);

    template<>
    void push<float>(int count);

    template<>
    void push<unsigned int>(int count);

    template<>
    void push<unsigned char>(int count);

    [[nodiscard]] int getStride() const;
    [[nodiscard]] std::vector<VertexBufferElement> getElements() const;
};