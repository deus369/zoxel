#if !defined(zox_mod_players)
#define zox_mod_players

// todo: move based functionality into here
#include "states/_.c"
#include "settings/_.c"
zox_declare_tag(Player)
zox_declare_tag(PlayerCharacter)
zox_component_byte(PlayerState)
zox_component_double(PlayerRespawn)
zox_component_entity(PlayerLink)
zox_memory_component(PlayerLinks, ecs_entity_t)
zox_component_entity(PlayerPauseEvent)
#include "prefabs/_.c"
#include "systems/_.c"
int spawn_players(ecs_world_t *world, const ecs_entity_t game);

void on_boot_players(ecs_world_t *world, ecs_entity_t app) {
    if (!headless && zox_is_players) {
        zox_geter_value(app, GameLink, ecs_entity_t, game)
        spawn_connected_devices(world, app);
        players_playing = spawn_players(world, game);
    }
}

zox_begin_module(Players)
    zox_define_tag(Player)
    zox_define_tag(PlayerCharacter)
    zox_define_component_byte(PlayerState)
    zox_define_component_double(PlayerRespawn)
    zox_define_component_entity(PlayerLink)
    zox_define_memory_component(PlayerLinks)
    zox_define_component_entity(PlayerPauseEvent)
    define_systems_players(world);
    add_hook_on_boot(on_boot_players);
    spawn_prefabs_players(world);
zox_end_module(Players)

#endif
