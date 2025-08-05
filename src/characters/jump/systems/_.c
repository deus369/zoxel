zox_increment_system_with_reset(JumpState, zox_dirty_end)
#include "can_jump.c"
#include "jump3.c"
#include "jump_sound.c"
#include "jump_begin.c"

void define_systems_jump(ecs_world_t* world) {
    zox_define_increment_system(JumpState); // , [none] Jumper);
    // jump
    // move these to Jump module? under Characters
    zox_system(CanJumpSystem, EcsOnUpdate,
            [in] collisions3.Grounded,
            [in] characters.CanJump);
    zox_system(JumpBeginSystem, EcsOnUpdate,
            [in] characters.JumpState,
            [out] characters.Jump);
    zox_system(Jump3System, zox_pip_physics,
            [in] physics.DisableMovement,
            [out] physics3.Velocity3D,
            [out] characters.Jump);
    zox_system_1(JumpSoundSystem, EcsOnUpdate,
            [in] characters.JumpState,
            [none] !characters.SilentJumper);
}