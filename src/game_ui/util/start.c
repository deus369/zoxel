void menu_start_triggered(ecs_world_t *world,
    const ecs_entity_t player,
    const ecs_entity_t canvas)
{
    find_child_with_tag(canvas, MenuStart, menu)
    if (!menu) {
        zox_log_error("No MenuStart found on canvas")
        return;
    }
    zox_delete(menu)
    spawn_main_menu(world, player, canvas, game_name);
    const double volume = (0.6 + 0.4 * (rand() % 101) / 100.0) * get_volume_sfx();
    spawn_sound_generated(world, prefab_sound_generated, instrument_piano, note_frequencies[16], 2.8f, volume);
}

void button_event_menu_start(ecs_world_t *world,
    const ClickEventData *event)
{
    const ecs_entity_t canvas = zox_get_value(event->clicker, CanvasLink)
    menu_start_triggered(world, event->clicker, canvas);
}
