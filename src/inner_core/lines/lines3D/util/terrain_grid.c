extern unsigned char terrain_spawn_distance;
extern unsigned char terrain_vertical;

void spawn_terrain_grid(float real_chunk_scale) {
    float bottom_bounds = - real_chunk_scale * terrain_vertical; // - real_chunk_scale * 0.5f; // + real_chunk_scale * 0.5f; // real_chunk_scale; //  * (1.0f / 2.0f); // 2.0f; // 0.5f;
    float top_bounds = - bottom_bounds + real_chunk_scale;
    float spacing = real_chunk_scale;
    float thickness = 2.0f;
    float radius = (terrain_spawn_distance) * (real_chunk_scale) + thickness * 0.01f;
    float radius2 = (terrain_spawn_distance + 1) * (real_chunk_scale) + thickness * 0.01f;
    for (int i = bottom_bounds; i <= top_bounds; i += spacing) {
        spawn_line3D(world, (float3) { -radius, i, -radius }, (float3) { -radius, i, radius2 }, thickness, 0);
        spawn_line3D(world, (float3) { -radius, i, radius2 }, (float3) { radius2, i, radius2 }, thickness, 0);
        spawn_line3D(world, (float3) { radius2, i, radius2 }, (float3) { radius2, i, -radius }, thickness, 0);
        spawn_line3D(world, (float3) { radius2, i, -radius }, (float3) { -radius, i, -radius }, thickness, 0);
    }
    for (float i = -radius; i <= radius2; i += spacing) {
        spawn_line3D(world, (float3) { i, bottom_bounds, radius2 }, (float3) { i, top_bounds, radius2 }, thickness, 0);
    }
    for (float i = -radius; i <= radius2; i += spacing) {
        spawn_line3D(world, (float3) { radius2, bottom_bounds, i }, (float3) { radius2, top_bounds, i }, thickness, 0);
    }
    for (float i = -radius; i <= radius2; i += spacing) {
        spawn_line3D(world, (float3) { i, bottom_bounds, -radius }, (float3) { i, top_bounds, -radius }, thickness, 0);
    }
    for (float i = -radius; i <= radius2; i += spacing) {
        spawn_line3D(world, (float3) { -radius, bottom_bounds, i }, (float3) { -radius, top_bounds, i }, thickness, 0);
    }

    for (float i = -radius + spacing; i < radius2; i += spacing) {
        spawn_line3D(world, (float3) { i, top_bounds, -radius }, (float3) { i, top_bounds, radius2 }, thickness, 0);
    }
    for (float i = -radius + spacing; i < radius2; i += spacing) {
        spawn_line3D(world, (float3) { -radius, top_bounds, i }, (float3) { radius2, top_bounds, i }, thickness, 0);
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