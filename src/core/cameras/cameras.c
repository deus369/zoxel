#ifndef zoxel_cameras
#define zoxel_cameras

#define max_cameras 16
int main_cameras_count = 1;
ecs_entity_t main_cameras[max_cameras];
ecs_entity_t ui_cameras[1];
// -=- Tags -=-
ECS_DECLARE(Camera);
ECS_DECLARE(CameraFollower2D);  // a tag for a camera that follows a Character2D
ECS_DECLARE(UICamera);
// -=- components -=-
//! Used for the cameras frustrum.
zoxel_component(ProjectionMatrix, float4x4);
//! Used with all the materials to render the scene.
zoxel_component(ViewMatrix, float4x4);
//! Has dimensions of the camera viewport screen. Used to calculate a camera frustrum.
zoxel_component(ScreenDimensions, int2);
zoxel_component(ScreenPosition, int2);
//! Used to calculate a camera frustrum.
zoxel_component(FieldOfView, float);
zoxel_component(CameraNearDistance, float);
//! A link to a Camera
zoxel_component(CameraLink, ecs_entity_t);
//! A link to a Camera Target entity.
zoxel_component(CameraTarget, ecs_entity_t);
//! Used to free roam a camera.
zoxel_component(FreeRoam, unsigned char);
// -=- prefabs -=-
#include "prefabs/camera_base.c"
#include "prefabs/camera2D.c"
#include "prefabs/ui_camera.c"
// -=- util -=-
#include "util/main_camera.c"
// -=- systems -=-
#include "systems/projection_matrix_system.c"
#include "systems/view_matrix_system.c"
#include "systems/camera2D_follow_system.c"

void set_main_cameras(int new_count)
{
    main_cameras_count = new_count;
}

void set_mouse_mode()
{
    ecs_entity_t main_camera = main_cameras[0]; //  get_main_camera();
    if (!ecs_is_valid(world, main_camera))
    {
        return;
    }
    bool constrain_mouse;
    if (ecs_has(world, main_camera, FreeRoam) &&
        ecs_get(world, main_camera, FreeRoam)->value == 1)
    {
        constrain_mouse = true;
    }
    else
    {
        constrain_mouse = false;
    }
    SDL_SetRelativeMouseMode(constrain_mouse);  //! Locks Main Mouse.
    if (constrain_mouse)
    {
        SDL_WarpMouseInWindow(main_window, screen_dimensions.x / 2, screen_dimensions.y / 2);
    }
    // SDL_SetWindowGrab(main_window, constrain_mouse);
}

void CamerasImport(ecs_world_t *world)
{
    ECS_MODULE(world, cameras);
    // zoxel_module(world, cameras, nm_zoxel_cameras);
    // -=- tags -=-
    ECS_TAG_DEFINE(world, Camera);
    ECS_TAG_DEFINE(world, CameraFollower2D); // Until fix is found. \todo Fix this, readd it back here where it belongs.
    ECS_TAG_DEFINE(world, UICamera);
    // -=- components -=-
    ECS_COMPONENT_DEFINE(world, CameraLink);
    ECS_COMPONENT_DEFINE(world, CameraTarget);
    ECS_COMPONENT_DEFINE(world, ProjectionMatrix);
    ECS_COMPONENT_DEFINE(world, ViewMatrix);
    ECS_COMPONENT_DEFINE(world, ScreenDimensions);
    ECS_COMPONENT_DEFINE(world, ScreenPosition);
    ECS_COMPONENT_DEFINE(world, FieldOfView);
    ECS_COMPONENT_DEFINE(world, CameraNearDistance);
    ECS_COMPONENT_DEFINE(world, FreeRoam);
    // -=- systems -=-
    ECS_SYSTEM_DEFINE(world, ProjectionMatrixSystem, EcsOnUpdate,
        [in] ScreenDimensions, [in] FieldOfView, [in] CameraNearDistance, [out] ProjectionMatrix);
    zoxel_system(world, ViewMatrixSystem, EcsOnUpdate, [in] Position, [in] Rotation, [in] ProjectionMatrix, [out] ViewMatrix);
    zoxel_system(world, CameraFollow2DSystem, EcsOnUpdate,
        [none] CameraFollower2D, [in] FreeRoam, [in] CameraTarget, [out] Position, [out] Rotation);
    // -=- prefabs -=-
    spawn_camera_base_prefab(world);
    spawn_camera2D_follower_prefab(world);
}

// Custom name for namespace?
// const char* nm_zoxel_cameras = "Zoxel.cameras";
#endif