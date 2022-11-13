ecs_entity_t canvas_prefab;

void spawn_prefab_canvas(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "canvas_prefab");
    printf("spawn_prefab canvas [%lu].\n", (long int) (e));
    zoxel_add_tag(world, e, Canvas);
    zoxel_add_component(world, e, PixelSize);
    canvas_prefab = e;
}

ecs_entity_t spawn_canvas(ecs_world_t *world, int2 size)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, canvas_prefab);
    ecs_set(world, e, PixelSize, { size });
    canvas = e;
    return e;
}