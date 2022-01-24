#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

typedef struct {
    GLFWwindow* window;
    int width;
    int height;
    char title[256];
} Window;
typedef struct{
    struct ImGuiContext* ctx;
    struct ImGuiIO* io;
}GUI;
typedef struct{
    Window window;
    GUI gui;
    unsigned VAO,VBO,shaderProgram; 
    int fps;
}Application;
Application Setup(const int width, const int height, const char* title);


void LoadGLFW(Application* app);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void LoadGLAD(void);
void SetupRenderingScreen(Application* app);
void LoadGUI(Application *app);
void CleanUp(Application* app);