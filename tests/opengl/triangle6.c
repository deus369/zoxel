// sudo apt-get install libglew-dev libglfw3-dev
// cc -std=c99 tests/opengl/triangle6.c -o build/triangle6 -lGL -lGLEW -lglfw && ./build/triangle6
// todo: create triangle without knowing vertex_count
#define zox_logs
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../src/core/util/logs.c"
#include "../../src/core/rendering/opengl/util/error_util.c"
#include "../../src/core/rendering/opengl/util/compute_util.c"
#include "../../src/core/timing/util/time_macros.c"
#include "glfw_util.c"
#include "glew_util.c"
#include "opengl_util.c"

// 0 | 1
#define is_full_screen 1
// #define is_opengl_es 0
const int triangles_generate_count = 20;
const int MAX_VERTICES = triangles_generate_count * 3;
const int compute_run_times = triangles_generate_count;
const float sky_r = 0.03f;
const float sky_g = 0.35f;
const float sky_b = 0.28f;

// Define the parameters for the indirect draw command
typedef struct {
    GLuint count;
    GLuint instanceCount;
    GLuint first;
    GLuint baseInstance;
} DrawArraysIndirectCommand;
DrawArraysIndirectCommand drawCommand = { 0, 1, 0, 0 };

const char* compute_shader_source = "\
#version 430\n\
layout(location = 0) uniform float time_passed;\
\
struct vec3z {\
    float x;\
    float y;\
    float z;\
};\
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;\
layout(std430, binding = 0) buffer PositionBuffer {\
    vec3z vertices[];\
};\
layout(std430, binding = 1) buffer MyAtomicCounter {\
    uint counter;\
};\
struct DrawArraysIndirectCommand {\
    int count;\
    int instanceCount;\
    int first;\
    int baseInstance;\
};\
layout(std430, binding = 2) buffer DrawArraysIndirectCommandBuffer {\
    DrawArraysIndirectCommand drawCommand;\
};\
\
float random(vec2 st) {\
    return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);\
}\
\
void main() {\
    const float random_strength = 0.02;\
    const float sin_strength = 0.2;\
    const float sizex = 0.814;\
    const float sizey = 0.998;\
    vec2 st = vec2(float(gl_WorkGroupID.x) + time_passed, int(gl_WorkGroupID.y));\
    float random_addition = 2.0 * random(st) - 1.0;\
    if (gl_WorkGroupID.x > 2 && random_addition <= 0.5) return;\
    uint index = atomicAdd(counter, 3u);\
    drawCommand.count = 3;\
    random_addition = sizex * (random_strength * random_addition + sin_strength * sin(time_passed));\
    vec3z v1 = vec3z(-sizex, -sizey, 0);\
    vec3z v2 = vec3z(sizex, -sizey, 0);\
    vec3z v3 = vec3z(0, 0.4 + random_addition, 0);\
    v3.x = -0.5 + 0.1 * int(index / 3);\
    vertices[index] = v3;\
    vertices[index + 1] = v2;\
    vertices[index + 2] = v1;\
    atomicAdd(drawCommand.count, 3);\
}";
const char* vertex_shader_source = "\
#version 310 es\n\
layout(location = 0) in lowp vec4 position;\
void main()\
{\
    gl_Position = position;\
}";
const char* fragment_shader_source = "\
#version 310 es\n\
out lowp vec4 fragColor;\
void main()\
{\
    fragColor = vec4(0.47f, 0.03f, 0.03f, 1.0f);\
}";

// not needed !
void manual_update_vertex_count(GLuint count_buffer, GLuint ibo) {
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
}

void run_compute_shader_debug(GLuint compute_program, GLuint triangle_buffer, GLuint count_buffer, GLuint ibo, int run_count) {
    begin_timing_absolute()
    // double time_passed = 100.0 * get_time_seconds();
    double time_passed = get_time_seconds();
    glUseProgram(compute_program);
    GLuint time_attribute = 0; // glGetUniformLocation(triangle_buffer, "time_passed");
    glUniform1f(time_attribute, (float) time_passed);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, triangle_buffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, count_buffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, ibo);
    GLuint zero = 0;
    glClearBufferData(GL_ATOMIC_COUNTER_BUFFER, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, &zero);
    glDispatchCompute(run_count, 1, 1);
    // manual_update_vertex_count(count_buffer, ibo);
    glUseProgram(0);
    // check_opengl_error("run_compute_shader_debug");
    // zoxel_log("time_passed [%f]\n", (float) time_passed);
    end_timing("    + compute timing")
}

GLuint create_simple_vbo() {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vbo;
}

// used for commands
GLuint create_ibo() {
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, ibo);
    DrawArraysIndirectCommand drawCommand = { 0, 1, 0, 0 };
    glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(drawCommand), &drawCommand, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
    return ibo;
}

GLuint create_ssbo(int max_size) {
    GLuint buffer;
    glCreateBuffers(1, &buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, max_size, NULL, GL_DYNAMIC_DRAW);
    check_opengl_error("create_dynamic_storage_buffer");
    return buffer;
}

GLuint create_count_buffer() { 
    GLuint countBuffer;
    glGenBuffers(1, &countBuffer);
    glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, countBuffer);
    GLuint zero = 0;
    glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), &zero, GL_DYNAMIC_DRAW);
    return countBuffer;
}

GLuint create_command_buffer() {
    GLuint command_buffer;
    glGenBuffers(1, &command_buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, command_buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(DrawArraysIndirectCommand), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    return command_buffer;
}

int main(int argc, char *argv[]) {
    unsigned char is_es = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--opengles") == 0) {
            printf("    > enabling [opengles]\n");
            is_es = 1;
            break;
        }
    }
    print_supported_renderer_drivers();
    GLFWwindow* window = open_glfw_window(is_es, is_full_screen);
    initialize_glew();
    print_opengl_version();
    // print_opengl_extensions();
    int supports_compute = check_compute_shader_support();
    if (supports_compute == EXIT_FAILURE) {
        printf("    - compute shaders is not supported\n");
        close_glfw_window(window);
        return 1;
    }
    printf("    + compute shaders are supported\n");
    if (is_indirect_supported() == EXIT_FAILURE) {
        printf("    - indirect opengl rendering is not supported\n");
        close_glfw_window(window);
        return 1;
    }
    printf("    + indirect rendering is supported\n");
    glClearColor(sky_r, sky_g, sky_b, 1.0f); //0.13f, 0.24f, 0.66f, 1.0f);
    GLuint compute_program = setup_compute_buffer(compute_shader_source);
    GLuint shader_program = create_material(vertex_shader_source, fragment_shader_source);
    GLuint ibo = create_ibo();
    GLuint vbo = create_simple_vbo();
    GLuint count_buffer = create_count_buffer();
    GLuint triangle_buffer = create_ssbo(MAX_VERTICES * 3 * 4);
    attach_buffer_to_compute_program(compute_program, triangle_buffer);
    attach_buffer_to_render_program(shader_program, triangle_buffer);
    while (loop_glfw_window(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        run_compute_shader_debug(compute_program, triangle_buffer, count_buffer, ibo, compute_run_times);
        indirect_render_material(shader_program, vbo, ibo);
        updated_glfw_render(window);
        update_glfw_window();
    }
    glDeleteBuffers(1, &count_buffer);
    glDeleteBuffers(1, &triangle_buffer);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    glDeleteProgram(compute_program);
    glDeleteProgram(shader_program);
    close_glfw_window(window);
    return 0;
}

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