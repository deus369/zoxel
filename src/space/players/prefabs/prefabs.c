ecs_entity_t prefab_menu_game;
ecs_entity_t prefab_menu_game_touch;
#include "crosshair.c"
#include "player.c"
#include "menu_game_touch.c"
#include "menu_game.c"

void spawn_prefabs_players2(ecs_world_t *world) {
    zox_prefab_add(prefab_game, PlayerLinks)
    zox_prefab_set(prefab_player, PlayerPauseEvent, { 0 })
    prefab_menu_game = spawn_prefab_menu_game(world, prefab_element_invisible);
    prefab_menu_game_touch = spawn_prefab_menu_game_touch(world, prefab_element_invisible);
}
