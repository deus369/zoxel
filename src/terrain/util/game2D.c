void realms_start_game2D_delayed(ecs_world_t *world, const ecs_entity_t game) {
    set_sky_color(world, game_sky_color, game_sky_bottom_color);
    spawn_grid2D(world);
}