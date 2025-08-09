zox_increment_system_with_reset(JumpState, zox_dirty_end);
#include "can_jump.c"
#include "jump3.c"
#include "jump_sound.c"
#include "jump_begin.c"

void define_systems_jump(ecs_world_t* world) {
    zoxd_system_increment(JumpState); // , [none] Jumper);
    // jump
    // move these to Jump module? under Characters
    zox_system(CanJumpSystem, EcsOnUpdate,
            [in] collisions3.Grounded,
            [in] characters.CanJump);
    zox_system(JumpBeginSystem, EcsOnUpdate,
            [in] characters.JumpState,
            [out] characters.Jump);
    /*zox_system(Jump3VelSystem, zoxp_physics + 1,
            [in] physics.DisableMovement,
            [out] physics3.Velocity3D,
            [out] characters.Jump);*/
    zox_system(Jump3AccSystem, zoxp_physics + 1,
            [in] physics.DisableMovement,
            [in] physics3.Velocity3D,
            [out] physics3.Acceleration3D,
            [out] characters.Jump);
    zox_system_1(JumpSoundSystem, EcsOnUpdate,
            [in] characters.JumpState,
            [none] !characters.SilentJumper);
}