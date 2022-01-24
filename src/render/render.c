#include "../../include/render/render.h"
void RenderScreen(Application *app){
    // render
    // ------
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // draw our first triangle
    glUseProgram(app->shaderProgram);
    glUniform2f(glGetUniformLocation(app->shaderProgram, "res"), app->window.width,app->window.height);
    glUniform1f(glGetUniformLocation(app->shaderProgram, "time"), (float)glfwGetTime());

    //printf("%d %d\n",app.window.width,app.window.height);
    glBindVertexArray(app->VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0); // no need to unbind it every time 

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    
}