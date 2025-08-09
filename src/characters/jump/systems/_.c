#include "jump_state.c"
#include "jump3.c"
#include "jump_begin.c"
#include "jump_sound.c"
#include "land_sound.c"
zox_increment_system_with_reset(JumpState, zox_dirty_end);
zox_increment_system_with_reset(LandState, zox_dirty_end);

void define_systems_jump(ecs_world_t* world) {
    zoxd_system_increment(JumpState);
    zoxd_system_increment(LandState);
    // jump
    // move these to Jump module? under Characters
    zox_system(CanJumpSystem, EcsOnUpdate,
            [in] collisions3.Grounded,
            [in] jumps.JumpState,
            [out] jumps.CanJump,
            [out] jumps.LandState);
    zox_system(JumpBeginSystem, EcsOnUpdate,
            [in] jumps.JumpState,
            [out] jumps.Jump);
    /*zox_system(Jump3VelSystem, zoxp_physics + 1,
            [in] physics.DisableMovement,
            [out] physics3.Velocity3D,
            [out] jumps.Jump);*/
    zox_system(Jump3AccSystem, zoxp_physics + 1,
            [in] physics.DisableMovement,
            [in] physics3.Velocity3D,
            [out] physics3.Acceleration3D,
            [out] jumps.Jump);
    zox_system_1(JumpSoundSystem, zoxp_mainthread,
            [in] jumps.JumpState,
            [none] !jumps.SilentJumper);
    zox_system_1(LandSoundSystem, zoxp_mainthread,
            [in] jumps.LandState,
            [none] !jumps.SilentJumper);
}