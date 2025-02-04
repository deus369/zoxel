ecs_entity_t world_grid2D;
const float world_grid2D_size = 8;

ecs_entity_t spawn_grid2D(ecs_world_t *world) {
    const float size = world_grid2D_size;
    const float grid_size = 0.5f;
    const float thickness = 4.0f;
    const color_rgb grid_color = (color_rgb) { 25, 15, 15 };
    const ecs_entity_t e = ecs_new(world, 0);
    zox_prefab_add(e, Children)
    Children *children = zox_get_mut(e, Children)
    zox_modified(e, Children)
    float2 position;
    for (position.x = -size; position.x <= size; position.x += grid_size) {
        for (position.y = -size; position.y <= size; position.y += grid_size) {
            if (position.x != size) add_to_Children(children, spawn_line2D_colored(world, position, (float2) { position.x + grid_size, position.y }, thickness, 0, grid_color));
            if (position.y != size) add_to_Children(children, spawn_line2D_colored(world, position, (float2) { position.x, position.y + grid_size }, thickness, 0, grid_color));
        }
    }
    world_grid2D = e;
    return e;
}
