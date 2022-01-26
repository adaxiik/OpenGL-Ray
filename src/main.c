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

int main(void)
{
    Application app = Setup(WIDTH,HEIGHT,"OpenGL go brr");
    glfwSwapInterval(0); //vsync
    
    double lastTime = glfwGetTime();
    int frames = 0;

    while (!glfwWindowShouldClose(app.window.window))
    {
        UpdateGUI(&app);
        double currentTime = glfwGetTime();
        ++frames;
        if(currentTime - lastTime >= 1.0){
            //printf("%f ms/frame\n",1000.0/double(frames));
            app.fps = frames;
            frames = 0;
            lastTime += 1.0;
        }
        glfwGetWindowSize(app.window.window, &app.window.width, &app.window.height);
        processInput(app.window.window);
        RenderScreen(&app);
    }
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

