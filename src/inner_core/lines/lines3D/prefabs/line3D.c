ecs_entity_t prefab_line3D;
ecs_entity_t prefab_temporary_line3D;

ecs_entity_t spawn_prefab_line3D(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_prefab_name("prefab_line3D")
    zox_add_tag(e, Line3D)
    zox_set(e, LineData3D, { { 0, 0, 0, 0, 0, 0 } })
    zox_set(e, LineThickness, { 1 })
    zox_set(e, ColorRGB, { { 22, 122, 44 } })
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab line3D [%lu].\n", (long int) (e));
    #endif
    prefab_line3D = e;
    return e;
}

ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time) {
    ecs_entity_t e;
    if (life_time == 0.0) {
        e = ecs_new_w_pair(world, EcsIsA, prefab_line3D);
    } else {
        e = ecs_new_w_pair(world, EcsIsA, prefab_temporary_line3D);
    }
    zox_set_only(e, LineData3D, { { pointA.x, pointA.y, pointA.z, pointB.x, pointB.y, pointB.z } })
    zox_set_only(e, LineThickness, { thickness })
    if (life_time != 0.0f) zox_set_only(e, DestroyInTime, { life_time })
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned line3D [%lu]\n", (long int) e);
    #endif
    return e;
}

/*void spawn_line3D_square(ecs_world_t *world, float3 point, float3 size, float thickness, double life_time) {
    spawn_line3D(world,
        float3_add(point, (float3) { -size.x / 2.0f, -size.y / 2.0f }),
        float3_add(point, (float3) { size.x / 2.0f, -size.y / 2.0f }),
        thickness, life_time);
    spawn_line3D(world,
        float3_add(point, (float3) { size.x / 2.0f, -size.y / 2.0f }),
        float3_add(point, (float3) { size.x / 2.0f, size.y / 2.0f }),
        thickness, life_time);
    spawn_line3D(world,
        float3_add(point, (float3) { size.x / 2.0f, size.y / 2.0f }),
        float3_add(point, (float3) { -size.x / 2.0f, size.y / 2.0f }),
        thickness, life_time);
    spawn_line3D(world,
        float3_add(point, (float3) { -size.x / 2.0f, size.y / 2.0f }),
        float3_add(point, (float3) { -size.x / 2.0f, -size.y / 2.0f }),
        thickness, life_time);
}*/