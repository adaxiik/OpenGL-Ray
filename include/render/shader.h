#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned CompileShaders(const char* vertex_shader_path, const char* fragment_shader_path);
char *ReadFile(const char *path);