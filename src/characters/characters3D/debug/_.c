uint get_debug_label_app(ecs_world_t *world,
    const ecs_entity_t player,
    char *buffer,
    const uint size, uint index)
{
    zox_geter_value(mouse_lock_window, WindowSize, int2, window_size)
    const int2 lock_position = get_mouse_center_point(world, mouse_lock_window);
    zox_geter_value(mouse_lock_window, WindowFullscreen, byte, fullscreen)
    zox_geter_value(mouse_lock_window, WindowMaximized, byte, maximized)
    index += snprintf(buffer + index, size - index, " - window_size %ix%i\n", window_size.x, window_size.y);
    index += snprintf(buffer + index, size - index, " - lock_position %ix%i\n", lock_position.x, lock_position.y);
    index += snprintf(buffer + index, size - index, " - fullscreen %i\n", fullscreen);
    index += snprintf(buffer + index, size - index, " - maximized %i\n", maximized);
    return index;
}

uint get_label_player_chunk_link(ecs_world_t *world,
    const ecs_entity_t player,
    char *buffer,
    const uint size, uint index)
{
    // index = get_debug_label_app(world, player, buffer, size, index);
    if (!player) {
        index += snprintf(buffer + index, size - index, "! invalid player\n");
        return index;
    }
    zox_geter(player, CharacterLink, characterLink)
    if (!zox_valid(characterLink->value)) {
        index += snprintf(buffer + index, size - index, "[%s] has no character\n", zox_get_name(player));
        return index;
    }

    return get_label_chunk_link(world, characterLink->value, buffer, size, index);
}
