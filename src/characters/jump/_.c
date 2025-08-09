#ifndef zoxm_jump
#define zoxm_jump


zox_tag(SilentJumper);
zoxc_byte(CanJump);
zoxc_byte(JumpState);
zoxc_byte(LandState);
zoxc_double(Jump);
zoxc_byte(FlyMode);

#include "systems/_.c"

// TODO: Falling - FallSounds, FallDamage! Count Height

static inline byte get_character_can_jump(ecs_world_t *world, ecs_entity_t c) {
    return zox_valid(c) && zox_has(c, CanJump) ? zox_gett_value(c, CanJump) : 0;
}

zox_begin_module(Jumps)
    zox_define_tag(SilentJumper);
    zox_define_component_byte(CanJump);
    zox_define_component_byte(JumpState);
    zox_define_component_byte(LandState);
    zox_define_component_double(Jump);
    zox_define_component_byte(FlyMode);
    define_systems_jump(world);
zox_end_module(Jumps)

#endif