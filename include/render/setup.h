#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
typedef struct {
    GLFWwindow* window;
    int width;
    int height;
    char title[256];
} Window;

typedef struct{
    Window window;
    unsigned VAO,VBO,shaderProgram; 
}Application;
Application Setup(const int width, const int height, const char* title);


void LoadGLFW(Application* app);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void LoadGLAD(void);
void SetupRenderingScreen(Application* app);

void CleanUp(Application* app);