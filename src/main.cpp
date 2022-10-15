#define GLFW_INCLUDE_NONE
#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Renderer.h"
#include "classes/VertexBuffer.h"
#include "classes/VertexBufferLayout.h"
#include "classes/IndexBuffer.h"
#include "classes/Display.h"
#include "classes/Position.h"
#include "classes/VertexArray.h"

static std::string parseShader(const std::string& filepath) {
    std::ifstream stream(filepath);
    std::string line;

    std::stringstream src;
    while(getline(stream, line)) {
        src << line << "\n";
    }

    return src.str();
}

static unsigned int compileShader(unsigned int type, const std::string& src) {
    unsigned int id = glCreateShader(type);
    const char* csrc = src.c_str();
    glShaderSource(id, 1, &csrc, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE) {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char* msg = (char*)alloca(len*sizeof(char));
        glGetShaderInfoLog(id, len, &len, msg);
        std::cerr << msg << "\n";
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


int main() {
    glfwSetErrorCallback(errorCallback);
    if (!glfwInit()) {
        std::cerr << "Error: GLFW initialisation failed";
        return 1;
    }

    Display display {640, 480, "ScenarioDE", nullptr, nullptr};
    gladLoadGL(glfwGetProcAddress);

    Position positions[] {
        {-0.5, -0.5},
        {0.5, -0.5},
        {0.5, 0.5},
        {-0.5, 0.5},
    };
    constexpr unsigned int NUM_POS {4};

    unsigned int indices[] {0, 1, 2, 2, 3, 0};
    constexpr unsigned int NUM_IDX {6};

    VertexArray va {};
    VertexBuffer vb {positions, NUM_POS*sizeof(Position)};
    VertexBufferLayout vbl {};
    vbl.push<float>(2);
    va.addBuffer(vb, vbl);

    IndexBuffer ib {indices, NUM_IDX};

    std::string vs = parseShader("../res/shaders/vertex.glsl");
    std::string fs = parseShader("../res/shaders/fragment.glsl");

    unsigned int shader = createShader(vs, fs);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_colour");
    if(location == -1)
        std::cerr << "u_colour not found";
    float colour[] {0.2, 0.3, 0.4, 0.5};
    float dcolour[] {0.01, 0.01, 0.01, 0.01};

    while (!glfwWindowShouldClose(display.getWindow())) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform4f(location, colour[0], colour[1], colour[2], colour[3]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        colour[0] += dcolour[0];
        colour[1] += dcolour[1];
        colour[2] += dcolour[2];
        colour[3] += dcolour[3];

        if(colour[0] >= 1 || colour[0] <= 0)
            dcolour[0] *= -1;
        if(colour[1] >= 1 || colour[1] <= 1)
            dcolour[1] *= -1;
        if(colour[2] >= 1 || colour[2] <= 0)
            dcolour[2] *= -1;
        if(colour[3] >= 1 || colour[3] <= 0)
            dcolour[3] *= -1;

        glfwSwapBuffers(display.getWindow());
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    return 0;
}
