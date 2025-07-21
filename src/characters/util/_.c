#include "prefabs.c"

static inline byte get_character_can_jump(ecs_world_t *world, ecs_entity_t c) {
    return zox_valid(c) && zox_has(c, CanJump) ? zox_gett_value(c, CanJump) : 0;
}

static inline ecs_entity_t get_player_character(ecs_world_t *world, ecs_entity_t p) {
    return zox_valid(p) && zox_has(p, CharacterLink) ? zox_gett_value(p, CharacterLink) : 0;
}