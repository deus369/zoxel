#include "base_camera.c"
#include "ui_camera.c"
#include "free_camera.c"
entity prefab_camera;
entity prefab_camera_ui;
entity prefab_camera_game;

void spawn_prefabs_cameras(ecs *world) {
    prefab_camera = spawn_prefab_camera(world);
    prefab_camera_ui = spawn_prefab_camera_ui(world, prefab_camera);
    spawn_prefab_free_camera(world, prefab_camera);
    if (prefab_app) {
        zox_prefab_add(prefab_app, CameraLinks)
    }
}