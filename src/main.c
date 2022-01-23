#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/render/setup.h"
#include "../include/render/setup.h"


void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
    Application app = Setup(SCR_WIDTH,SCR_HEIGHT,"OpenGL go brr");

    // render loop
    // -----------
    while (!glfwWindowShouldClose(app.window.window))
    {
        glfwGetWindowSize(app.window.window, &app.window.width, &app.window.height);
        // input
        // -----
        processInput(app.window.window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(app.shaderProgram);
        glUniform2f(glGetUniformLocation(app.shaderProgram, "res"), app.window.width,app.window.height);
        //printf("%d %d\n",app.window.width,app.window.height);
        glBindVertexArray(app.VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(app.window.window);
        glfwPollEvents();
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

