#ifndef zoxm_raycasts
#define zoxm_raycasts

// #define zox_debug_camera_rays // used to verify raycast line is straight
// todo later: fix rays for coop, viewport distortion effects rays
// #define zox_debug_rays
#include "data/ray.c"
// 2D
zoxc_byte(RaycasterResult);
zoxc_entity(RaycasterTarget);       //! A target entity for the Raycaster
zoxc_int2(Raycaster);               //! Contains the raycast mouse position
// 3D
zoxc_float3(RaycastOrigin);
zoxc_float3(RaycastNormal);
#include "util/camera.c"
#include "util/prefab.c"
#include "systems/mouse_raycaster_system.c"
#include "systems/zevice_raycaster_system.c"
#include "systems/camera_ray_system.c"
#include "systems/ray_debug_system.c"

zox_begin_module(Raycasts)
    zox_define_component_int2(Raycaster);
    zox_define_component_byte(RaycasterResult);
    zox_define_component_entity(RaycasterTarget);
    zox_define_component_float3(RaycastOrigin);
    zox_define_component_float3(RaycastNormal);
    // zox_system(MouseRaycasterSystem, zoxp_inputs_update, [in] inputs.DeviceLinks, [in] inputs.DeviceMode, [out] raycasts.Raycaster)
    zox_system(ZeviceRaycasterSystem, zoxp_inputs_update,
            [in] inputs.ZevicePointerPosition,
            [out] raycasts.Raycaster)
#ifndef zox_debug_camera_rays
    zox_system(CameraRaySystem, zoxp_inputs_update,
            [out] raycasts.RaycastOrigin,
            [out] raycasts.RaycastNormal)
#else
    zox_system_1(CameraRaySystem, zoxp_mainthread,
            [out] raycasts.RaycastOrigin,
            [out] raycasts.RaycastNormal)
#endif
#ifdef zox_debug_rays
    zox_system_1(RayDebugSystem, zoxp_mainthread,
            [in] raycasts.RaycastOrigin,
            [in] raycasts.RaycastNormal)
#endif
    add_hook_spawn_prefabs(prefab_set_game_prefabs);
zox_end_module(Raycasts)

#endif
