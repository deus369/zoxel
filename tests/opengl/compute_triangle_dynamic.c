// sudo apt-get install libglew-dev libglfw3-dev
// cc -std=c99 tests/opengl/compute_triangle_dynamic.c -o build/compute_triangle_dynamic -lGL -lGLEW -lglfw && ./build/compute_triangle_dynamic
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
const int triangles_generate_count = 10;
const int MAX_VERTICES = triangles_generate_count * 3;
const int compute_run_times = triangles_generate_count; // 10; // 1;
const float sky_r = 0.03f;
const float sky_g = 0.35f;
const float sky_b = 0.28f;

// Define the parameters for the indirect draw command
struct DrawArraysIndirectCommand {
    uint count;
    uint instanceCount;
    uint first;
    uint baseInstance;
} drawCommand = { MAX_VERTICES, 1, 0, 0 };
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

const char* compute_shader_source = "\
#version 430\n\
struct vec3z\
{\
    float x;\
    float y;\
    float z;\
};\
\
shared int index;\
layout(location = 0) uniform float time;\
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;\
layout(std430, binding = 0) buffer PositionBuffer {\
    vec3z vertices[];\
};\
\
float random(vec2 st) {\
    return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);\
}\
\
void main() {\
    int this_index = int(gl_WorkGroupID.x);\
    const float random_strength = 0.02;\
    const float sizex = 0.814;\
    const float sizey = 0.998;\
    float extra = float(this_index + 1) * 0.4;\
    vec2 st = vec2(float(this_index) + time, int(gl_WorkGroupID.y));\
    float random_number = 2.0 * random(st) - 1.0;\
    random_number = 0.2 + sizex * (random_strength * random_number + 0.6 * sin(time));\
    vec3z v1 = vec3z(-sizex, -sizey, 0);\
    vec3z v2 = vec3z(sizex, -sizey, 0);\
    vec3z v3 = vec3z(0, 0.3 + random_number, 0);\
    v1.x += 0.6 * random_number;\
    v2.x -= 0.6 * random_number;\
    v3.x = -0.5 + 0.1 * this_index;\
    vertices[this_index * 3] = v3;\
    vertices[this_index * 3 + 1] = v2;\
    vertices[this_index * 3 + 2] = v1;\
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

void upload_verts(uint vbo) {
    GLfloat vertices[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void run_compute_shader_debug(uint compute_program, uint vbo, uint triangle_buffer, int run_count) {
    //begin_timing_absolute()
    double time = 100.0 * get_time_seconds();
    run_compute_shader(compute_program, run_count, time);
    // glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    //end_timing("    + compute timing")
}

uint create_ibo() {
    uint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, ibo);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(drawCommand), &drawCommand, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
    return ibo;
}

uint create_simple_vbo() {
    uint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vbo;
}

uint create_count_buffer() { 
    uint countBuffer;
    glGenBuffers(1, &countBuffer);
    glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, countBuffer);
    uint zero = 0;
    glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(uint), &zero, GL_DYNAMIC_DRAW);
    return countBuffer;
}

uint create_dynamic_storage_buffer() {
    uint buffer;
    glCreateBuffers(1, &buffer);
    glNamedBufferStorage(buffer, MAX_VERTICES * 4 * 3, NULL, GL_DYNAMIC_STORAGE_BIT);
    // glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffer);
    //glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
    //int vert_count = 6;
    //glBufferData(GL_SHADER_STORAGE_BUFFER, vert_count * 3 * 4, NULL, GL_DYNAMIC_DRAW);
    check_opengl_error("create_dynamic_storage_buffer");
    return buffer;
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
    uint compute_program = setup_compute_buffer(compute_shader_source);
    uint shader_program = create_material(vertex_shader_source, fragment_shader_source);
    uint ibo = create_ibo();
    uint vbo = create_simple_vbo();
    uint triangle_buffer = create_dynamic_storage_buffer();
    attach_buffer_to_compute_program(compute_program, triangle_buffer);
    attach_buffer_to_render_program(shader_program, triangle_buffer);
    glClearColor(sky_r, sky_g, sky_b, 1.0f); //0.13f, 0.24f, 0.66f, 1.0f);

    while (loop_glfw_window(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        run_compute_shader_debug(compute_program, vbo, triangle_buffer, compute_run_times);
        indirect_render_material(shader_program, vbo, ibo);
        updated_glfw_render(window);
        update_glfw_window();
    }
    // glDeleteBuffers(1, &count_buffer);
    glDeleteBuffers(1, &triangle_buffer);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    glDeleteProgram(compute_program);
    glDeleteProgram(shader_program);
    close_glfw_window(window);
    return 0;
}