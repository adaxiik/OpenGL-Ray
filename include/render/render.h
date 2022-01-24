#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../include/render/setup.h"
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
void RenderScreen(Application *app);
void UpdateGUI(Application *app);