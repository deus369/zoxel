//! Used to store vertex data.
/**
*   \todo Seperate mesh data into different files.
*/
ZOXEL_COMPONENT(Material, GLuint);

extern GLuint CreateTexturedMaterial2D();

void AddGPUMaterialComponents(ecs_world_t *world, ecs_entity_t prefab)
{
    ecs_add(world, prefab, Material);
    ecs_override(world, prefab, Material);
    ecs_set(world, prefab, Material, { 0 });
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