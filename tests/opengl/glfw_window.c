// cc -std=c99 tests/opengl/glfw_window.c -o build/glfw_window -lGL -lGLEW -lglfw && ./build/glfw_window
#include <GLFW/glfw3.h>
#include "../../src/core/util/logs.c"
#include "../../src/core/generic/util/time_macros.c"
#include "glfw_util.c"

int main() {
    GLFWwindow* window = open_glfw_window(1, 0);
    while (loop_glfw_window(window)) {
        glClearColor(0.13f, 0.24f, 0.66f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        updated_glfw_render(window);
        update_glfw_window();
    }
    close_glfw_window(window);
    return 0;
}