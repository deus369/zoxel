#ifndef zox_mod_raycasts
#define zox_mod_raycasts

// todo later: fix rays for coop, viewport distortion effects rays
// #define zox_debug_rays
#include "data/ray.c"
// 2D
zox_component_byte(RaycasterResult)
zox_component_entity(RaycasterTarget)       //! A target entity for the Raycaster
zox_component_int2(Raycaster)               //! Contains the raycast mouse position
// 3D
zox_component_float3(RaycastOrigin)
zox_component_float3(RaycastNormal)
#include "util/camera.c"
#include "systems/mouse_raycaster_system.c"
#include "systems/camera_ray_system.c"
#include "systems/ray_debug_system.c"

void prefab_add_raycasts_to_players(ecs_world_t *world, const ecs_entity_t e) {
    zox_prefab_set(e, RaycasterTarget, { 0 })
    zox_prefab_set(e, RaycasterResult, { 0 })
    zox_prefab_set(e, Raycaster, { int2_zero })
}

void prefab_add_raycasts3D(ecs_world_t *world, const ecs_entity_t e) {
    zox_prefab_set(e, RaycastOrigin, { float3_zero })
    zox_prefab_set(e, RaycastNormal, { float3_forward })
}

zox_begin_module(Raycasts)
zox_define_component_int2(Raycaster)
zox_define_component_byte(RaycasterResult)
zox_define_component_entity(RaycasterTarget)
zox_define_component_float3(RaycastOrigin)
zox_define_component_float3(RaycastNormal)
zox_system(MouseRaycasterSystem, zox_pip_raycasting, [in] DeviceLinks, [in] DeviceMode, [out] Raycaster)
zox_system(CameraRaySystem, zox_pip_raycasting, [in] FrustumCorners, [out] RaycastOrigin, [out] RaycastNormal)
#ifdef zox_debug_rays
zox_system_1(RayDebugSystem, zox_pip_mainthread, [in] RaycastOrigin, [in] RaycastNormal)
#endif
prefab_add_raycasts_to_players(world, prefab_player);
prefab_add_raycasts3D(world, prefab_camera);
zoxel_end_module(Raycasts)

#endif
