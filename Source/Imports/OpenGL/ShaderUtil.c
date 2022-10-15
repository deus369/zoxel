#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
const char *shaderFilepath = "Resources/Shaders/BasicRender2D";
const char *vertExtension = ".vert";
const char *fragExtension = ".frag";
GLuint material;
GLuint vbo;
GLuint vao;
GLuint gl_positionX;
GLuint gl_positionY;
GLuint gl_view_matrix;
GLuint gl_angle;
GLuint gl_scale;
GLuint gl_brightness;

int LoadShader(char* filepath, GLenum shaderType, GLuint* shader2)
{
    if (strlen(filepath) == 0)
    {
        printf("Shader Filepath is Empty.\n");
        free(filepath);
        return -1;
    }
    // printf("Loading Shader [%s] \n", filepath);
    // size_t *bufferSize;
    GLchar *buffer = (GLchar*) SDL_LoadFile(filepath, NULL); // bufferSize);
    if (!buffer)
    {
        printf("Loading shader returned null: %s\n", filepath);
        free(filepath);
        return -1;
    }
    free(filepath);
    // printf("Success Loading Shader Source!"); //  [%i] \n", bufferSize);
    // const char *ext = SDL_strrchr(buffer, '.');
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, (const GLchar**) &buffer, NULL); // &bufferSize);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        GLint info_log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar* info_log = malloc(info_log_length);
        glGetShaderInfoLog(shader, info_log_length, NULL, info_log);
        fprintf(stderr, "Failed to Compile Shader:\n%s\n", info_log);
        free(info_log);
        return -1;
    }
    free(buffer);
    *shader2 = shader;
    // printf("Success Loading Shader Source!"); //   [%i] \n", bufferSize);
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
    // Load the modern OpenGL funcs
    printf("Initializing OpenGL");
    printf("OpenGL Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL Version:  %s\n", glGetString(GL_VERSION));
    printf("GLSL Version:    %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

int LoadShaders()
{
    GLuint vertShader;
    char *vertFilename = malloc(strlen(shaderFilepath) + strlen(vertExtension) + 1);
    strcpy(vertFilename, shaderFilepath);
    strcat(vertFilename, vertExtension);
    if (vertFilename)
    {
        if (LoadShader(vertFilename, GL_VERTEX_SHADER, &vertShader) != 0)
        {
            printf("Error loading Shader Vert.\n");
            return -1;
        }
    }
    else
    {
        return -1;
    }
    GLuint fragShader;
    char *fragFilename = malloc(strlen(shaderFilepath) + strlen(vertExtension) + 1);
    strcpy(fragFilename, shaderFilepath);
    strcat(fragFilename, fragExtension);
    if (fragFilename)
    {
        if (LoadShader(fragFilename, GL_FRAGMENT_SHADER, &fragShader) != 0)
        {
            printf("Error loading Shader Frag.\n");
            return -1;
        }
    }
    else
    {
        return -1;
    }
    material = glCreateProgram();
    LinkShaderProgram(material, vertShader, fragShader);
    // Keep a reference to the GPU data
    gl_angle = glGetUniformLocation(material, "angle");
    gl_scale = glGetUniformLocation(material, "scale");
    gl_brightness = glGetUniformLocation(material, "brightness");
    gl_positionX = glGetUniformLocation(material, "positionX");
    gl_positionY = glGetUniformLocation(material, "positionY");
    gl_view_matrix = glGetUniformLocation(material, "viewMatrix");
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
    return 0;
}

/*int GetStringSize(const char* text)
{
    int count = 0;
    while (text[count] != '\0')
    {
        count++;
    }
    return count;
}*/