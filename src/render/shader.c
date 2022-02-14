#include "../../include/render/shader.h"
#include <stdio.h>
#include <stdlib.h>

unsigned CompileShaders(const char *vertex_shader_path, const char *fragment_shader_path){
    const char *vertexShaderSource = ReadFile(vertex_shader_path);
    const char *fragmentShaderSource = ReadFile(fragment_shader_path);

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "ERROR: Vertex shader compilation failed\n%s\n", infoLog);
        free((void*)vertexShaderSource);
        return 0;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fprintf(stderr,"ERROR: Fragment shader compilation failed\n %s\n",infoLog);
        free((void*)vertexShaderSource);
        free((void*)fragmentShaderSource);
        return 0;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr,"ERROR: Shader linking Failed\n %s\n",infoLog);
        free((void*)vertexShaderSource);
        free((void*)fragmentShaderSource);
        return 0;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    free((void*)vertexShaderSource);
    free((void*)fragmentShaderSource);
    return shaderProgram;
}

char *ReadFile(const char *path){
    FILE *fp;
    long lSize;
    char *buffer;

    fp = fopen(path, "rb");

    if (!fp)
        fprintf(stderr, "ERROR: File %s not found\n", path),exit(1);
        
    

    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    /* allocate memory for entire content */
    buffer = calloc(1, lSize + 1);
    if (!buffer)
        fclose(fp), fprintf(stderr, "ERROR: malloc failed\n"),exit(1);

    /* copy the file into the buffer */
    if (1 != fread(buffer, lSize, 1, fp))
        fclose(fp), free(buffer), fprintf(stderr, "ERROR: read failed\n"),exit(1);

    /* do your work here, buffer is a string contains the whole text */
    fclose(fp);
    return buffer;
}

void Set1f(unsigned shaderProgram, const char *name, float a){
    glUniform1f(glGetUniformLocation(shaderProgram, name), a);
}

void Set2f(unsigned shaderProgram, const char *name, float a, float b){
    glUniform2f(glGetUniformLocation(shaderProgram, name), a, b);
}

void Set3f(unsigned shaderProgram, const char *name, float a, float b, float c){
    glUniform3f(glGetUniformLocation(shaderProgram, name), a, b, c);
}

void Set4f(unsigned shaderProgram, const char *name, float a, float b, float c, float d){
    glUniform4f(glGetUniformLocation(shaderProgram, name), a, b, c, d);
}

void Set1i(unsigned shaderProgram, const char *name, int a){
    glUniform1i(glGetUniformLocation(shaderProgram, name), a);
}

void Set2i(unsigned shaderProgram, const char *name, int a, int b){
    glUniform2i(glGetUniformLocation(shaderProgram, name), a, b);
}

void Set3i(unsigned shaderProgram, const char *name, int a, int b, int c){
    glUniform3i(glGetUniformLocation(shaderProgram, name), a, b, c);
}

void Set4i(unsigned shaderProgram, const char *name, int a, int b, int c, int d){
    glUniform4i(glGetUniformLocation(shaderProgram, name), a, b, c, d);
}


