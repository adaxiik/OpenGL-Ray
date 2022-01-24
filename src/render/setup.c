#include "../../include/render/setup.h"
#include "../../include/render/shader.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void LoadGLFW(Application* app){
    
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    app->window.window = glfwCreateWindow(app->window.width, app->window.height, app->window.title, NULL, NULL);
    if (!app->window.window)
    {
        //std::cout << "Failed to create GLFW window" << std::endl;
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(app->window.window);
    glfwSetFramebufferSizeCallback(app->window.window, framebuffer_size_callback);
    
    
}

void LoadGLAD(void){
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialize GLAD\n");
        //std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }
}

void SetupRenderingScreen(Application* app){
     // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -1.0f, -1.0f, 0.0f, // left  
         3.0f, -1.0f, 0.0f, // right 
        -1.0f,  3.0f, 0.0f  // top   
    }; 


    glGenVertexArrays(1, &app->VAO);
    glGenBuffers(1, &app->VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(app->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, app->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void CleanUp(Application* app){
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &app->VAO);
    glDeleteBuffers(1, &app->VBO);
    glDeleteProgram(app->shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    
}
Application Setup(const int width, const int height, const char* title){
    Application app;
    app.window.width = width;
    app.window.height = height;
    strcpy(app.window.title, title);
    LoadGLFW(&app);
    LoadGLAD();
    SetupRenderingScreen(&app);
    if((app.shaderProgram = CompileShaders("assets/vert.vs", "assets/frag.fs")) == 0){
        fprintf(stderr, "Failed to compile shaders\n");
        CleanUp(&app);
        exit(1);
    }
    return app;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    
    (void)window;
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}