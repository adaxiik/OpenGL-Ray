cmake_minimum_required(VERSION 3.0.0)
project(OpenGLRay LANGUAGES C VERSION 1.0)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-rtti -Wall -flto -ftree-vectorize -march=native -O3 -mtune=generic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address -Wall -Wextra")
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})

file(GLOB SOURCES "src/render/*.c" "src/logic/*.c")

add_executable(OpenGLRay src/main.c src/glad.c ${SOURCES})
target_include_directories(OpenGLRay PRIVATE /include)
target_link_libraries(OpenGLRay ${OPENGL_gl_LIBRARY} glfw3 dl m pthread)

file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})