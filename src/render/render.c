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

    igRender();
    ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());

    glfwSwapBuffers(app->window.window);
    glfwPollEvents();
    
}
void UpdateGUI(Application *app){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    igNewFrame();

    igBegin("Stats", NULL, 0);
    igText("%f ms / %i fps\n",1000.0/(double)app->fps,app->fps);
    //igButton("Test",(struct ImVec2){0,0});
    igEnd();

    // // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. 
    // // Here we just want to make the demo initial state a bit more friendly!
    // igSetNextWindowPos((struct ImVec2){0,0}, ImGuiCond_FirstUseEver,(struct ImVec2){0,0} ); 
    //igShowDemoWindow(NULL);
}