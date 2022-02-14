#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned CompileShaders(const char* vertex_shader_path, const char* fragment_shader_path);
char *ReadFile(const char *path);

void Set1f(unsigned shaderProgram, const char *name, float a);
void Set2f(unsigned shaderProgram, const char *name, float a, float b);
void Set3f(unsigned shaderProgram, const char *name, float a, float b, float c);
void Set4f(unsigned shaderProgram, const char *name, float a, float b, float c, float d);

void Set1i(unsigned shaderProgram, const char *name, int a);
void Set2i(unsigned shaderProgram, const char *name, int a, int b);
void Set3i(unsigned shaderProgram, const char *name, int a, int b, int c);
void Set4i(unsigned shaderProgram, const char *name, int a, int b, int c, int d);
