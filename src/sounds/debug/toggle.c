void toggle_sound(ecs_world_t *world, int32_t keycode) {
    (void) world;
    if (keycode == SDLK_m) {
        nosounds = !nosounds;
        zox_log("Sound %s", nosounds ? "Disabled" : "Enabled");
    }
}