//! Contains a link to the MaterialGPULink on the GPU.
/**
*   Materials are shader program instances.
*   \todo Seperate mesh data into different files.
*/
zoxel_component(MaterialGPULink, GLuint);

//! Grab from opengl part.
extern GLuint CreateTexturedMaterial2D();

void AddGPUMaterialComponents(ecs_world_t *world, ecs_entity_t prefab)
{
    zoxel_set_component(world, prefab, MaterialGPULink, { 0 });
}

void SpawnGPUMaterial(ecs_world_t *world, ecs_entity_t e)
{
    ecs_set(world, e, MaterialGPULink, { CreateTexturedMaterial2D() });
}

ECS_DTOR(MaterialGPULink, ptr,
{
    if (ptr->value != 0)
    {
        // printf("Deleting MaterialGPULink [%i] on GPU.\n", ptr->value);
        glDeleteProgram(ptr->value);
    }
})