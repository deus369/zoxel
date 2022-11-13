//! Basic Character 2D prefab.
ecs_entity_t character2DPrefab;

void spawn_prefab_character2D(ecs_world_t *world, int2 textureSize)
{
    ecs_entity_t e = ecs_new_prefab(world, "character2D_prefab");
    printf("spawn_prefab character2D [%lu].\n", (long int) (e));
    #ifdef zoxel_transforms2D
    add_transform2Ds(world, e);
    #endif
    #ifdef zoxel_physics2D
    zoxel_add_tag(world, e, Frictioned);
    AddPhysics2DComponents(world, e);
    #endif
    // Rendering2D
    add_seed(world, e, 444);
    zoxel_add_component(world, e, Brightness);
    add_dirty(world, e);
    add_animated_noise_texture(world, e);
    add_gpu_material(world, e);
    add_gpu_texture(world, e);
    add_texture(world, e, textureSize);
    character2DPrefab = e;
}