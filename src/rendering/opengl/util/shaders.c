void clear_regular_buffer(GLuint *gpu_buffer) {
    if (gpu_buffer) {
        glDeleteBuffers(1, gpu_buffer);
        *gpu_buffer = 0;
    }
}

byte initialize_material(GLuint material, GLuint vert_shader, GLuint frag_shader) {
    glAttachShader(material, vert_shader);
    glAttachShader(material, frag_shader);
    glLinkProgram(material);
    GLint success;
    glGetProgramiv(material, GL_LINK_STATUS, &success);
    // if errors
    if (success != GL_TRUE) {
        GLint info_log_length;
        glGetProgramiv(material, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar* info_log = malloc(info_log_length);
        glGetProgramInfoLog(material, info_log_length, NULL, info_log);
        zox_log_error("Material Initializaiton Failed: material [%i] Shader [%ix%i]\n [%s]", (int) material, vert_shader, frag_shader, info_log);
        free(info_log);
        glDetachShader(material, vert_shader);
        glDetachShader(material, frag_shader);
        return 0;
    }
    glDetachShader(material, vert_shader);
    glDetachShader(material, frag_shader);
    return 0;
}

GLuint spawn_gpu_material_program(const GLuint2 shader) {
    GLuint material = glCreateProgram();
    initialize_material(material, shader.x, shader.y);
#ifdef zoxel_catch_opengl_errors
    check_opengl_error("spawn_gpu_material_program");
#endif
    return material;
}

int compile_shader(GLenum shaderType, GLuint* shader2, const GLchar* buffer) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, (const GLchar **) &buffer, NULL);
    glCompileShader(shader);
    // glValidateProgram(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        GLint info_log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar* info_log = malloc(info_log_length);
        glGetShaderInfoLog(shader, info_log_length, NULL, info_log);
        zox_log_error("-> failed to compile shader [%s]", info_log);
        free(info_log);
        return -1;
    }
    *shader2 = shader;
    return 0;
}

int load_shader(const char* filepath, GLenum shaderType, GLuint* shader2) {
    if (strlen(filepath) == 0) {
        zoxel_log("Shader Filepath is Empty.\n");
        return -1;
    }
    char* fullpath = get_full_file_path(filepath);
    GLchar *buffer = (GLchar*) SDL_LoadFile(fullpath, NULL);
    free(fullpath);
    if (!buffer) {
        zoxel_log("Loading shader (SDL_LoadFile) returned null at [%s].\n", filepath);
        return -1;
    }
    if (compile_shader(shaderType, shader2, buffer) != 0) {
        free(buffer);
        return -1;
    }
    free(buffer);
    return 0;
}

GLuint2 spawn_gpu_shader_inline(const GLchar* vert_buffer, const GLchar* frag_buffer) {
    GLuint2 shader = { 0, 0 };
    if (render_backend != zox_render_backend_opengl) {
        return shader;
    }
    if (compile_shader(GL_VERTEX_SHADER, &shader.x, vert_buffer) != 0) {
        zoxel_log("Error loading shader vert [%s]\n", vert_buffer);
        return shader;
    }
    if (compile_shader(GL_FRAGMENT_SHADER, &shader.y, frag_buffer) != 0) {
        zoxel_log("Error loading shader frag [%s]\n", frag_buffer);
        return shader;
    }
    return shader;
}

/*GLuint2 spawn_gpu_shader(const char* vertFilepath, const char* fragFilepath) {
    GLuint2 shader = { 0, 0 };
    if (render_backend != zox_render_backend_opengl) {
        return shader;
    }
    if (load_shader(vertFilepath, GL_VERTEX_SHADER, &shader.x) != 0) {
        zoxel_log("Error loading shader vert [%s]\n", vertFilepath);
        return shader;
    }
    if (load_shader(fragFilepath, GL_FRAGMENT_SHADER, &shader.y) != 0) {
        zoxel_log("Error loading shader frag [%s]\n", fragFilepath);
        return shader;
    }
    return shader;
}*/

//! For when you only need one material, otherwise will need to return shaders too. Returns material reference.
/*GLuint load_gpu_shader(GLuint2* shader, const char* vertFilepath, const char* fragFilepath) {
    if (load_shader(vertFilepath, GL_VERTEX_SHADER, &shader->x) != 0) {
        zoxel_log("Error loading shader vert [%s]\n", vertFilepath);
        return 0;
    }
    if (load_shader(fragFilepath, GL_FRAGMENT_SHADER, &shader->y) != 0) {
        zoxel_log("Error loading shader frag [%s]\n", fragFilepath);
        return 0;
    }
    return spawn_gpu_material_program((const GLuint2) { shader->x, shader->y });
}
*/