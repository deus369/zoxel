// debugs need systems to be _1 main thread
byte is_debug_behaviour = 0;
byte is_debug_target = 0;
byte is_debug_rotate_towards = 0;
byte is_debug_move_forwards = 0;
byte is_debug_wander = 0;
byte is_debug_flee = 0;
byte is_debug_attack = 0;

#include "wander_system.c"
#include "flee_system.c"
#include "follow_system.c"
#include "behaviour_system.c"
#include "rotate_towards_system.c"
#include "move_forward_system.c"
#include "target_set_system.c"
#include "attack_system.c"
#include "stay_upright_system.c"

void define_systems_npcs(ecs_world_t *world) {
    zox_system(BehaviourSystem, EcsOnUpdate,
        [in] combat.InCombat,
        [in] npcs.DefaultBehaviour,
        [out] npcs.Behaviour,
        [out] npcs.MoveForwards,
        [out] npcs.RotateTowards,
        [out] npcs.MoveSpeed,
        [none] npcs.Npc)
    zox_system_m(ThreatPositionSystem, !is_debug_target,
        [in] combat.LastDamager,
        [out] npcs.ThreatPosition,
        [none] npcs.Npc)
    zox_system_m(RotateTowardsSystem, !is_debug_rotate_towards,
        [in] npcs.RotateTowards,
        [in] physics.DisableMovement,
        [in] transforms3.Position3D,
        [in] transforms3.Rotation3D,
        [in] physics3.Omega3D,
        [in] npcs.TargetPosition,
        [out] physics3.Alpha3D,
        [none] npcs.Npc)
    zox_system_m(MoveForwardSystem, !is_debug_move_forwards,
        [in] npcs.MoveForwards,
        [in] physics.DisableMovement,
        [in] transforms3.Position3D,
        [in] transforms3.Rotation3D,
        // [in] physics3.Velocity3D,
        [in] npcs.TargetPosition,
        [in] npcs.MoveSpeed,
        [out] physics3.Acceleration3D,
        [none] npcs.Npc)
    zox_system_m(WanderSystem, !is_debug_wander,
        [in] npcs.Behaviour,
        [in] physics.DisableMovement,
        [in] transforms3.Position3D,
        [out] npcs.TargetPosition,
        [out] npcs.WanderDirection,
        [none] npcs.Npc)
    zox_system_m(AttackSystem, !is_debug_attack,
        [in] npcs.Behaviour,
        [in] physics.DisableMovement,
        [in] npcs.ThreatPosition,
        [out] npcs.TargetPosition,
        [none] npcs.Npc)
    zox_system_m(FleeSystem, !is_debug_flee,
        [in] npcs.Behaviour,
        [in] physics.DisableMovement,
        [in] transforms3.Position3D,
        [in] npcs.ThreatPosition,
        [out] npcs.TargetPosition,
        [none] npcs.Npc)
    /*zox_system(StayUprightSystem, EcsOnUpdate,
        [in] transforms3.Rotation3D,
        [in] physics3.Omega3D,
        [out] physics3.Alpha3D,
        [none] npcs.Npc)*/
}