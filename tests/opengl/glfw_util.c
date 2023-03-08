#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* open_glfw_window(int is_es) {
    if (!glfwInit()) {
        return NULL;
    }
    if (is_es) {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    }
    GLFWwindow* window = glfwCreateWindow(600, 420, "Compute Simpler", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    check_opengl_error("setup_window");
    // Wait for all previously issued commands to complete
    glFinish();
    return window;
}

void update_glfw_window(GLFWwindow* window) {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

int loop_glfw_window(GLFWwindow* window) {
    return !glfwWindowShouldClose(window);
}

void close_glfw_window() {
    glfwTerminate();
}