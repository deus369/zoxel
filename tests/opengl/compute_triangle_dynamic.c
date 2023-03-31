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

#define is_full_screen 1 // 0 | 1
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
    fragColor = vec4(0.42f, 0.10f, 0.10f, 1.0f);\
}";
const char* compute_shader_source = "\
#version 310 es\n\
layout(location = 0) uniform float time;\
struct vec3z\
{\
    float x;\
    float y;\
    float z;\
};\
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;\
layout(std430, binding = 0) buffer PositionBuffer {\
    vec3z positions[];\
};\
float random(vec2 st) {\
    return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);\
}\
void main() {\
    float size = 0.98;\
    int index = int(gl_WorkGroupID.x);\
    vec2 st = vec2(float(int(gl_WorkGroupID.x)) + time, int(gl_WorkGroupID.y));\
    float random_number = 2.0 * random(st) - 1.0;\
    random_number = 0.2 + size * (0.04 * random_number + 0.6 * sin(time));\
    vec3z position;\
    if (index == 0) {\
        position = vec3z(-size, -size, 0.0);\
    } else if (index == 1) {\
        position = vec3z(size, -size, 0.0);\
    } else if (index == 2) {\
        position = vec3z(0.0, random_number, 0.0);\
    }\
    positions[index] = position;\
}";

void run_compute_shader_debug(GLuint compute_program, GLuint vbo, GLuint position_buffer, int data_length, int vertex_count) {
    begin_timing_absolute()
    zoxel_log("    > Running compute\n");
    double time = 100.0 * get_time_seconds();
    zoxel_log("        > current time [%d]\n", time);
    run_compute_shader(compute_program, vertex_count, time);
    // copy_buffer_to_render_shader(vbo, position_buffer, 0, data_length);
    end_timing("        > trigger compute time")
}

int main() {
    const int vertex_count = 3;
    const int single_data_length = 3 * 4;    // 24 * 16
    const int data_length = vertex_count * 3 * 4;    // 24 * 16
    GLFWwindow* window = open_glfw_window(1, is_full_screen);
    initialize_glew();
    int supports_compute = check_compute_shader_support();
    if (supports_compute == EXIT_FAILURE) {
        close_glfw_window(window);
        return 1;
    }
    GLuint position_buffer = setup_storage_buffer(data_length);
    GLuint compute_program = setup_compute_buffer(compute_shader_source);
    attach_buffer_to_compute_program(compute_program, position_buffer);
    GLuint shader_program = create_material(vertex_shader_source, fragment_shader_source);
    GLuint vbo = create_vertex_buffer(shader_program, vertex_count, single_data_length);
    attach_buffer_to_render_program(shader_program, position_buffer);
    // Use shader program and bind vertex buffer for rendering
    while (loop_glfw_window(window)) {
        glClearColor(0.13f, 0.24f, 0.66f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        run_compute_shader_debug(compute_program, vbo, position_buffer, data_length, vertex_count);
        render_material(shader_program, vbo, vertex_count);
        updated_glfw_render(window);
        update_glfw_window();
    }
    glDeleteBuffers(1, &position_buffer);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader_program);
    glDeleteProgram(compute_program);
    close_glfw_window(window);
    return 0;
}