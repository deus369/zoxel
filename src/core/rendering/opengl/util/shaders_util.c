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
        // fprintf(stderr, " - failed to link program:\n%s\n", info_log);
        zoxel_log_arg("Failed to link [%i], program:\n%s\n", (int) program, info_log);
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
    if (shader.x == 0 || shader.y == 0)
    {
        return 0;
    }
    GLuint material = glCreateProgram();
    #ifdef zoxel_catch_opengl_errors
        GLenum err2 = glGetError();
        if (err2 != GL_NO_ERROR)
        {
            zoxel_log_arg("GL ERROR with spawn_gpu_material_program [%i] - glCreateProgram\n",
                (int) err2);
            return -1;
        }
    #endif
    LinkShaderProgram(material, shader.x, shader.y);
    #ifdef zoxel_catch_opengl_errors
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            zoxel_log_arg("GL ERROR with spawn_gpu_material_program [%i] - shader [%ix%i]\n",
                (int) err, shader.x, shader.y);
            return -1;
        }
    #endif
    return material;
}

int compile_shader(GLenum shaderType, GLuint* shader2, const GLchar* buffer)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, (const GLchar **) &buffer, NULL);
    glCompileShader(shader);
    // glValidateProgram(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        GLint info_log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar* info_log = malloc(info_log_length);
        glGetShaderInfoLog(shader, info_log_length, NULL, info_log);
        // zoxel_log_arg(stderr, "Failed to compile shader:\n%s\n", info_log);
        zoxel_log_arg("Failed to compile shader:\n%s\n", info_log);
        free(info_log);
        return -1;
    }
    *shader2 = shader;
    return 0;
}

int load_shader(const char* filepath, GLenum shaderType, GLuint* shader2)
{
    if (strlen(filepath) == 0)
    {
        zoxel_log("Shader Filepath is Empty.\n");
        return -1;
    }
    char* fullpath = get_full_file_path(filepath);
    GLchar *buffer = (GLchar*) SDL_LoadFile(fullpath, NULL); //filepath, NULL);
    free(fullpath);
    if (!buffer)
    {
        zoxel_log_arg("Loading shader (SDL_LoadFile) returned null at [%s].\n", filepath);
        return -1;
    }
    // this is causing crashes...
    if (compile_shader(shaderType, shader2, buffer) != 0)
    {
        free(buffer);
        return -1;
    }
    free(buffer);
    return 0;
}

GLuint2 spawn_gpu_shader(const char* vertFilepath, const char* fragFilepath)
{
    GLuint2 shader = { 0, 0 };
    if (load_shader(vertFilepath, GL_VERTEX_SHADER, &shader.x) != 0)
    {
        zoxel_log_arg("Error loading shader vert [%s]\n", vertFilepath);
        return shader;
    }
    // GLuint fragShader;
    if (load_shader(fragFilepath, GL_FRAGMENT_SHADER, &shader.y) != 0)
    {
        zoxel_log_arg("Error loading shader frag [%s]\n", fragFilepath);
        return shader;
    }
    return shader;
}

GLuint2 spawn_gpu_shader_inline(const GLchar* vert_buffer, const GLchar* frag_buffer)
{
    GLuint2 shader = { 0, 0 };
    if (compile_shader(GL_VERTEX_SHADER, &shader.x, vert_buffer) != 0)
    {
        zoxel_log_arg("Error loading shader vert [%s]\n", vert_buffer);
        return shader;
    }
    if (compile_shader(GL_FRAGMENT_SHADER, &shader.y, frag_buffer) != 0)
    {
        zoxel_log_arg("Error loading shader frag [%s]\n", frag_buffer);
        return shader;
    }
    return shader;
}

//! For when you only need one material, otherwise will need to return shaders too. Returns material reference.
GLuint load_gpu_shader(GLuint2* shader, const char* vertFilepath, const char* fragFilepath)
{
    // GLuint vertShader;
    if (load_shader(vertFilepath, GL_VERTEX_SHADER, &shader->x) != 0)
    {
        zoxel_log_arg("Error loading shader vert [%s]\n", vertFilepath);
        return 0;
    }
    // GLuint fragShader;
    if (load_shader(fragFilepath, GL_FRAGMENT_SHADER, &shader->y) != 0)
    {
        zoxel_log_arg("Error loading shader frag [%s]\n", fragFilepath);
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
    compile_shader(vertexShaderSource, GL_VERTEX_SHADER, &vertShader);
    compile_shader(fragShaderSource, GL_FRAGMENT_SHADER, &fragShader);
    material = glCreateProgram();
    LinkShaderProgram(material, vertShader, fragShader);
    // Clean up shaders
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    initialize_mesh(material);
    return 0;
}*/


    /*glUseProgram(shader);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        printf("GL ERROR with glUseProgram!");
        return -1;
    }*/
    /*GLuint shader = glCreateShader(shaderType);
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
    *shader2 = shader;*/