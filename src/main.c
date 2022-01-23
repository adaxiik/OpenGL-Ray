#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/render/setup.h"
#include "../include/render/render.h"

#define WIDTH 800
#define HEIGHT 600

void processInput(GLFWwindow *window);

int main(void)
{
    Application app = Setup(WIDTH,HEIGHT,"OpenGL go brr");
    
    glfwSwapInterval(1); //vsync


    double lastTime = glfwGetTime();
    int frames = 0;
    while (!glfwWindowShouldClose(app.window.window))
    {
        double currentTime = glfwGetTime();
        ++frames;
        if(currentTime - lastTime >= 3.0){
            //printf("%f ms/frame\n",1000.0/double(frames));
            printf("%f ms / %i fps\n",3000.0/(double)frames,frames/3);
            frames = 0;
            lastTime += 3.0;
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

