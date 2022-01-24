#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/render/setup.h"
#include "../include/render/render.h"

//#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#define WIDTH 800
#define HEIGHT 600

void processInput(GLFWwindow *window);

struct ImGuiContext* ctx;
struct ImGuiIO* io;

void gui_init(Application *app) {
    // IMGUI_CHECKVERSION();
    ctx = igCreateContext(NULL);
    io  = igGetIO();

    const char* glsl_version = "#version 330 core";
    ImGui_ImplGlfw_InitForOpenGL(app->window.window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup style
    igStyleColorsDark(NULL);
}

void gui_terminate(void) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    igDestroyContext(ctx);
}

void gui_render(void) {
    igRender();
    ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}
void gui_update(int fps) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    igNewFrame();

    igBegin("Stats", NULL, 0);
    igText("%f ms / %i fps\n",3000.0/(double)fps,fps/3);
    //igButton("Test",(struct ImVec2){0,0});
    igEnd();

    // // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. 
    // // Here we just want to make the demo initial state a bit more friendly!
    // igSetNextWindowPos((struct ImVec2){0,0}, ImGuiCond_FirstUseEver,(struct ImVec2){0,0} ); 
    //igShowDemoWindow(NULL);
}

int main(void)
{
    Application app = Setup(WIDTH,HEIGHT,"OpenGL go brr");

    gui_init(&app);
    glfwSwapInterval(1); //vsync


    double lastTime = glfwGetTime();
    int frames = 0;
    int fps;
    while (!glfwWindowShouldClose(app.window.window))
    {
        gui_update(fps);
        double currentTime = glfwGetTime();
        ++frames;
        if(currentTime - lastTime >= 3.0){
            //printf("%f ms/frame\n",1000.0/double(frames));
            fps = frames;
            frames = 0;
            lastTime += 3.0;
        }
        glfwGetWindowSize(app.window.window, &app.window.width, &app.window.height);
        processInput(app.window.window);
        RenderScreen(&app);
        gui_render();

        glfwSwapBuffers(app.window.window);
        glfwPollEvents();
    }
    gui_terminate();
    CleanUp(&app);

    return 0;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

