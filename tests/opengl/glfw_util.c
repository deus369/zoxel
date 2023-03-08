#include <GL/glew.h>
#include <GLFW/glfw3.h>

int render_dirty = 1;
int screen_width = 256;
int screen_height = 256;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}


void window_pos_callback(GLFWwindow* window, int xpos, int ypos)
{
    printf("Window position: %d, %d\n", xpos, ypos);
    render_dirty = 1;
    // glfwSetWindowMonitor(window, NULL, 0, 0, 420, 420, GLFW_DONT_CARE);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    printf("Window size: %d x %d\n", width, height);
    render_dirty = 1;
    // glfwSetWindowMonitor(window, NULL, 0, 0, screen_width, screen_height, GLFW_DONT_CARE);
}

void check_glfw() {
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    printf("GLFW version: %d.%d.%d\n", major, minor, rev);
}

GLFWwindow* open_glfw_window(int is_es, int fullscreen) {
    check_glfw();
    if (!glfwInit()) {
        return NULL;
    }
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE); // prevent fullscreen
    glfwWindowHint(GLFW_SAMPLES, 0);
    if (is_es) {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    }
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    // glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    screen_width = mode->width;
    screen_height = mode->height;
    printf("Spawning GLFW window with size [%ix%i]\n", screen_width, screen_height);
    // "Compute Test"
    // if (fullscreen == 0)
    {
        // monitor = NULL;
        // screen_width /= 2;
        // screen_height /= 2;
    }
    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "", NULL, NULL);
    if (!window)
    {
        return NULL;
    }
    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    glfwSetWindowAttrib(window, GLFW_MAXIMIZED, GLFW_FALSE);
    glfwSwapInterval(1);    // vsync
    glfwMakeContextCurrent(window);
    // Set the key callback function
    glfwSetWindowPosCallback(window, window_pos_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetKeyCallback(window, key_callback);
    // Wait for all previously issued commands to complete
    glewExperimental = GL_TRUE;
    glewInit();
    check_opengl_error("setup_window");
    return window;
}

void updated_glfw_render(GLFWwindow* window) {
    glfwSwapBuffers(window);
}

void update_glfw_window() {
    glfwPollEvents();
}

int loop_glfw_window(GLFWwindow* window) {
    return !glfwWindowShouldClose(window);
}

void close_glfw_window(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

// glfwSetWindowMonitor(window, NULL, 0, 0, screen_width, screen_height, GLFW_DONT_CARE);
// glfwSetWindowSize(window, 202, 202);
// glFinish();
    /*
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_REFRESH_RATE, 30); // Max 30 fps
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE); // Always on top
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    */