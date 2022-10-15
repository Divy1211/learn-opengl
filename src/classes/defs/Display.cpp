#include <iostream>

#include "../Display.h"

Display::Display(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* window) {
    this->window = glfwCreateWindow(width, height, title, monitor, window);
    if (!this->window) {
        std::cerr << "GLFW window creation failed" << "\n";
    }
    glfwMakeContextCurrent(this->window);

}

Display::~Display() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void Display::makeCurrentContext() {
    glfwMakeContextCurrent(this->window);
}

GLFWwindow* Display::getWindow() {
    return this->window;
}
