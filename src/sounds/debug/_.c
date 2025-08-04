// add debug keys to test sounds here
#include "toggle.c"

void zox_debug_sound(ecs_world_t* world, ecs_entity_t e) {
    zox_geter(e, SoundData, data);
    zox_log_error("Destroying Entity [%s]", zox_get_name(e));
    zox_log("   - sound [%i]", data->length);
}