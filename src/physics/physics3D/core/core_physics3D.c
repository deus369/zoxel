#ifndef zox_core_physics3D
#define zox_core_physics3D

#include "data/settings.c"
zox_component_byte(InitializePhysics3D)
zox_component_float3(Velocity3D)
zox_component_float3(Acceleration3D)
zox_component_float4(Omega3D)
zox_component_float4(Alpha3D)
zox_component_byte(Grounded) // use for friction - todo: use bit operations to check what sides cause friction and apply like that
// move to new sub module - Forces
zox_component_float3(Gravity3D)
zox_component_byte(Flying)
zox_declare_tag(Jumper)
zox_component_double(Jump)
#include "util/physics3D_util.c"
#include "systems/velocity3D_system.c"
#include "systems/acceleration3D_system.c"
#include "systems/omega3D_system.c"
#include "systems/alpha3D_system.c"
#include "systems/friction3D_system.c"
#include "systems/dissipation3D_system.c"
#include "systems/gravity3D_system.c"
#include "systems/jump3D_system.c"
#include "systems/physics3D_disable_system.c"
#include "systems/random_jump3D_system.c"
#include "systems/position3D_bounds_system.c" //  move to transforms

zox_begin_module(CorePhysics3D)
zox_define_component_byte(InitializePhysics3D)
zox_define_component_float3(Velocity3D)
zox_define_component_float3(Acceleration3D)
zox_define_component_float4(Omega3D)
zox_define_component_float4(Alpha3D)
zox_define_component_byte(Grounded)
zox_define_component_byte(Jump)
zox_define_tag(Jumper)
zox_define_component_float3(Gravity3D)
zox_system(Velocity3DSystem, zox_pip_physics, [out] Position3D, [in] Velocity3D)
zox_system(Omega3DSystem, zox_pip_physics, [in] Omega3D, [out] Rotation3D)
zox_system(Physics3DDisableSystem, zox_pip_physics, [out] InitializePhysics3D, [out] Position3D, [out] Velocity3D)
zox_system(Gravity3DSystem, zox_pip_physics, [in] Gravity3D, [in] Grounded, [out] Acceleration3D)
zox_system(RandomJump3DSystem, zox_pip_physics, [in] Grounded, [out] Jump, [none] Jumper)
zox_system(Jump3DSystem, zox_pip_physics, [in] DisableMovement, [out] Jump, [out] Acceleration3D)
zox_system(Friction3DSystem, zox_pip_physics, [in] Grounded, [in] Velocity3D, [out] Acceleration3D, [none] physics.Frictioned)
zox_system(Dissipation3DSystem, zox_pip_physics, [none] physics.Frictioned, [in] Omega3D, [out] Alpha3D)
zox_system(Acceleration3DSystem, zox_pip_physics, [out] Acceleration3D, [out] Velocity3D)
zox_system(Alpha3DSystem, zox_pip_physics, [out] Alpha3D, [out] Omega3D)
zox_system(Position3DBoundsSystem, zox_pip_physics, [in] Position3DBounds, [in] Bounds3D, [out] Position3D) // EcsPostUpdate - move to collisions maybe?
zoxel_end_module(CorePhysics3D)

#endif
