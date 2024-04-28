extern unsigned char terrain_spawn_distance;
extern unsigned char terrain_vertical;
ecs_entity_t terrain_grid;

void destroy_terrain_grid(ecs_world_t *world) {
    zox_delete(terrain_grid)
}

void spawn_terrain_grid(ecs_world_t *world, const float real_chunk_scale) {
    const color_rgb grid_color = (color_rgb) { 0, 0, 0 };
    const float bottom_bounds = - real_chunk_scale * terrain_vertical;
    const float top_bounds = - bottom_bounds + real_chunk_scale;
    const float spacing = real_chunk_scale;
    const float thickness = 2.0f;
    const float radius = (terrain_spawn_distance) * (real_chunk_scale) + thickness * 0.01f;
    const float radius2 = (terrain_spawn_distance + 1) * (real_chunk_scale) + thickness * 0.01f;
    terrain_grid = ecs_new(world, 0);
    zox_prefab_set(terrain_grid, Children, { 0, NULL })
    Children *children = zox_get_mut(terrain_grid, Children)
    zox_modified(terrain_grid, Children)
    for (int i = bottom_bounds; i <= top_bounds; i += spacing) {
        add_to_Children(children, spawn_line3D_colored(world, (float3) { -radius, i, -radius }, (float3) { -radius, i, radius2 }, thickness, 0, grid_color));
        add_to_Children(children, spawn_line3D_colored(world, (float3) { -radius, i, radius2 }, (float3) { radius2, i, radius2 }, thickness, 0, grid_color));
        add_to_Children(children, spawn_line3D_colored(world, (float3) { radius2, i, radius2 }, (float3) { radius2, i, -radius }, thickness, 0, grid_color));
        add_to_Children(children, spawn_line3D_colored(world, (float3) { radius2, i, -radius }, (float3) { -radius, i, -radius }, thickness, 0, grid_color));
    }
    for (float i = -radius; i <= radius2; i += spacing) {
        add_to_Children(children, spawn_line3D_colored(world, (float3) { i, bottom_bounds, radius2 }, (float3) { i, top_bounds, radius2 }, thickness, 0, grid_color));
    }
    for (float i = -radius; i <= radius2; i += spacing) {
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
    }

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
