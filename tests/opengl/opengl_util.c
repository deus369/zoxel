const int position_pack_size = 3;

// a simple 3D point
typedef struct {
    float x;
    float y;
    float z;
} vec3;

int check_new_shader(uint compute_program) {
    // debug compute_program linking
    GLint link_status;
    glGetProgramiv(compute_program, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE) {
        GLint log_length;
        glGetProgramiv(compute_program, GL_INFO_LOG_LENGTH, &log_length);
        char* log = (char*) malloc(log_length * sizeof(char));
        glGetProgramInfoLog(compute_program, log_length, NULL, log);
        zoxel_log("Compute shader program failed to link: %s\n", log);
        free(log);
        return 1;
    }
    check_opengl_error("check_new_shader");
    return 0;
}

// creates a simple unlit material
uint create_material(const char* vertex_shader_source, const char* fragment_shader_source) {
    uint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    uint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    uint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    check_opengl_error("create_material");
    return shader_program;
}

// Set up compute shader
uint setup_compute_buffer(const char* compute_shader_source) {
    uint compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compute_shader, 1, &compute_shader_source, NULL);
    glCompileShader(compute_shader);
    uint compute_program = glCreateProgram();
    glAttachShader(compute_program, compute_shader);
    glLinkProgram(compute_program);
    glDeleteShader(compute_shader);
    check_opengl_error("setup_compute_buffer");
    check_new_shader(compute_program);
    return compute_program;
}

// connects a material to a buffer
void attach_buffer_to_compute_program(uint material, uint buffer) {
    glUseProgram(material);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffer);
    glUseProgram(0);
    check_opengl_error("attach_buffer_to_compute_program");
}

void attach_buffer_to_render_program(uint render_program, uint buffer) {
    glUseProgram(render_program);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexAttribPointer(0, position_pack_size, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glUseProgram(0);
    check_opengl_error("attach_buffer_to_render_program");
}

uint create_vertex_buffer(uint shader_program, int vertex_count, int single_data_length) {
    const uint position_attrib = 0;
    uint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(position_attrib);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * single_data_length, NULL, GL_STATIC_DRAW);
    glVertexAttribPointer(position_attrib, position_pack_size, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    check_opengl_error("create_vertex_buffer");
    return vbo;
}

// position buffer used for vertex positions
uint setup_storage_buffer(int length) {
    uint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, length, NULL, GL_DYNAMIC_DRAW);
    check_opengl_error("setup_compute_buffer");
    return buffer;
}

void copy_buffer_to_render_shader(uint vbo, uint buffer, uint variable_index, int data_length) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(variable_index);
    glBindBuffer(GL_COPY_WRITE_BUFFER, buffer);
    glCopyBufferSubData(GL_COPY_WRITE_BUFFER, GL_ARRAY_BUFFER, 0, 0, data_length);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // check_opengl_error("create_vertex_buffer");
}

// Dispatch compute shader to generate vertex positions
void run_compute_shader(uint compute_program, int run_count_x, double time) {
    // double time_atm = (double) ((int) get_time_seconds());
    glUseProgram(compute_program);
    const uint time_attribute = 0;
    glUniform1f(time_attribute, time);
    glDispatchCompute(run_count_x, 1, 1);
    // glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    glUseProgram(0);
    // check_opengl_error("run_compute_shader");
}

void render_material(uint shader_program, uint vbo, int vertex_count) {
    glUseProgram(shader_program);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
    check_opengl_error("render_material");
}

unsigned char is_indirect_supported() {
    const char* extensions = (const char*) glGetString(GL_EXTENSIONS);
    if (extensions == NULL) {
        return EXIT_FAILURE;
    }
    if (// strstr(extensions, "GL_EXT_draw_instanced") != NULL &&
        strstr(extensions, "GL_ARB_draw_indirect") != NULL) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}

void print_opengl_version () {
    const char* version = (const char*) glGetString(GL_VERSION);
    printf("    > OpenGL version [%s]\n", version);
}

void print_opengl_extensions() {
    const char* extensions = (const char*) glGetString(GL_EXTENSIONS);
    if (!extensions) {
        printf("    - Error: Could not retrieve OpenGL extensions.\n");
        return;
    }
    printf("    > OpenGL extensions:\n");
    // Iterate through the extensions string and print each extension
    const char* start = extensions;
    const char* end;
    while (*start) {
        end = start;
        while (*end && *end != ' ') {
            end++;
        }
        printf("        - %.*s\n", (int)(end - start), start);
        start = (*end) ? (end + 1) : end;
    }
}