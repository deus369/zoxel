#include "prefabs.c"

static inline ecs_entity_t get_player_character(ecs_world_t *world, ecs_entity_t p) {
    return zox_valid(p) && zox_has(p, CharacterLink) ? zox_gett_value(p, CharacterLink) : 0;
}