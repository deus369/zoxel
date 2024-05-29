#include "base_camera.c"
#include "camera2D.c"
#include "ui_camera.c"
#include "free_camera.c"
ecs_entity_t prefab_camera;


void spawn_prefabs_cameras(ecs_world_t *world) {
    prefab_camera = spawn_prefab_camera(world);
    spawn_prefab_free_camera(world, prefab_camera);
    spawn_prefab_camera2D_follower(world, prefab_camera);
}
