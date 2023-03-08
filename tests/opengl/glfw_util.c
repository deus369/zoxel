#include <GL/glew.h>
#include <GLFW/glfw3.h>

int render_dirty = 1;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
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
    glfwSetWindowMonitor(window, NULL, 0, 0, 256, 256, GLFW_DONT_CARE);
}

void check_glfw() {
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    printf("GLFW version: %d.%d.%d\n", major, minor, rev);
}

GLFWwindow* open_glfw_window(int is_es, int fullscreen) {
    if (!glfwInit()) {
        return NULL;
    }
    if (is_es) {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    }
    glfwSwapInterval(1);    // vsync
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE); // prevent fullscreen
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    // glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    int screen_width = 256; // mode->width / 2;
    int screen_height = 256; // mode->height / 2;
    printf("Spawning GLFW window with size [%ix%i]\n", screen_width, screen_height);
    // "Compute Test"
    if (fullscreen == 0) {
        monitor = NULL;
    }
    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "", monitor, NULL); //  , NULL);
    if (!window)
    {
        return NULL;
    }
    // Set the key callback function
    glfwSetKeyCallback(window, key_callback);
    // glfwSetWindowSize(window, 202, 202);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    glfwSetWindowAttrib(window, GLFW_MAXIMIZED, GLFW_FALSE);
    glfwSetWindowMonitor(window, NULL, 0, 0, screen_width, screen_height, GLFW_DONT_CARE);
    glfwSetWindowPosCallback(window, window_pos_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glewInit();
    check_opengl_error("setup_window");
    // Wait for all previously issued commands to complete
    glFinish();
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

void close_glfw_window() {
    glfwTerminate();
}