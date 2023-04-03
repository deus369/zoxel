#include <GLFW/glfw3.h>

int screen_width = 256;
int screen_height = 256;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Z) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
}

void window_pos_callback(GLFWwindow* window, int xpos, int ypos) {
    // zoxel_log("> glfw window position set to [%d, %d]\n", xpos, ypos);
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    // zoxel_log("> glfw window size set to [%d, %d]\n", width, height);
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
    // glfwWindowHint(GLFW_SAMPLES, 0);
    if (is_es) {
        printf("    > setting glfw to opengl es 3.1\n");
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    } else {
        printf("    > setting glfw to opengl api 4.6\n");
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        /*int major_version = 4;
        int minor_version = 6;
        // Check for other available versions
        if (glfwExtensionSupported("GL_ARB_ES3_2_compatibility")) {
            printf("    > setting glfw to opengl api 4.6 with ES 3.2 compatibility\n");
            major_version = 4;
            minor_version = 6;
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            // glfwWindowHint(GLFW_CONTEXT_FLAGS, GLFW_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT);
        } else if (glfwExtensionSupported("GL_ARB_compatibility")) {
            printf("    > setting glfw to opengl api 2.1 with compatibility profile\n");
            major_version = 2;
            minor_version = 1;
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
        } else {
            printf("    > setting glfw to opengl api 4.6\n");
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
            // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_DONT_CARE);
            // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_DONT_CARE);
            // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        }*/
    }
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    screen_width = mode->width;
    screen_height = mode->height;
    if (!fullscreen) {
        monitor = NULL;
        // glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE); // prevent fullscreen
        // glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
        screen_width /= 2;
        screen_height /= 2;
    }
    zoxel_log("> spawning glfw window: size [%ix%i]\n", screen_width, screen_height);
    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "gpu_compute", monitor, NULL);
    if (!window) {
        return NULL;
    }
    /*if (!fullscreen) {
        glfwSetWindowAttrib(window, GLFW_MAXIMIZED, GLFW_FALSE);
        glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    }*/
    glfwSwapInterval(1);    // vsync
    glfwMakeContextCurrent(window);
    glfwSetWindowPosCallback(window, window_pos_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetKeyCallback(window, key_callback);
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
    glfwTerminate();
    glfwDestroyWindow(window);
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