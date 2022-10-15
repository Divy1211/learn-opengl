cmake_minimum_required(VERSION 3.22)
project(ScenarioDE)

set(CMAKE_CXX_STANDARD 20)

# glfw stuff
# to build on linux, run 'sudo apt install xorg-dev' first
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${PROJECT_SOURCE_DIR}/deps/glfw)

add_executable(
    ${PROJECT_NAME}
    deps/glad/src/gl.c

    src/classes/defs/VertexBuffer.cpp        src/classes/VertexBuffer.h
    src/classes/defs/IndexBuffer.cpp         src/classes/IndexBuffer.h
    src/classes/defs/VertexArray.cpp         src/classes/VertexArray.h
    src/classes/defs/Display.cpp             src/classes/Display.h
    src/classes/defs/VertexBufferLayout.cpp  src/classes/VertexBufferLayout.h

    src/classes/Position.h

    src/Renderer.cpp src/Renderer.h

    src/main.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/deps/glad/include)
target_link_libraries(${PROJECT_NAME} glfw)


