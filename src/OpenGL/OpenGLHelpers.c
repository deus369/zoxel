#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "opengl.h"
#include "../Core/Core.h"

GLuint prog;
GLuint vbo;
GLuint vao;
GLuint gl_position_x;
GLuint gl_position_y;
GLuint gl_angle;
GLuint gl_scale;
GLuint gl_brightness;

const float squareSize = 0.1f;

// createt cube floats
const float squareVerts[] =
{
    -squareSize,  squareSize,
    -squareSize, -squareSize,
     squareSize,  squareSize,
     squareSize, -squareSize
};

bool opengl_shader_compile_source(GLuint shader, const GLchar* source)
{
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        GLint info_log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar* info_log = malloc(info_log_length);
        glGetShaderInfoLog(shader, info_log_length, NULL, info_log);
        fprintf(stderr, "failed to compile shader:\n%s\n", info_log);
        free(info_log);
        return false;
    }
    return true;
}

bool opengl_shader_link_program(GLuint program, GLuint vertex_shader, GLuint fragment_shader)
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

void InitializeOpenGL(bool vsync)
{
    printf("OpenGL Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL Version:  %s\n", glGetString(GL_VERSION));
    printf("GLSL Version:    %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Enable v-sync (set 1 to enable, 0 to disable)
    SDL_GL_SetSwapInterval(vsync ? 1 : 0);
    
    // Load the modern OpenGL funcs
    opengl_load_functions();

    // vert shader
    const GLchar *vs_source =
        "#version 330\n"
        "layout(location = 0) in vec2 point;\n"
        "uniform float pointX;\n"
        "uniform float pointY;\n"
        "uniform float angle;\n"
        "uniform float scale;\n"
        "void main() {\n"
        "    vec2 position2D = vec2(pointX, pointY);\n"
        "    mat2 rotate = mat2(cos(angle), -sin(angle),\n"
        "                       sin(angle), cos(angle));\n"
        "    gl_Position = vec4(position2D + (rotate * point) * scale, 0.0, 1.0);\n"
        "}\n";
    // fragment shader
    const GLchar *fs_source =
        "#version 330\n"
        "uniform float brightness;\n"
        "out vec4 color;\n"
        "void main() {\n"
        "    color = vec4(0.1, 0.65, 0.15, 0) * brightness;\n"
        "}\n";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    opengl_shader_compile_source(vs, vs_source);
    opengl_shader_compile_source(fs, fs_source);

    prog = glCreateProgram();
    opengl_shader_link_program(prog, vs, fs);

    gl_angle = glGetUniformLocation(prog, "angle");
    gl_scale = glGetUniformLocation(prog, "scale");
    gl_brightness = glGetUniformLocation(prog, "brightness");
    gl_position_x = glGetUniformLocation(prog, "pointX");
    gl_position_y = glGetUniformLocation(prog, "pointY");

    glDeleteShader(fs);
    glDeleteShader(vs);

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
}

//! Cleanup OpenGL resources
void EndOpenGL()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(prog);
}

void UpdateBeginOpenGL()
{
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(prog);
}

void OpenGLRender(float positionX, float positionY, float angle, float scale, float brightness)
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