#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>


// #define INCBIN_PREFIX
// #include "../incbin/incbin.h"       // Using https://github.com/graphitemaster/incbin/
// #include "opengl.h"
// #include "../../Core/Core/Core.h"
// Use a shaders folder
// const char *shaderFilepath = "BasicRender2D";
// INCBIN(basicRender2DVert, "../../../Shaders/BasicRender2D.vert");
// INCBIN(basicRender2DVert, "../../../Shaders/BasicRender2D.vert");
// Fuck this isn't going to work on other machines..
// Convert shader files to .c files, add on \n's or something.. create a header file generated with includes
// Get filepath of game, add that on!
const char *shaderFilepath = "/home/deus/projects/open-zoxel/src/Shaders/BasicRender2D";
const char *vertExtension = ".vert";
const char *fragExtension = ".frag";

GLuint material;
GLuint vbo;
GLuint vao;
GLuint gl_position_x;
GLuint gl_position_y;
GLuint gl_angle;
GLuint gl_scale;
GLuint gl_brightness;
// version 330
// layout(location = 0)
const float squareSize = 0.1f;
// createt cube floats
const float squareVerts[] =
{
    -squareSize,  squareSize,
    -squareSize, -squareSize,
     squareSize,  squareSize,
     squareSize, -squareSize
};

int GetStringSize(const char* text)
{
    int count = 0;
    while (text[count] != '\0')
    {
        count++;
    }
    return count;
}

int GetFileSize(const char* filepath, int32_t* file_size)
{
    FILE* file = fopen(filepath, "rb");
    if (file == NULL)
    {
        printf("Can't open shader file: %s \n", filepath);
        return -1;
    }
    fseek(file, 0L, SEEK_END);
    *file_size = ftell(file);
    fclose(file);
    return 0;
}

int LoadShaderFile(const char* filepath, GLchar* buffer, GLint size)
{
    FILE* file = fopen(filepath, "rb");
    if (file == NULL)
    {
        printf("Can't open shader file: %s \n", filepath);
        return -1;
    }
    fread(buffer, size, 1, file);
    buffer[size] = 0;
    fclose(file);
    return 0;
}

int CompileShader(const char* buffer, GLenum shaderType, GLuint* shader2)
{
    GLint bufferSize = (GLint) GetStringSize(buffer);
    printf("Compiling Shader: %i\n", bufferSize);
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, (const GLchar**) &buffer, &bufferSize);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        GLint info_log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar* info_log = malloc(info_log_length);
        glGetShaderInfoLog(shader, info_log_length, NULL, info_log);
        fprintf(stderr, "Failed to compile shader:\n%s\n", info_log);
        free(info_log);
        return -1;
    }
    // free(buffer);
    *shader2 = shader;
    printf("Success Loading Shader Source [%i] \n", (int) bufferSize);
    return 0;
}

int LoadShader(const char* filepath, GLenum shaderType, GLuint* shader2)
{
    if (GetStringSize(filepath) == 0)
    {
        printf("Shader Filepath is Empty.\n");
        return -1;
    }
    printf("Loading Shader [%s] \n", filepath);
    GLchar* buffer;
    GLint bufferSize;
    GetFileSize(filepath, &bufferSize);
    buffer = (GLchar*) malloc((bufferSize+1) * sizeof(GLchar));
    if (buffer == NULL)
    {
        printf("Can't allocate Shader buffer. \n");
        return -1;
    }
    LoadShaderFile(filepath, buffer, bufferSize);
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, (const GLchar**) &buffer, &bufferSize);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        GLint info_log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar* info_log = malloc(info_log_length);
        glGetShaderInfoLog(shader, info_log_length, NULL, info_log);
        fprintf(stderr, "Failed to compile shader:\n%s\n", info_log);
        free(info_log);
        return -1;
    }
    free(buffer);
    *shader2 = shader;
    printf("Success Loading Shader Source [%i] \n", (int) bufferSize);
    return 0;
}

bool LinkShaderProgram(GLuint program, GLuint vertex_shader, GLuint fragment_shader)
{
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success != GL_TRUE)
    {
        GLint info_log_length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);

        GLchar* info_log = malloc(info_log_length);
        glGetProgramInfoLog(program, info_log_length, NULL, info_log);

        fprintf(stderr, "failed to link program:\n%s\n", info_log);
        free(info_log);

        glDetachShader(program, vertex_shader);
        glDetachShader(program, fragment_shader);

        return false;
    }
    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);
    return false;
}

