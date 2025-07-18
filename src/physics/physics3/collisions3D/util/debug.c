static inline ecs_entity_t get_player_character(ecs_world_t*, ecs_entity_t);
static inline byte get_character_can_jump(ecs_world_t*, ecs_entity_t);

uint debug_label_collisions(ecs_world_t *world,
    const ecs_entity_t player,
    char *buffer,
    const uint size, uint index)
{
    const ecs_entity_t character = get_player_character(world, player);
    if (!zox_valid(character)) {
        index += snprintf(buffer + index, size - index, "[%s] has no character\n", zox_get_name(player));
        return index;
    }
    index += snprintf(buffer + index, size - index, "character [%s]\n", zox_get_name(character));
    zox_geter_value(character, Position3D, float3, position)
    zox_geter_value(character, LastUnstuck3, float3, lastun3)
    zox_geter_value(character, Collision, byte, collision)
    // zox_geter_value(character, CanJump, byte, can_jump)
    const byte can_jump = get_character_can_jump(world, character);
    zox_geter_value(character, Grounded, byte, grounded)
    index += snprintf(buffer + index, size - index, " - collision [%i]\n", collision);
    index += snprintf(buffer + index, size - index, " - can_jump [%i]\n", can_jump);
    index += snprintf(buffer + index, size - index, " - grounded [%i]\n", grounded);
    index += snprintf(buffer + index, size - index, " - pos [%fx%fx%f]\n", position.x, position.y, position.z);
    index += snprintf(buffer + index, size - index, " - lastun3 [%fx%fx%f]\n", lastun3.x, lastun3.y, lastun3.z);

    return index;
}