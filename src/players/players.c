#if !defined(zox_mod_players)
#define zox_mod_players

// todo: move based functionality into here
#include "data/settings.c"
zox_declare_tag(Player)
zox_declare_tag(PlayerCharacter)
zox_component_byte(PlayerState)
zox_component_entity(PlayerLink)
zox_memory_component(PlayerLinks, ecs_entity_t)
zox_component_entity(PlayerPauseEvent)
#include "prefabs/_.c"
int spawn_players(ecs_world_t *world, const ecs_entity_t game);

zox_begin_module(Players)
    zox_define_tag(Player)
    zox_define_tag(PlayerCharacter)
    zox_define_component_byte(PlayerState)
    zox_define_component_entity(PlayerLink)
    zox_define_memory_component(PlayerLinks)
    zox_define_component_entity(PlayerPauseEvent)
    spawn_prefabs_players(world);
zox_end_module(Players)

#endif
