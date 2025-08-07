#if !defined(zoxm_ai) && defined(zoxm_characters)
#define zoxm_ai

// todo: a threat level - if you are higher level than npc they should have higher chance to flee!

zox_declare_tag(Npc)
zox_declare_tag(Jumper)
zox_declare_tag(Wanderer)
zox_declare_tag(Coward)
zox_component_byte(Behaviour)
zox_component_byte(DefaultBehaviour)
zox_component_byte(MoveForwards)
zox_component_byte(RotateTowards)
zox_component_float(MoveSpeed)
zox_component_float3(TargetPosition)
zox_component_float3(ThreatPosition)
zox_component_float3(WanderDirection)
#include "states/_.c"
#include "prefabs/_.c"
#include "systems/_.c"
#include "util/_.c"

zox_begin_module(Npcs)
    zox_define_tag(Npc)
    zox_define_tag(Jumper)
    zox_define_tag(Wanderer)
    zox_define_tag(Coward)
    zox_define_component_byte(Behaviour)
    zox_define_component_byte(DefaultBehaviour)
    zox_define_component_byte(MoveForwards)
    zox_define_component_byte(RotateTowards)
    zox_define_component_float(MoveSpeed)
    zox_define_component_float3(TargetPosition)
    zox_define_component_float3(ThreatPosition)
    zox_define_component_float3(WanderDirection)
    define_systems_npcs(world);
    spawn_prefabs_npcs(world);
zox_end_module(Npcs)

#endif
