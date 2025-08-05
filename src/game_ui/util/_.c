#include "menu_main.c"
#include "menu_options.c"
#include "menu_paused.c"
#include "game_loading.c"
#include "taskbar.c"
#include "crosshair.c"
#include "start.c"
#include "game.c"
#include "pause.c"

void dispose_gameui(ecs_world_t *world, void *ctx) {
    dispose_hook_taskbar();
}