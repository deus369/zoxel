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
#include "glfw_util.c"
#include "glew_util.c"
#include "opengl_util.c"
#include "../../src/core/timing/util/time_macros.c"

// #define debug_triangle6_timing
#define is_full_screen 0            // 0 | 1
const int MAX_VERTICES = 3000;      // MAX_VERTICES / 3 = total triangles;
const int compute_run_times = 72;
const float sky_r = 69.0f / 255.0f;
const float sky_g = 112.0f / 255.0f;
const float sky_b = 122.0f / 255.0f;
double time_passed = 0.0;
double update_rate = 0.06;
double last_time_passed = -666;

struct vec3{
    float x;
    float y;
    float z;
};

typedef struct {
    GLuint count;
    GLuint instanceCount;
    GLuint first;
    GLuint baseInstance;
} DrawArraysIndirectCommand;

const char* compute_shader_source = "\
#version 430\n\
const uint MAX_VERTICES = 3000;\
const float random_strength = 0.02;\
const float sizex = 1.6;\
const float sizey = 1.0;\
const float size_per_index = 0.04f;\
const float sin_speed = 40.0f;\
const float sin_strength = 0.42;\
const float add_y = 0.1;\
\
struct vec3z {\
    float x;\
    float y;\
    float z;\
};\
struct DrawArraysIndirectCommand {\
    uint count;\
    int instanceCount;\
    int first;\
    int baseInstance;\
};\
\
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;\
layout(location = 0) uniform float time_passed;\
layout(std430, binding = 0) buffer PositionBuffer {\
    vec3z vertices[];\
};\
layout(std430, binding = 1) buffer DrawArraysIndirectCommandBuffer {\
    DrawArraysIndirectCommand drawCommand;\
};\
\
float random(vec2 st) {\
    return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);\
}\
\
void main() {\
    vec2 st = vec2(float(gl_WorkGroupID.x) + time_passed, int(gl_WorkGroupID.y) - time_passed);\
    float random_add = 2.0 * random(st) - 1.0;\
    if (random_add < 0) random_add = -random_add;\
    if (random_add < 0.86) return;\
    if (drawCommand.count + 3u > MAX_VERTICES) return;\
    uint index = atomicAdd(drawCommand.count, 3u);\
    float sin_add = sin_strength * sin(sin_speed * time_passed);\
    random_add = random_strength * random_add;\
    vec3z v1 = vec3z(-sizex + random_add, -sizey, 0);\
    vec3z v2 = vec3z(sizex - random_add, -sizey, 0);\
    vec3z v3 = vec3z(0, add_y + sin_add + random_add, 0);\
    if (index % 2 == 0) v3.x = size_per_index * int(index / 3);\
    else v3.x = - size_per_index * int(index / 3);\
    v3.y -= 0.006 * int(index / 3);\
    vertices[index] = v3;\
    vertices[index + 1] = v2;\
    vertices[index + 2] = v1;\
    drawCommand.instanceCount = 1;\
}";

const char* vertex_shader_source = "\
#version 310 es\n\
layout(location = 0) in lowp vec4 position;\
\
void main() {\
    gl_Position = position;\
}";

const char* fragment_shader_source = "\
#version 310 es\n\
out lowp vec4 fragColor;\
\
void main() {\
    fragColor = vec4(71.0f / 255.0f, 48.0f / 255.0f, 28.0f / 255.0f, 1.0f);\
}";

void clear_triangle_buffer(GLuint triangle_buffer) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, triangle_buffer);
    glClearBufferData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, GL_RED, GL_UNSIGNED_INT, NULL);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void clear_ibo(GLuint ibo) {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ibo);
    glClearBufferData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, GL_RED, GL_UNSIGNED_INT, NULL);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void run_compute_shader_2(GLuint compute_program, GLuint triangle_buffer, GLuint ibo, int run_count) {
    #ifdef debug_triangle6_timing
        begin_timing_absolute()
    #endif
    clear_triangle_buffer(triangle_buffer);
    clear_ibo(ibo);
    glUseProgram(compute_program);
    GLuint time_attribute = 0; // glGetUniformLocation(triangle_buffer, "time_passed");
    glUniform1f(time_attribute, (float) get_time_seconds());
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, triangle_buffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ibo);
    glDispatchCompute(run_count, 1, 1);
    glUseProgram(0);
    check_opengl_error("run_compute_shader_2");
    #ifdef debug_triangle6_timing
        end_timing("    + compute timing")
    #endif
}

GLuint create_ibo() {
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, ibo);
    DrawArraysIndirectCommand drawCommand = { 0, 1, 0, 0 };
    glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(drawCommand), &drawCommand, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
    check_opengl_error("create_ibo");
    return ibo;
}

GLuint create_ssbo(int bytes_allocated) {
    GLuint buffer;
    glCreateBuffers(1, &buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, bytes_allocated, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    check_opengl_error("create_ssbo");
    return buffer;
}

void indirect_render_material(GLuint shader_program, GLuint ibo) {
    glUseProgram(shader_program);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, ibo);
    glDrawArraysIndirect(GL_TRIANGLES, 0);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
    glUseProgram(0);
    check_opengl_error("indirect_render_material glDrawArraysIndirect");
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
    GLuint ssbo = create_ssbo(MAX_VERTICES * sizeof(vec3));
    attach_buffer_to_compute_program(compute_program, ssbo);
    attach_buffer_to_render_program(shader_program, ssbo);
    GLuint ibo = create_ibo();
    while (loop_glfw_window(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        time_passed = get_time_seconds() * 100;
        // printf("time_passed: %f\n", (float) time_passed);
        if (time_passed - last_time_passed >= update_rate) {
            last_time_passed = time_passed;
            // printf("last time: %f\n", (float) last_time_passed);
            run_compute_shader_2(compute_program, ssbo, ibo, compute_run_times);
        }
        indirect_render_material(shader_program, ibo);
        updated_glfw_render(window);
        update_glfw_window();
    }
    glDeleteBuffers(1, &ssbo);
    glDeleteBuffers(1, &ibo);
    glDeleteProgram(compute_program);
    glDeleteProgram(shader_program);
    close_glfw_window(window);
    return 0;
}