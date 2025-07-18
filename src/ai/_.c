#if !defined(zox_mod_ai) && defined(zox_mod_characters)
#define zox_mod_ai

#include "data/behaviours.c"
zox_declare_tag(Npc)
zox_declare_tag(Wanderer)
zox_component_byte(Behaviour)
zox_declare_tag(Jumper)
#include "prefabs/_.c"
#include "systems/_.c"

int count_entities_npc(ecs_world_t *world) {
    return zox_count_types(Npc)
}

zox_begin_module(Npcs)
    zox_define_tag(Npc)
    zox_define_tag(Wanderer)
    zox_define_tag(Jumper)
    zox_define_component_byte(Behaviour)
    define_systems_ai(world);
    spawn_prefabs_ai(world);
zox_end_module(Npcs)

#endif
