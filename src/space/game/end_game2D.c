void player_end_game2D(
    ecs *world,
    const entity player
) {
    const entity camera = zox_get_value(player, CameraLink)
    const entity character = zox_get_value(player, CharacterLink)
    const entity canvas = zox_get_value(player, CanvasLink)
    zox_delete(world_grid2D)
    zox_delete(character)
    zox_set(player, CharacterLink, { 0 })
    zox_set(camera, CharacterLink, { 0 })
    spawn_main_menu(world, player, canvas, game_name);
}