// todo: pre prefab functions?
// extern void clone_vox_data(ecs *world, const entity e, const entity source, byte max_depth);

entity spawn_prefab_vox(
    ecs *world,
    const entity prefab
) {
    zox_prefab_child(prefab);
    zox_prefab_name("vox");
    zox_add_tag(e, Vox);
    zox_prefab_set(e, VoxType, { vox_type_soil });
    // transform
    zox_prefab_set(e, Euler, { float3_zero });
    zox_prefab_set(e, Scale1D, { 1 });
    zox_prefab_set(e, MeshDirty, { 0 });
    zox_prefab_set(e, RenderDisabled, { 0 });
    // zox_prefab_set(e, TransformMatrix, { float4x4_identity })
    // vox
    zox_prefab_set(e, VoxScale, { vox_model_scale });
    zox_prefab_set(e, GenerateChunk, { 0 });
    zox_prefab_set(e, NodeDepth, { block_vox_depth });
    add_components_mesh_colored(world, e);
    return e;
}

// grass/rubble - generated atm
entity spawn_vox_basic(
    ecs *world,
    const entity prefab,
    byte max_depth,
    byte node_depth
) {
    zox_instance(prefab);
    spawn_gpu_mesh(world, e);
    spawn_gpu_colors(world, e);
    zox_set(e, NodeDepth, { node_depth });
    byte ddepth = max_depth - node_depth + 1;
    zox_set(e, VoxScale, { ((float) ddepth) / 64.0f });
    zox_set(e, ChunkSize, { int3_single(powers_of_two[node_depth]) });
    return e;
}