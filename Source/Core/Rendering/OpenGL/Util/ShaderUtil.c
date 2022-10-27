#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// things
const bool isForceDefaults = false;
const char* shaderVertFilepath = "Resources/Shaders/BasicRender2D.vert";
const char* shaderFragFilepath = "Resources/Shaders/BasicRender2D.frag";
const char* texturedRender2DVertPath = "Resources/Shaders/TexturedRender2D.vert";
const char* texturedRender2DFragPath = "Resources/Shaders/TexturedRender2D.frag";
GLuint material;
GLuint texturedMaterial;
// const char *vertExtension = ".vert";
// const char *fragExtension = ".frag";
extern void InitializeMesh(GLuint material);
extern void InitializeTexturedMesh(GLuint material);

int LoadShader(const char* filepath, GLenum shaderType, GLuint* shader2)
{
    if (strlen(filepath) == 0)
    {
        printf("Shader Filepath is Empty.\n");
        return -1;
    }
    GLchar *buffer = (GLchar*) SDL_LoadFile(filepath, NULL); // bufferSize);
    if (!buffer)
    {
        printf("Loading shader returned null: %s\n", filepath);
        return -1;
    }
    // this is causing crashes...
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
    glValidateProgram(shader);
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
    /*glUseProgram(shader);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        printf("GL HAD ERROR with glUseProgram!");
        return -1;
    }*/
    *shader2 = shader;
    return 0;
}

//! Used incase external shaders are missing
int LoadDefaultShaders()
{
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
    InitializeMesh(material);
    return 0;
}

int LoadTextureRender2DShader()
{
    GLuint vertShader;
    GLuint fragShader;
    if (LoadShader(texturedRender2DVertPath, GL_VERTEX_SHADER, &vertShader) != 0)
    {
        printf("Error loading Shader Vert 2.\n");
        return -1;
    }
    if (LoadShader(texturedRender2DFragPath, GL_FRAGMENT_SHADER, &fragShader) != 0)
    {
        printf("Error loading Shader Frag 2.\n");
        return -1;
    }
    texturedMaterial = glCreateProgram();
    LinkShaderProgram(texturedMaterial, vertShader, fragShader);
    return 0;
}

int LoadShaders()
{
    printf("Loading Shader Vert: %s\n", shaderVertFilepath);
    GLuint vertShader;
    if (LoadShader(shaderVertFilepath, GL_VERTEX_SHADER, &vertShader) != 0)
    {
        printf("Error loading Shader Vert.\n");
        return -1;
    }
    printf("Loading Shader Frag: %s\n", shaderFragFilepath);
    GLuint fragShader;
    if (LoadShader(shaderFragFilepath, GL_FRAGMENT_SHADER, &fragShader) != 0)
    {
        printf("Error loading Shader Frag.\n");
        return -1;
    }
    material = glCreateProgram();
    LinkShaderProgram(material, vertShader, fragShader);
    if (LoadTextureRender2DShader() != 0)
    {
        printf("Error loading Texture Shader.\n");
        return -1;
    }
    InitializeMesh(material);
    InitializeTexturedMesh(texturedMaterial);
    //printf("Material A %i\n", material);
    //printf("Material B %i\n", texturedMaterial);
    return 0;
}