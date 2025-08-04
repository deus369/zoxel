extern int zox_statistics_systems;
extern int zox_statistics_components;
extern int zox_statistics_modules;

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>


void enable_input() {
    struct termios t;
    tcgetattr(0, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &t);
    fcntl(0, F_SETFL, O_NONBLOCK);
}


void iterate_terminal(ecs_world_t* world) {
    if (!headless) {
        return;
    }

    enable_input();

    zox_log("\033[2J\033[H");
    zox_log("Z:x");
    zox_log("...");
    zox_log("Welcome Traveler");
    zox_log("\n");
    zox_log("   - mods [%i]", zox_statistics_modules);
    zox_log("   - syss [%i]", zox_statistics_systems);
    zox_log("   - coms [%i]", zox_statistics_components);

    char key;
    if (read(0, &key, 1) > 0) {
        if (key == 'q') exit(0);
        if (key == 'r') {
            zox_statistics_modules = 0;
            zox_statistics_systems = 0;
            zox_statistics_components = 0;
        }
    }
}