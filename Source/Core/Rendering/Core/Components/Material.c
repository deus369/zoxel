//! Contains a link to the Material on the GPU.
/**
*   Materials are shader program instances.
*   \todo Seperate mesh data into different files.
*/
zoxel_component(Material, GLuint);

extern GLuint CreateTexturedMaterial2D();

void AddGPUMaterialComponents(ecs_world_t *world, ecs_entity_t prefab)
{
    zoxel_set_component(world, prefab, Material, { 0 });
}

void SpawnGPUMaterial(ecs_world_t *world, ecs_entity_t e)
{
    ecs_set(world, e, Material, { CreateTexturedMaterial2D() });
}

ECS_DTOR(Material, ptr,
{
    if (ptr->value != 0)
    {
        // printf("Deleting Material on GPU.\n");
        glDeleteProgram(ptr->value);
    }
})