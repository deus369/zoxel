// a simple 3D point
typedef struct
{
    float x;
    float y;
    float z;
} vec3;

int check_new_shader(GLuint compute_program) {
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
GLuint create_material(const char* vertex_shader_source, const char* fragment_shader_source) {
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    check_opengl_error("create_material");
    return shader_program;
}

// Set up compute shader
GLuint setup_compute_buffer(const char* compute_shader_source) {
    GLuint compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compute_shader, 1, &compute_shader_source, NULL);
    glCompileShader(compute_shader);
    GLuint compute_program = glCreateProgram();
    glAttachShader(compute_program, compute_shader);
    glLinkProgram(compute_program);
    glDeleteShader(compute_shader);
    check_opengl_error("setup_compute_buffer");
    check_new_shader(compute_program);
    return compute_program;
}

// connects a material to a buffer
void attach_buffer_to_compute_program(GLuint material, GLuint buffer) {
    glUseProgram(material);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffer);
    glUseProgram(0);
    check_opengl_error("attach_buffer_to_compute_program");
}

GLuint create_vertex_buffer(GLuint shader_program, int vertex_count, int single_data_length) {
    const GLuint position_attrib = 0; // glGetAttribLocation(shader_program, "position");
    GLuint vbo = 0;
    zoxel_log("    > position attrib [%i]\n", position_attrib);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(position_attrib);
    // Copy vertex data to buffer
    glBufferData(GL_ARRAY_BUFFER, vertex_count * single_data_length, NULL, GL_DYNAMIC_DRAW);
    // Set up vertex attributes
    glVertexAttribPointer(position_attrib, vertex_count, GL_FLOAT, GL_FALSE, single_data_length, (void*) 0);
    // Unbind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    check_opengl_error("create_vertex_buffer");
    return vbo;
}

// position buffer used for vertex positions
GLuint setup_storage_buffer(int length) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, length, NULL, GL_DYNAMIC_DRAW);
    check_opengl_error("setup_compute_buffer");
    return buffer;
}

void copy_buffer_to_render_shader(GLuint vbo, GLuint buffer, GLuint variable_index, int data_length) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(variable_index);
    glBindBuffer(GL_COPY_WRITE_BUFFER, buffer);
    glCopyBufferSubData(GL_COPY_WRITE_BUFFER, GL_ARRAY_BUFFER, 0, 0, data_length);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // check_opengl_error("create_vertex_buffer");
}

// Dispatch compute shader to generate vertex positions
void run_compute_shader(GLuint compute_program, int vertex_count, double time) {
    // double time_atm = (double) ((int) get_time_seconds());
    glUseProgram(compute_program);
    const GLuint time_attribute = 0;
    glUniform1f(time_attribute, time);
    glDispatchCompute(vertex_count, 1, 1);
    // glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    glUseProgram(0);
    // check_opengl_error("run_compute_shader");
}

void render_material(GLuint shader_program, GLuint vbo, int vertex_count) {
    glUseProgram(shader_program);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
    // check_opengl_error("render_material");
}