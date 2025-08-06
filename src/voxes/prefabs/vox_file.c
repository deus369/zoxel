

// todo: base this off prefab_chunk
ecs_entity_t spawn_prefab_vox_file(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("vox_file")
    zox_add_tag(e, Vox)
    zox_prefab_add(e, ChunkSize)
    zox_prefab_add(e, VoxelNode)
    zox_prefab_set(e, ColorRGBs, { 0, NULL });
    zox_prefab_add(e, UboGPULink)
    // extra for rendering
    zox_prefab_set(e, VoxScale, { vox_model_scale })
    // Transforms
    zox_prefab_set(e, Position3D, { float3_zero })
    zox_prefab_set(e, Rotation3D, { float4_identity })
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    // Rendering
    zox_prefab_set(e, Brightness, { 1.0f })
    zox_prefab_set(e, RenderDisabled, { 1 })
    zox_prefab_set(e, MeshDirty, { 0 })
    prefab_add_mesh_basic(world, e);
    add_components_mesh_colored(world, e);
    return e;
}

ecs_entity_t spawn_vox_file(ecs_world_t *world,
    const ecs_entity_t prefab,
    const vox_file *data,
    const char* filename
) {
    // model_lod
    zox_neww(model)
    char name[128];
    sprintf(name, "vox_file_%s", filename);
    zox_set_unique_name(model, name); // "file_model");
    ModelLods modelLods;
    for (int i = 0; i < max_vox_file_lods; i++) {
        zox_instance(prefab)
        zox_set(e, RenderLod, { i })
        zox_set(e, VoxScale, { vox_model_scale }) // this needs setting again
        zox_set(e, ChunkMeshDirty, { chunk_dirty_state_trigger })
        set_vox_file(world, e, data);
        modelLods.value[i] = e;
    }
    zox_set_ptr(model, ModelLods, modelLods)
    return model;
}
