#include <GL/glew.h>

void initialize_glew() {
    glewExperimental = GL_TRUE;
    glewInit();
}