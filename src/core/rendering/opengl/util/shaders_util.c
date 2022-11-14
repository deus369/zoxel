#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// things
const bool isForceDefaults = false;

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
        fprintf(stderr, " - failed to link program:\n%s\n", info_log);
        free(info_log);
        glDetachShader(program, vertShader);
        glDetachShader(program, fragShader);
        return false;
    }
    glDetachShader(program, vertShader);
    glDetachShader(program, fragShader);
    return false;
}

GLuint spawn_gpu_material_program(const GLuint2 shader)
{
    GLuint material = glCreateProgram();
    LinkShaderProgram(material, shader.x, shader.y);
    return material;
}

int LoadShader(const char* filepath, GLenum shaderType, GLuint* shader2)
{
    if (strlen(filepath) == 0)
    {
        printf("Shader Filepath is Empty.\n");
        return -1;
    }
    char* fullpath = get_full_file_path(filepath);
    GLchar *buffer = (GLchar*) SDL_LoadFile(fullpath, NULL); //filepath, NULL);
    free(fullpath);
    if (!buffer)
    {
        printf("Loading shader (SDL_LoadFile) returned null at [%s].\n", filepath);
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
        fprintf(stderr, " - failed to compile shader:\n%s\n", info_log);
        free(info_log);
        return -1;
    }
    free(buffer);
    *shader2 = shader;
    return 0;
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
        fprintf(stderr, "Failed to compile shader:\n%s\n", info_log);
        free(info_log);
        return -1;
    }
    *shader2 = shader;
    return 0;
}

//! For when you only need one material, otherwise will need to return shaders too. Returns material reference.
GLuint load_gpu_shader(GLuint2* shader, const char* vertFilepath, const char* fragFilepath)
{
    // GLuint vertShader;
    if (LoadShader(vertFilepath, GL_VERTEX_SHADER, &shader->x) != 0)
    {
        printf("Error loading shader vert [%s]\n", vertFilepath);
        return 0;
    }
    // GLuint fragShader;
    if (LoadShader(fragFilepath, GL_FRAGMENT_SHADER, &shader->y) != 0)
    {
        printf("Error loading shader frag [%s]\n", fragFilepath);
        return 0;
    }
    return spawn_gpu_material_program((const GLuint2) { shader->x, shader->y });
}

    /*GLuint material = glCreateProgram();
    LinkShaderProgram(material, shader.x, shader.y);
    // glDeleteShader(vertShader);
    // glDeleteShader(fragShader);
    return material;*/
    
//! Used incase external shaders are missing
/*int LoadDefaultShaders()
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
    // Clean up shaders
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    InitializeMesh(material);
    return 0;
}*/


    /*glUseProgram(shader);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        printf("GL HAD ERROR with glUseProgram!");
        return -1;
    }*/