void PrintOpenGL()
{
    printf("Initializing OpenGL");
    printf("OpenGL Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL Version:  %s\n", glGetString(GL_VERSION));
    printf("GLSL Version:    %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void InitializeOpenGL(bool vsync)
{
    // Enable v-sync (set 1 to enable, 0 to disable)
    SDL_GL_SetSwapInterval(vsync ? 1 : 0);
    // Load the modern OpenGL funcs
    opengl_load_functions();
    // printf("basicRender2DVertEnd: %i\n", GetStringSize(basicRender2DVertEnd));
    /*if (CompileShader(basicRender2DVertEnd, GL_VERTEX_SHADER, &vertShader) != 0)
    {
        printf("Error loading Shader Vert");
    }*/
    GLuint vertShader;
    GLuint fragShader;
    int mallocSize = GetStringSize(shaderFilepath) + GetStringSize(vertExtension);
    printf("mallocSize [%i]\n", mallocSize);
    char *vertFilename = malloc(mallocSize);
    if (vertFilename)
    {
        strcpy(vertFilename, shaderFilepath);
        strcat(vertFilename, vertExtension);
        if (LoadShader(vertFilename, GL_VERTEX_SHADER, &vertShader) != 0)
        {
            printf("Error loading Shader Vert");
        }
        free(vertFilename);
    }
    char *fragFilename = malloc(mallocSize);
    if (fragFilename)
    {
        strcpy(fragFilename, shaderFilepath);
        strcat(fragFilename, fragExtension);
        if (LoadShader(fragFilename, GL_FRAGMENT_SHADER, &fragShader) != 0)
        {
            printf("Error loading Shader Frag");
        }
        free(fragFilename);
    }
    material = glCreateProgram();
    LinkShaderProgram(material, vertShader, fragShader);
    // Keep a reference to the GPU data
    gl_angle = glGetUniformLocation(material, "angle");
    gl_scale = glGetUniformLocation(material, "scale");
    gl_brightness = glGetUniformLocation(material, "brightness");
    gl_position_x = glGetUniformLocation(material, "pointX");
    gl_position_y = glGetUniformLocation(material, "pointY");
    // GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVerts), squareVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // Clean up shaders
    glDeleteShader(fragShader);
    glDeleteShader(vertShader);
}

//! Cleanup OpenGL resources
void EndOpenGL()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(material);
}

void UpdateBeginOpenGL()
{
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);       // Clears the buffer ?
    //! This sets the materials actually, would be best to group entities per material here?
    glUseProgram(material);
}

void RenderEntity2D(float positionX, float positionY, float angle, float scale, float brightness)
{
    // glPushMatrix();
    // glTranslatef(positionX, positionY, 0);
    // set variables, can this be done using a filtered / system ?
    glUniform1f(gl_position_x, positionX);
    glUniform1f(gl_position_y, positionY);
    glUniform1f(gl_angle, angle);
    glUniform1f(gl_scale, scale);
    glUniform1f(gl_brightness, brightness);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(squareVerts) / sizeof(*squareVerts) / 2);
    //glPopMatrix();
}

void UpdateEndOpenGL()
{
    glBindVertexArray(0);
    glUseProgram(0);
}

// vert shader
// const GLchar *vertSource =
//     "#version 330\n"
//     "layout(location = 0) in vec2 point;\n"
//     "uniform float pointX;\n"
//     "uniform float pointY;\n"
//     "uniform float angle;\n"
//     "uniform float scale;\n"
//     "void main() {\n"
//     "    vec2 position2D = vec2(pointX, pointY);\n"
//     "    mat2 rotate = mat2(cos(angle), -sin(angle),\n"
//     "                       sin(angle), cos(angle));\n"
//     "    gl_Position = vec4(position2D + (rotate * point) * scale, 0.0, 1.0);\n"
//     "}\n";
// // fragment shader
// const GLchar *fragSource =
//     "#version 330\n"
//     "uniform float brightness;\n"
//     "out vec4 color;\n"
//     "void main() {\n"
//     "    color = vec4(0.1, 0.65, 0.15, 0) * brightness;\n"
//     "}\n";