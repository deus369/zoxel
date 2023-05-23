#include <stdio.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
// cc -std=c99 tests/opengl/indirect_triangle.c -o build/indirect_triangle -lGL -lglut && ./build/indirect_triangle

struct DrawArraysIndirectCommand {
    GLint count;
    GLint instanceCount;
    GLint first;
    GLint baseInstance;
};

struct IndirectRenderData {
    uint vbo;
    uint command_buffer;
    struct DrawArraysIndirectCommand command;
    GLfloat vertices[];
};

struct IndirectRenderData indirect_render_data = { 0, 0, { 3, 1, 0, 0 }, { 0.0f,  0.5f, 0.5f, -0.5f, -0.5f, -0.5f } };

void init_indirect_renderer() {
    glGenBuffers(1, &indirect_render_data.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, indirect_render_data.vbo);
    glBufferData(GL_ARRAY_BUFFER, 6 * 4, indirect_render_data.vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Draw the triangle using the indirect draw command
    glGenBuffers(1, &indirect_render_data.command_buffer);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirect_render_data.command_buffer);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(indirect_render_data.command), &indirect_render_data.command, GL_STATIC_DRAW);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
}

void clean_indirect_renderer() {
    glDeleteBuffers(1, &indirect_render_data.vbo);
    glDeleteBuffers(1, &indirect_render_data.command_buffer);
}

void display_indirect_renderer() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindBuffer(GL_ARRAY_BUFFER, indirect_render_data.vbo);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirect_render_data.command_buffer);
    glDrawArraysIndirect(GL_TRIANGLES, 0);
    glDisableVertexAttribArray(0);
}

void display() {
    display_indirect_renderer();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Indirect Triangle Example");
  init_indirect_renderer();
  glutDisplayFunc(display);
  glutMainLoop();
  clean_indirect_renderer();
  return 0;
}