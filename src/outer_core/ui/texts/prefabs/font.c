ecs_entity_t font_prefab;

//! meta data for a font character
ecs_entity_t spawn_font_prefab(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "font_prefab");
    zoxel_add_tag(world, e, Font);
    zoxel_add_component(world, e, FontData);
    font_prefab = e;
    return e;
}