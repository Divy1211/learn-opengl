#pragma once

class IndexBuffer {

private:
    unsigned int rendererId;
    unsigned int count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    [[nodiscard]] unsigned int getCount() const {
        return this->count;
    }
};