#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// things
const bool isForceDefaults = false;
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

void InitializeMesh()
{
#ifdef USE_VERTEX_BUFFERS
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVerts), squareVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
#endif
}

int LoadShader(char* filepath, GLenum shaderType, GLuint* shader2)
{
    if (strlen(filepath) == 0)
    {
        printf("Shader Filepath is Empty.\n");
        free(filepath);
        return -1;
    }
    GLchar *buffer = (GLchar*) SDL_LoadFile(filepath, NULL); // bufferSize);
    if (!buffer)
    {
        printf("Loading shader returned null: %s\n", filepath);
        free(filepath);
        return -1;
    }
    free(filepath);
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, (const GLchar**) &buffer, NULL);
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
    return 0;
}

bool LinkShaderProgram(GLuint program, GLuint vertShader, GLuint fragShader)
{
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
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
        glDetachShader(program, vertShader);
        glDetachShader(program, fragShader);
        return false;
    }
    glDetachShader(program, vertShader);
    glDetachShader(program, fragShader);
    // Clean up shaders
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    return false;
}

int CompileShader(const GLchar* buffer, GLenum shaderType, GLuint* shader2)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, (const GLchar **) &buffer, NULL);
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
    *shader2 = shader;
    return 0;
}

//! Used incase external shaders are missing
int LoadDefaultShaders()
{
    //ftransform();\n"
    // "#version 300 es\n"
    //"     color = vec4(0.8, 0.65, 0.15, 0);\n"
    // "out lowp vec4 color;\n"
    // gl_Position = gl_Vertex;
    const GLchar *vertexShaderSource = \
        "void main(void) {\n" \
        "    gl_Position = vec4(0, 0, 0, 1);\n" \
        "}\n";
    const GLchar *fragShaderSource = \
        "void main() {\n" \
        "     gl_FragColor = vec4(0.8, 0.65, 0.15, 0);\n" \
        "}\n";
    GLuint vertShader;
    GLuint fragShader;
    CompileShader(vertexShaderSource, GL_VERTEX_SHADER, &vertShader);
    CompileShader(fragShaderSource, GL_FRAGMENT_SHADER, &fragShader);
    material = glCreateProgram();
    LinkShaderProgram(material, vertShader, fragShader);
    InitializeMesh();
    return 0;
}

int LoadShaders()
{
    if (isForceDefaults)
    {
        return LoadDefaultShaders();
    }
    GLuint vertShader;
    char *vertFilename = malloc(strlen(shaderFilepath) + strlen(vertExtension) + 1);
    strcpy(vertFilename, shaderFilepath);
    strcat(vertFilename, vertExtension);
    if (vertFilename)
    {
        if (LoadShader(vertFilename, GL_VERTEX_SHADER, &vertShader) != 0)
        {
            printf("Error loading Shader Vert.\n");
            return LoadDefaultShaders(); // -1;
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
            return LoadDefaultShaders(); // -1;
        }
    }
    else
    {
        return -1;
    }
    material = glCreateProgram();
    LinkShaderProgram(material, vertShader, fragShader);
    InitializeMesh();
    gl_angle = glGetUniformLocation(material, "angle");
    gl_scale = glGetUniformLocation(material, "scale");
    gl_brightness = glGetUniformLocation(material, "brightness");
    gl_positionX = glGetUniformLocation(material, "positionX");
    gl_positionY = glGetUniformLocation(material, "positionY");
    gl_view_matrix = glGetUniformLocation(material, "viewMatrix");
    return 0;
}