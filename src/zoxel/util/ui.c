//! Functions for zoxel main, containing data for zoxel game.

ecs_entity_t zoxel_main_menu;

void spawn_zoxel_main_menu(ecs_world_t *world)
{
    if (zoxel_main_menu != 0 && ecs_is_alive(world, zoxel_main_menu))
    {
        delete_hierarchy(world, zoxel_main_menu);
        // ecs_delete(world, zoxel_window);
        zoxel_main_menu = 0;
        return;
    }
    int2 window_size = { 260, 220 };
    int2 window_position = { 0, 0 };
    float2 window_anchor = { 0.5f, 0.5f };
    zoxel_main_menu = spawn_main_menu(world, "Zoxel", window_position, window_size, window_anchor, false);
}