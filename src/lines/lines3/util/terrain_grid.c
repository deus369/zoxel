ecs_entity_t terrain_grid;

void destroy_terrain_grid(ecs_world_t *world) {
    if (terrain_grid) {
        zox_delete(terrain_grid)
    }
}

void spawn_terrain_grid(
    ecs_world_t *world,
    const float real_chunk_scale,
    byte terrain_spawn_distance,
    byte terrain_vertical
) {
    const color_rgb grid_color = (color_rgb) { 0, 0, 0 };
    const float spacing = real_chunk_scale;
    const float thickness = 2.0f;
    const float radius = (terrain_spawn_distance) * (real_chunk_scale); // + thickness * 0.01f;
    const float radius2 = (terrain_spawn_distance + 1) * (real_chunk_scale); // + thickness * 0.01f;
    const float bottom_bounds = - real_chunk_scale * terrain_vertical;
    const float top_bounds = - bottom_bounds + real_chunk_scale;
    const float left_bounds = -radius;
    const float right_bounds = radius2;
    const float back_bounds = -radius;
    const float front_bounds = radius2;
    terrain_grid = zox_get_new();
    zox_prefab_add(terrain_grid, Children)
    Children *children = zox_get_mut(terrain_grid, Children)
    zox_modified(terrain_grid, Children)
    // front/back side
    for (float k = back_bounds; k <= front_bounds; k += (front_bounds - back_bounds)) {
        for (float i = left_bounds; i <= right_bounds; i += spacing) {
            for (float j = bottom_bounds; j <= top_bounds; j += spacing) {
                if (j != top_bounds) add_to_Children(children, spawn_line3D_colored(world, (float3) { i, j, k }, (float3) { i, j + spacing, k }, thickness, 0, grid_color));
                if ((int) i != (int) right_bounds) add_to_Children(children, spawn_line3D_colored(world, (float3) { i, j, k }, (float3) { i + spacing, j, k }, thickness, 0, grid_color));
            }
        }
    }
    // left/right side
    for (float k = left_bounds; k <= right_bounds; k += (right_bounds - left_bounds)) {
        for (float i = back_bounds; i <= front_bounds; i += spacing) {
            for (float j = bottom_bounds; j <= top_bounds; j += spacing) {
                if (j != top_bounds) add_to_Children(children, spawn_line3D_colored(world, (float3) { k, j, i }, (float3) { k, j + spacing, i }, thickness, 0, grid_color));
                if (i != front_bounds) add_to_Children(children, spawn_line3D_colored(world, (float3) { k, j, i }, (float3) { k, j, i + spacing }, thickness, 0, grid_color));
            }
        }
    }
    /*for (int i = bottom_bounds; i <= top_bounds; i += spacing) {
        add_to_Children(children, spawn_line3D_colored(world, (float3) { -radius, i, -radius }, (float3) { -radius, i, radius2 }, thickness, 0, grid_color));
        add_to_Children(children, spawn_line3D_colored(world, (float3) { -radius, i, radius2 }, (float3) { radius2, i, radius2 }, thickness, 0, grid_color));
        add_to_Children(children, spawn_line3D_colored(world, (float3) { radius2, i, radius2 }, (float3) { radius2, i, -radius }, thickness, 0, grid_color));
        add_to_Children(children, spawn_line3D_colored(world, (float3) { radius2, i, -radius }, (float3) { -radius, i, -radius }, thickness, 0, grid_color));
    }*/
    /*for (float i = -radius; i <= radius2; i += spacing) {
        add_to_Children(children, spawn_line3D_colored(world, (float3) { radius2, bottom_bounds, i }, (float3) { radius2, top_bounds, i }, thickness, 0, grid_color));
    }
    for (float i = -radius; i <= radius2; i += spacing) {
        add_to_Children(children, spawn_line3D_colored(world, (float3) { i, bottom_bounds, -radius }, (float3) { i, top_bounds, -radius }, thickness, 0, grid_color));
    }
    for (float i = -radius; i <= radius2; i += spacing) {
        add_to_Children(children, spawn_line3D_colored(world, (float3) { -radius, bottom_bounds, i }, (float3) { -radius, top_bounds, i }, thickness, 0, grid_color));
    }
    for (float i = -radius + spacing; i < radius2; i += spacing) {
        add_to_Children(children, spawn_line3D_colored(world, (float3) { i, top_bounds, -radius }, (float3) { i, top_bounds, radius2 }, thickness, 0, grid_color));
    }
    for (float i = -radius + spacing; i < radius2; i += spacing) {
        add_to_Children(children, spawn_line3D_colored(world, (float3) { -radius, top_bounds, i }, (float3) { radius2, top_bounds, i }, thickness, 0, grid_color));
    }*/

    // bottom
    /*for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            spawn_line3D(world, (float3) { i, 0, j }, (float3) { i + 1, 0, j + 1 }, thickness, 32);
        }
    }*/
}
        /*spawn_line3D(world, (float3) { -radius, bottom_bounds, -radius }, (float3) { -radius, bottom_bounds, radius2 }, thickness, 0);
        spawn_line3D(world, (float3) { -radius, bottom_bounds, radius2 }, (float3) { radius2, bottom_bounds, radius2 }, thickness, 0);
        spawn_line3D(world, (float3) { radius2, bottom_bounds, radius2 }, (float3) { radius2, bottom_bounds, -radius }, thickness, 0);
        spawn_line3D(world, (float3) { radius2, bottom_bounds, -radius }, (float3) { -radius, bottom_bounds, -radius }, thickness, 0);
        spawn_line3D(world, (float3) { -radius, top_bounds, -radius }, (float3) { -radius, top_bounds, radius2 }, thickness, 0);
        spawn_line3D(world, (float3) { -radius, top_bounds, radius2 }, (float3) { radius2, top_bounds, radius2 }, thickness, 0);
        spawn_line3D(world, (float3) { radius2, top_bounds, radius2 }, (float3) { radius2, top_bounds, -radius }, thickness, 0);
        spawn_line3D(world, (float3) { radius2, top_bounds, -radius }, (float3) { -radius, top_bounds, -radius }, thickness, 0);*/
