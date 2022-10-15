#define GLFW_INCLUDE_NONE

#include "glad/gl.h"

#include <iostream>

#include "Renderer.h"

 void errorCallback(int error, const char* description) {
    std::cerr << "Error: " << description << "\n";
}

void clearGlErrors() {
    while(glGetError() != GL_NO_ERROR);
}

void checkGlErrors(const char* func, const char* file, int line) {
    while(GLenum errCode = glGetError()) {
        std::cerr << "[OpenGL Error] (" << errCode << ") in " << func << " at " << file << "::" << line << "\n";
    }
}