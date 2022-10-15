#pragma once

#include "GLFW/glfw3.h"

class Display {
private:
    GLFWwindow* window;
public:
    Display(int height, int width, const char* title, GLFWmonitor* monitor, GLFWwindow* window);
    ~Display();

    void makeCurrentContext();
    GLFWwindow* getWindow();
};
