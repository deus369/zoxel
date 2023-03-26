ecs_entity_t prefab_line3D;
ecs_entity_t prefab_temporary_line3D;

ecs_entity_t spawn_prefab_line3D(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "prefab_line3D");
    set_unique_entity_name(world, e, "prefab_line3D");
    zoxel_add_tag(world, e, Line3D);
    zoxel_set(world, e, LineData3D, { { 0, 0, 0, 0, 0, 0 } });
    zoxel_set(world, e, LineThickness, { 1 });
    zoxel_set(world, e, Color, { { 44, 188, 77, 255 } });
    // create a temporary line, similar to the previous one
    ecs_entity_t e2 = ecs_new_w_pair(world, EcsIsA, e);
    ecs_add_id(world, e2, EcsPrefab);
    set_unique_entity_name(world, e2, "prefab_temporary_line3D");
    zoxel_set(world, e2, DestroyInTime, { 0 });
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
    zoxel_log("spawn_prefab line3D [%lu].\n", (long int) (e));
    #endif
    prefab_line3D = e;
    prefab_temporary_line3D = e2;
    return e;
}

ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time) {
    ecs_defer_begin(world);
    ecs_entity_t e;
    if (life_time == 0.0)
    {
        e = ecs_new_w_pair(world, EcsIsA, prefab_line3D);
    }
    else
    {
        e = ecs_new_w_pair(world, EcsIsA, prefab_temporary_line3D);
    }
    // set_unique_entity_name(world, e, "line3D");
    ecs_set(world, e, LineData3D, { { pointA.x, pointA.y, pointA.z, pointB.x, pointB.y, pointB.z } });
    ecs_set(world, e, LineThickness, { thickness });
    if (life_time != 0.0f)
    {
        ecs_set(world, e, DestroyInTime, { life_time });
    }
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned line3D [%lu]\n", (long int) e);
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