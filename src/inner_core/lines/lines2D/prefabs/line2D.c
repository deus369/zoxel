ecs_entity_t prefab_line2D;
ecs_entity_t prefab_temporary_line2D;

ecs_entity_t spawn_prefab_line2D(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "prefab_line2D");
    set_unique_entity_name(world, e, "prefab_line2D");
    zoxel_add_tag(world, e, Line2D);
    zoxel_set(world, e, LineData2D, { { 0, 0, 0, 0 } });
    zoxel_set(world, e, LineThickness, { 1 });
    zoxel_set(world, e, Color, { { 0, 255, 255, 255 } });
    // create a temporary line, similar to the previous one
    ecs_entity_t e2 = ecs_new_w_pair(world, EcsIsA, e);
    ecs_add_id(world, e2, EcsPrefab);
    set_unique_entity_name(world, e2, "prefab_temporary_line2D");
    zoxel_set(world, e2, DestroyInTime, { 0 });
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
    zoxel_log("spawn_prefab line2D [%lu].\n", (long int) (e));
    #endif
    prefab_line2D = e;
    prefab_temporary_line2D = e2;
    return e;
}

ecs_entity_t spawn_line2D(ecs_world_t *world, float2 pointA, float2 pointB, float thickness, double life_time)
{
    ecs_defer_begin(world);
    ecs_entity_t e;
    if (life_time == 0.0)
    {
        e = ecs_new_w_pair(world, EcsIsA, prefab_line2D);
    }
    else
    {
        e = ecs_new_w_pair(world, EcsIsA, prefab_temporary_line2D);
    }
    // set_unique_entity_name(world, e, "line2D");
    ecs_set(world, e, LineData2D, { { pointA.x, pointA.y, pointB.x, pointB.y } });
    ecs_set(world, e, LineThickness, { thickness });
    if (life_time != 0.0f)
    {
        ecs_set(world, e, DestroyInTime, { life_time });
    }
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned line2D [%lu]\n", (long int) e);
    #endif
    return e;
}

void spawn_line2D_square(ecs_world_t *world, float2 point, float2 size, float thickness, double life_time)
{
    spawn_line2D(world,
        float2_add(point, (float2) { -size.x / 2.0f, -size.y / 2.0f }),
        float2_add(point, (float2) { size.x / 2.0f, -size.y / 2.0f }),
        thickness, life_time);
    spawn_line2D(world,
        float2_add(point, (float2) { size.x / 2.0f, -size.y / 2.0f }),
        float2_add(point, (float2) { size.x / 2.0f, size.y / 2.0f }),
        thickness, life_time);
    spawn_line2D(world,
        float2_add(point, (float2) { size.x / 2.0f, size.y / 2.0f }),
        float2_add(point, (float2) { -size.x / 2.0f, size.y / 2.0f }),
        thickness, life_time);
    spawn_line2D(world,
        float2_add(point, (float2) { -size.x / 2.0f, size.y / 2.0f }),
        float2_add(point, (float2) { -size.x / 2.0f, -size.y / 2.0f }),
        thickness, life_time);
}