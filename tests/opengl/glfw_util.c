#include <GL/glew.h>
#include <GLFW/glfw3.h>

int screen_width = 256;
int screen_height = 256;

extern void action_a();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Z)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        else if (key == GLFW_KEY_X)
            action_a();
    }
}


void window_pos_callback(GLFWwindow* window, int xpos, int ypos)
{
    zoxel_log("> glfw window position set to [%d, %d]\n", xpos, ypos);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    zoxel_log("> glfw window size set to [%d, %d]\n", width, height);
}

void check_glfw() {
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    zoxel_log("> glfw version [%d.%d.%d]\n", major, minor, rev);
}

GLFWwindow* open_glfw_window(int is_es, int fullscreen) {
    check_glfw();
    if (!glfwInit()) {
        return NULL;
    }
    glfwWindowHint(GLFW_SAMPLES, 0);
    if (is_es) {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    }
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    screen_width = mode->width;
    screen_height = mode->height;
    if (!fullscreen)
    {
        monitor = NULL;
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE); // prevent fullscreen
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    }
    zoxel_log("> spawning glfw window: size [%ix%i]\n", screen_width, screen_height);
    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "gpu_compute", monitor, NULL);
    if (!window)
    {
        return NULL;
    }
    if (!fullscreen)
    {
        glfwSetWindowAttrib(window, GLFW_MAXIMIZED, GLFW_FALSE);
        glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    }
    glfwSwapInterval(1);    // vsync
    glfwMakeContextCurrent(window);
    // call backs
    glfwSetWindowPosCallback(window, window_pos_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetKeyCallback(window, key_callback);
    // opengl
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
// glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);