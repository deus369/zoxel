const int position_pack_size = 3;

// a simple 3D point
typedef struct {
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

void attach_buffer_to_render_program(GLuint render_program, GLuint buffer) {
    glUseProgram(render_program);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexAttribPointer(0, position_pack_size, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glUseProgram(0);
    check_opengl_error("attach_buffer_to_render_program");
}

GLuint create_vertex_buffer(GLuint shader_program, int vertex_count, int single_data_length) {
    const GLuint position_attrib = 0;
    GLuint vbo;
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
void run_compute_shader(GLuint compute_program, int run_count_x, double time) {
    // double time_atm = (double) ((int) get_time_seconds());
    glUseProgram(compute_program);
    const GLuint time_attribute = 0;
    glUniform1f(time_attribute, time);
    glDispatchCompute(run_count_x, 1, 1);
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

//glVertexAttribPointer(position_attrib, vertex_count, GL_FLOAT, GL_FALSE, single_data_length, (void*) 0);
// GLuint position_attrib = glGetAttribLocation(shader_program, "position");
// zoxel_log("    > position attrib [%i]\n", position_attrib);

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



/*GLuint create_vbo() {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    check_opengl_error("create_vbo");
    return vbo;
}*/
// glBindBuffer(GL_ARRAY_BUFFER, vbo);
// glBindBuffer(GL_ARRAY_BUFFER, 0);
// GLuint vbo = create_vbo();
// glDeleteBuffers(1, &vbo);
// not needed !
// manual_update_vertex_count(count_buffer, ibo);
/*void manual_update_vertex_count(GLuint count_buffer, GLuint ibo) {
    // Make sure the compute shader has finished executing before we read the counter value
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    // Read the counter value from the SSBO
    GLuint vertex_count;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, count_buffer);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(GLuint), &vertex_count);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    // Update the draw command with the vertex count
    drawCommand.count = vertex_count;
    // printf("new vertex count found from buffer: %i\n", vertex_count);
    // Bind the indirect buffer and update it with the new draw command
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, ibo);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(drawCommand), &drawCommand, GL_DYNAMIC_DRAW);
    // glBufferSubData(GL_DRAW_INDIRECT_BUFFER, 0, sizeof(drawCommand), &drawCommand);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
    // DrawArraysIndirectCommand commandBuffer;
    // glBindBuffer(GL_SHADER_STORAGE_BUFFER, count_buffer);
    // glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 2, sizeof(DrawArraysIndirectCommand), &commandBuffer);
    // printf("new count %i\n", commandBuffer.count);
}*/

/*void upload_verts(GLuint vbo) {
    GLfloat vertices[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}*/

// GLuint vbo = create_vertex_buffer(shader_program, vertex_count, single_data_length);
// upload_verts(vbo);

// Generate a vertex buffer object (VBO)
/*glGenBuffers(1, &vbo);
glBindBuffer(GL_ARRAY_BUFFER, vbo);
// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);*/

/*GLuint create_ssbo(int max_size) {
    GLuint ssbo;
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, max_size, NULL, GL_DYNAMIC_DRAW);
    return ssbo;
}*/

    // Bind the SSBO to a binding point (e.g., binding point 0)
    /*glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, count_buffer);
    // Update the vertex count in the SSBO
    GLuint* count_ptr = (GLuint*) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, sizeof(GLuint), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    // *count_ptr = vertex_count; // set the vertex count to whatever value you need
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, ibo);
    DrawArraysIndirectCommand* drawCommand = (DrawArraysIndirectCommand*)glMapBufferRange(GL_DRAW_INDIRECT_BUFFER, 0, sizeof(DrawArraysIndirectCommand), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    // Update the vertex count in the draw command
    drawCommand->count = *count_ptr;

    // Unmap the IBO buffer
    glUnmapBuffer(GL_DRAW_INDIRECT_BUFFER);
    // Bind the IBO
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);*/

    /*GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, ibo);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);*/

    // glNamedBufferStorage(buffer, MAX_VERTICES * 4 * 3, NULL, GL_DYNAMIC_STORAGE_BIT);
    // glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffer);
    // glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
    // int vert_count = 6;
    // glBufferData(GL_SHADER_STORAGE_BUFFER, vert_count * 3 * 4, NULL, GL_DYNAMIC_DRAW);

// 3 | 0
// , offset = 0
// layout(binding = 1) uniform atomic_uint triangle_count;
// #extension GL_ARB_shader_printf : enable\n
// if (gl_LocalInvocationIndex == 0) printf(\"Final counter value: %u\n\", sharedCounter);
// atomicAdd(index, 1);
// memoryBarrierShared();
// shared int index;
// int index = int(gl_WorkGroupID.x);
// uint index = atomicCounterIncrement(triangle_count);
// if (gl_WorkGroupID.x == 0) index = 20;
// int this_index = index;
// index = index + 1;
//  * random_addition
// v1.x += 0.5;
// v2.x -= 0.5;  + random_addition

/*GLuint create_command_buffer() {
    GLuint command_buffer;
    glGenBuffers(1, &command_buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, command_buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(DrawArraysIndirectCommand), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    return command_buffer;
}*/

// DrawArraysIndirectCommand drawCommand = { 0, 1, 0, 0 };
// atomicAdd(counter, 3u);
/*layout(std430, binding = 1) buffer MyAtomicCounter {
    uint counter;
};
GLuint count_buffer = create_count_buffer();
count_buffer, 
glDeleteBuffers(1, &count_buffer);

void clear_atomic_buffer_data(GLuint count_buffer) {
    glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, count_buffer);
    glClearBufferData(GL_ATOMIC_COUNTER_BUFFER, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0); 
}

GLuint create_count_buffer() { 
    GLuint countBuffer;
    GLuint zero = 0;
    glGenBuffers(1, &countBuffer);
    glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 1, countBuffer);
    glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), &zero, GL_DYNAMIC_DRAW);
    check_opengl_error("create_count_buffer");
    return countBuffer;
}
// clear_atomic_buffer_data(count_buffer); GLuint count_buffer, 
// glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, count_buffer);
*/