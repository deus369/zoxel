ecs_entity_t debug_entity_text3D;

void key_down_update_text3D(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_g) {
        const ecs_entity_t e = debug_entity_text3D;
        if (!e) {
            return;
        }
        zox_log("> setting text3D %s", zox_get_name(e))
        set_entity_text(world, e, "Hello World");
    }
}