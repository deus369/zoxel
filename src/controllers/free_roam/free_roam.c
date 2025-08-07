// relies on players and cameras
#if !defined(zoxm_free_roam) && defined(zoxm_cameras) && defined(zoxm_players)
#define zoxm_free_roam

#include "data/settings.c"
#include "systems/free_camera_move_system.c"
#include "systems/free_camera_rotate_system.c"
#include "systems/free_camera_toggle_system.c"
#include "systems/free_camera_disable_movement_system.c"

zox_begin_module(FreeRoam)
    zox_system(FreeCameraMoveSystem, EcsOnUpdate, [in] inputs.DeviceLinks, [in] cameras.CameraLink, [none] players.Player)
    zox_system(FreeCameraRotateSystem, EcsOnUpdate, [in] inputs.DeviceLinks, [in] cameras.CameraLink, [none] players.Player)
    zox_system(FreeCameraToggleSystem, EcsOnUpdate, [in] inputs.DeviceLinks, [in] cameras.CameraLink, [in] games.GameLink, [none] players.Player)
zox_end_module(FreeRoam)

#endif

