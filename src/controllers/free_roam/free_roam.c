// relies on players and cameras
#if !defined(zox_mod_free_roam) && defined(zox_mod_cameras) && defined(zox_mod_players)
#define zox_mod_free_roam

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

