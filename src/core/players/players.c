#if !defined(zox_mod_players)
#define zox_mod_players

// todo: move based functionality into here
zox_declare_tag(Player)
zox_declare_tag(PlayerCharacter)
zox_component_byte(PlayerState)
zox_component_entity(PlayerLink)
zox_memory_component(PlayerLinks, ecs_entity_t)
#include "prefabs/prefabs.c"

zox_begin_module(Players)
zox_define_tag(Player)
zox_define_tag(PlayerCharacter)
zox_define_component_byte(PlayerState)
zox_define_component_entity(PlayerLink)
zox_define_memory_component(PlayerLinks)
spawn_prefabs_players(world);
zoxel_end_module(Players)

#endif
