// sudo apt-get install freeglut3-dev
// gcc tests/glut/play_button.c -o build/play_button -lglut -lGL -lGLU && ./build/play_button
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

const char *command = "make -j$(nproc) && make run";
const char *app_name = "z";
#define screen_width 1920
#define screen_height 1080
#define app_width 120
#define app_height 120
#define ANIMATION_DURATION 0.3 // Animation duration in seconds
#define animation_scale 0.12
#define ANIMATION_FPS 60       // Animation frames per second
#define ANIMATION_STEPS (ANIMATION_DURATION * ANIMATION_FPS)
unsigned char is_animating = 0;
int animation_step = 0;
#define FRAME_RATE_MS 16
int is_running = 0;
int bash_id;
pid_t pid;

void check_running() {
    if (is_running) {
        int status;
        int result = waitpid(pid, &status, WNOHANG);
        if (result != 0) {
            printf(" o> command has completed\n");
            is_running = 0;
        }
    }
}

void end_process() {
    if (pid > 0) {
        printf(" o> ending zoxel\n");
        kill(pid, SIGTERM);
        // execl("/usr/bin/pkill", "pkill", "zoxel", NULL);
        system("pkill zoxel");
        pid = 0;
    }
}

int execute_command() {
    printf(" o> running zoxel\n");
    /*bash_id = system(command);*/
    pid = fork();
    if (pid == -1) {
        printf("Error forking the process\n");
        return 1;
    } else if (pid == 0) {
        bash_id = execl("/bin/sh", "sh", "-c", "make -j$(nproc) && make run", NULL);
    }
    if (bash_id == -1) {
        printf(" o> error executing the command\n");
    } else {
        is_running = 1;
    }
}

void render_button() {
    float scale = ((float) animation_step / (ANIMATION_STEPS / 2)) * animation_scale;
    if (animation_step > ANIMATION_STEPS / 2) scale = animation_scale - ((float) (animation_step - (ANIMATION_STEPS / 2)) / (ANIMATION_STEPS / 2)) * animation_scale;
    // glPushMatrix();
    // glScalef(scale, scale, 1.0);
    glBegin(GL_TRIANGLES);
    if (is_running) glColor3f(0.6, 0.1, 0.1);
    else glColor3f(0.0, 0.8, 0.7);
    float low_end = 0.1f - scale;
    float high_end = 0.9f + scale;
    glVertex2f(app_width * low_end, app_height * low_end);
    glVertex2f(app_width * high_end, app_height * 0.5f);
    glVertex2f(app_width * low_end, app_height * high_end);
    glEnd();
    // glPopMatrix();
}

void animate() {
    if (is_animating) {
        animation_step++;
        if (animation_step > ANIMATION_STEPS) {
            is_animating = 0;
            animation_step = 0;
            if (is_running) end_process();
            else execute_command();
        }
    }
}

void display() {
    // glClear(GL_COLOR_BUFFER_BIT);
    // render_button();
    // glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!is_animating) {
            is_animating = 1;
            printf("    > beginning to run zoxel\n");
        }
    }
}

void timer(int value) {
    check_running();
    animate();
    glClear(GL_COLOR_BUFFER_BIT);
    render_button();
    glFlush();
    glutTimerFunc(FRAME_RATE_MS, timer, 0);
}

int main(int argc, char **argv) {
    atexit(end_process);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    int windowPosX = screen_width - app_width;
    int windowPosY = screen_height - app_height;
    glutInitWindowPosition(windowPosX, windowPosY);
    glutInitWindowSize(app_width, app_height);
    glutCreateWindow(app_name);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glClearColor(0.2, 0.3, 0.46, 1.0);
    gluOrtho2D(0, app_width, 0, app_height);
    glutTimerFunc(FRAME_RATE_MS, timer, 0);
    glutMainLoop();
    return 0;
}