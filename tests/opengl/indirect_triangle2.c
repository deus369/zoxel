// cc -std=c99 tests/opengl/indirect_triangle2.c -o build/indirect_triangle2 -lGL -lGLEW -lglfw && ./build/indirect_triangle2
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Define the parameters for the indirect draw command
struct DrawArraysIndirectCommand {
    uint count;
    uint instanceCount;
    uint first;
    uint baseInstance;
} drawCommand = { 3, 1, 0, 0 };

int main() {
    GLFWwindow* window;
    if (!glfwInit()) {
        return -1;
    }
    /*glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);*/
    window = glfwCreateWindow(640, 480, "Triangle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }

    // Define the vertices of the triangle
    GLfloat vertices[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    // Generate a vertex buffer object (VBO)
    uint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Generate an indirect buffer object (IBO)
    uint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, ibo);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(drawCommand), &drawCommand, GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArraysIndirect(GL_TRIANGLES, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    glfwTerminate();
    return 0;
}