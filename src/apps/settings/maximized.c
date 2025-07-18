byte maximized = 1;
extern void zox_set_app_maximized(ecs_world_t* world, ecs_entity_t e, byte maximized);

// when setting is set
void set_app_maximized(ecs_world_t* world, void* value) {
    maximized = *(byte*) value;
    // zox_log_sdl("> setting [maximized] set to [%i]", maximized)
    if (zox_valid(main_app)) {
        zox_set_app_maximized(world, main_app, maximized);
    }
}

// use our setting
void zox_toggle_maximized(ecs_world_t *world) {
    zoxs_set_byte(world, "maximized", !maximized);
}

void zox_set_maximized(ecs_world_t *world, byte new_maximized) {
    zoxs_set_byte(world, "maximized", new_maximized);
}

void zox_set_maximized_silently(ecs_world_t *world, const ecs_entity_t e, byte new_maximized) {
    // zox_log("> silently set [maximized] to [%i]", new_maximized)
    maximized = new_maximized;
    zoxs_set_byte_silently(world, "maximized", new_maximized);
    zox_set(e, WindowMaximized, { new_maximized })
}