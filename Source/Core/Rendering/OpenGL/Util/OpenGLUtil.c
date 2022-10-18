#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// Stored Shader Variables
GLuint vbo;
GLuint gl_positionX;
GLuint gl_positionY;
GLuint gl_view_matrix;
GLuint gl_angle;
GLuint gl_scale;
GLuint gl_brightness;

void InitializeMesh()
{
    gl_angle = glGetUniformLocation(material, "angle");
    gl_scale = glGetUniformLocation(material, "scale");
    gl_brightness = glGetUniformLocation(material, "brightness");
    gl_positionX = glGetUniformLocation(material, "positionX");
    gl_positionY = glGetUniformLocation(material, "positionY");
    gl_view_matrix = glGetUniformLocation(material, "viewMatrix");
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVerts), squareVerts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//! Cleanup OpenGL resources
void EndAppOpenGL()
{
    // glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(material);
}

void UpdateBeginOpenGL(const float* viewMatrix)
{
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);       // Clears the buffer ?
    //! This sets the materials actually, would be best to group entities per material here?
    glUseProgram(material);
    if (viewMatrix)
    {
        glUniformMatrix4fv(gl_view_matrix, 1, GL_FALSE, (const GLfloat*) viewMatrix);
    }
    // glBegin(GL_TRIANGLES);
    // glColor3f(0.1, 0.2, 0.3);
    // glVertex3f(0, 0, 0);
    // glVertex3f(1, 0, 0);
    // glVertex3f(0, 1, 0);
    // glEnd();
}

void RenderEntity2D(float2 position, float angle, float scale, float brightness)
{
    // set variables, can this be done using a filtered / system ?
    glUniform1f(gl_positionX, position.x);
    glUniform1f(gl_positionY, position.y);
    glUniform1f(gl_scale, scale);
    glUniform1f(gl_angle, angle);
    glUniform1f(gl_brightness, brightness);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(squareVerts) / sizeof(*squareVerts) / 2);
}

void UpdateEndOpenGL()
{
    glUseProgram(0);
}

void EndAppGraphics()
{
    //EndAppOpenGL();
}

// GluPerspective(fov, aspectRatio, 1.0f, 100.0f);
// glViewport(0, 0, (GLsizei) screenWidth, (GLsizei) screenHeight);
/*glMatrixMode( GL_PROJECTION );
glLoadIdentity();
// gluOrtho2D(-1.0 * aspectRatio, aspectRatio, -1.0, 1.0);
glMatrixMode( GL_MODELVIEW );
glLoadIdentity();*/

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

    /*GLchar* buffer;
    buffer = (GLchar*) malloc((bufferSize+1) * sizeof(GLchar));
    if (buffer == NULL)
    {
        printf("Can't allocate Shader buffer. \n");
        return -1;
    }
    LoadShaderFile(filepath, buffer, bufferSize);*/
    // GetFileSize(filepath, &bufferSize);

/*int CompileShader(const char* buffer, GLenum shaderType, GLuint* shader2)
{
    // GLint bufferSize = (GLint) GetStringSize(buffer); // (GLchar) 
    // printf("Compiling Shader: %i\n", bufferSize);
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, (const GLchar**) &buffer, NULL); // (const GLchar**) &bufferSize);
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
    // printf("Success Loading Shader Source [%i] \n", (int) bufferSize);
    return 0;
}*/

/*int GetFileSize(const char* filepath, int32_t* file_size)
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
}*/
    // char *fragFilename = malloc(mallocSize);
        // strcpy(fragFilename, shaderFilepath);
        // strcat(fragFilename, fragExtension);

// #define INCBIN_PREFIX
// #include "../incbin/incbin.h"       // Using https://github.com/graphitemaster/incbin/
// #include "opengl.h"
// #include "../../Core/Core/Core.h"
// Use a shaders folder
// const char *shaderFilepath = "BasicRender2D";
// INCBIN(basicRender2DVert, "../../../Resources/Shaders/BasicRender2D.vert");
// INCBIN(basicRender2DVert, "../../../Resources/Shaders/BasicRender2D.vert");
// Fuck this isn't going to work on other machines..
// Convert shader files to .c files, add on \n's or something.. create a header file generated with includes
// Get filepath of game, add that on!
// version 330
// layout(location = 0)
    // PrintOpenGL();
    // printf("basicRender2DVertEnd: %i\n", GetStringSize(basicRender2DVertEnd));
    /*if (CompileShader(basicRender2DVertEnd, GL_VERTEX_SHADER, &vertShader) != 0)
    {
        printf("Error loading Shader Vert");
    }*/
    // glPushMatrix();
    // glMultMatrixf(mat44);
    // glLoadMatrixf(mat44);
    // glTranslatef(positionX, positionY, 0);
    // glRotatef( 0, 0.0, 0.0, 1.0 );
    // glScalef(scale, scale, scale);
    // glTranslatef(positionX, positionY, 0);
    // glPopMatrix();