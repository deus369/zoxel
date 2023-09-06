// gcc tests/glut/test_pp.c -o build/test_pp -lglut -lGL -lGLU && ./build/test_pp
#include <GL/glut.h>

// Shaders
const char* vertexShaderSource = R"(
    void main() {
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        gl_TexCoord[0] = gl_MultiTexCoord0;
    }
)";

const char* fragmentShaderSource = R"(
    uniform sampler2D renderedTexture;
    void main() {
        vec2 texCoord = gl_TexCoord[0].xy;
        vec4 color = texture2D(renderedTexture, texCoord);
        
        // Apply post-processing effect
        // Example: Invert colors
        color.rgb = vec3(1.0) - color.rgb;
        
        gl_FragColor = color;
    }
)";

GLuint renderedTexture;
GLuint postProcessingShader;

void display() {
    // Render scene to a texture
    glBindFramebuffer(GL_FRAMEBUFFER, renderedTexture);
    glViewport(0, 0, 800, 600);
    // Render your scene here
    
    // Use the post-processing shader
    glUseProgram(postProcessingShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 800, 600);
    
    // Render a full-screen quad
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(-1, -1);
    glTexCoord2f(1, 0);
    glVertex2f(1, -1);
    glTexCoord2f(1, 1);
    glVertex2f(1, 1);
    glTexCoord2f(0, 1);
    glVertex2f(-1, 1);
    glEnd();
    
    // Swap buffers
    glutSwapBuffers();
}

void initialize() {
    // Create a texture for rendering
    glGenTextures(1, &renderedTexture);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Create and compile the post-processing shader
    postProcessingShader = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fragmentShaderSource);
    
    // Set up the OpenGL context
    glClearColor(0.4, 0.4, 0.4, 1.0);
}

int main(int argc, char** argv) {
    // Initialize GLUT and create a window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Post-processing Shader");
    
    // Initialize OpenGL
    initialize();
    
    // Register callback functions
    glutDisplayFunc(display);
    
    // Enter the main loop
    glutMainLoop();
    
    return 0;
}