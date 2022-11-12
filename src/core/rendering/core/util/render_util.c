//! Add mesh components to an entity prefab
void add_unique_mesh_components(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_set_component(world, e, Brightness, { 1 });
    add_gpu_mesh(world, e);
    add_gpu_material(world, e);
    add_gpu_texture(world, e);
    //! \todo Fix: Causes a Flecs memory leak?!?! Temporarily commented out.
    zoxel_add_component(world, e, MeshVertices);
    zoxel_add_component(world, e, MeshIndicies);
}