// extern void set_vox_file(ecs_world_t *world, const ecs_entity_t e, const vox_file *vox);

void set_colors_from_vox_file(ecs_world_t *world, const ecs_entity_t e, const vox_file *vox) {
    if (!vox) return;
    int colors_length = vox->palette.values_length;
    ColorRGBs *colorRGBs = zox_get_mut(e, ColorRGBs)
    resize_memory_component(ColorRGBs, colorRGBs, color_rgb, colors_length)
    memcpy(colorRGBs->value, vox->palette.values_rgb, colors_length * sizeof(color_rgb));
    zox_modified(e, ColorRGBs)
}

void set_as_debug_vox(ecs_world_t *world, const ecs_entity_t e) {
    ColorRGBs *colorRGBs = zox_get_mut(e, ColorRGBs)
    resize_memory_component(ColorRGBs, colorRGBs, color_rgb, 1)
    colorRGBs->value[0] = (color_rgb) { 223, 239, 2 };
    zox_modified(e, ColorRGBs)
    zox_set(e, ChunkSize, { { 1, 1, 1 } })
    ChunkOctree *chunkOctree = zox_get_mut(e, ChunkOctree)
    fill_new_octree(chunkOctree, 1, 1);
    zox_modified(e, ChunkOctree)
}

byte is_vox_valid(const vox_file *vox) {
    return (vox && vox->chunks);
}

void set_vox_file(ecs_world_t *world, const ecs_entity_t e, const vox_file *vox) {
    if (!is_vox_valid(vox)) {
        set_as_debug_vox(world, e);
        return;
    }
    const byte target_depth = character_depth;
    const byte *voxels = vox->chunks[0].xyzi.voxels;
    const byte3 vox_size_original = int3_to_byte3(vox->chunks[0].size.xyz);
    // maxed based on octree size
    const int max_length = pow(2, target_depth);
    int3 vox_size = vox->chunks[0].size.xyz;
    if (vox_size.x > max_length) vox_size.x = max_length;
    if (vox_size.y > max_length) vox_size.y = max_length;
    if (vox_size.z > max_length) vox_size.z = max_length;
    ChunkOctree *chunkOctree = zox_get_mut(e, ChunkOctree)
    chunkOctree->linked = target_depth;
    fill_new_octree(chunkOctree, 0, target_depth);
    byte2 set_octree_data = (byte2) { 1, target_depth };
    byte3 position;
    int vox_index;
    for (position.x = 0; position.x < vox_size.x; position.x++) {
        for (position.y = 0; position.y < vox_size.y; position.y++) {
            for (position.z = 0; position.z < vox_size.z; position.z++) {
                vox_index = byte3_array_index(position, vox_size_original);
                set_octree_data.x = voxels[vox_index];
                byte3 node_position = position;
                set_octree_voxel_final(chunkOctree, &node_position, &set_octree_data, 0);
            }
        }
    }
    optimize_solid_nodes(chunkOctree);
    close_same_nodes(world, chunkOctree, chunkOctree->linked, 0);
    zox_modified(e, ChunkOctree)
    zox_set(e, ChunkSize, { vox_size }) // size
    set_colors_from_vox_file(world, e, vox); // colors
}

// todo: base this off prefab_chunk
ecs_entity_t spawn_prefab_vox_file(ecs_world_t *world, const int3 size) {
    zox_prefab()
    zox_prefab_name("prefab_vox_file")
    zox_add_tag(e, Vox)
    zox_prefab_add(e, ChunkSize)
    zox_prefab_add(e, ChunkOctree)
    zox_prefab_add(e, ColorRGBs)
    zox_prefab_add(e, UboGPULink)
    // extra for rendering
    add_chunk_octree(world, e, size);
    zox_prefab_set(e, VoxScale, { vox_model_scale })
    // Transforms
    add_transform3Ds(world, e, 0);
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    // Rendering
    zox_prefab_set(e, Brightness, { 1.0f })
    zox_prefab_set(e, RenderDisabled, { 1 })
    zox_prefab_set(e, MeshDirty, { 0 })
    prefab_add_mesh_basic(world, e);
    add_components_mesh_colored(world, e);
    return e;
}

ecs_entity_t spawn_vox_file(ecs_world_t *world, const ecs_entity_t prefab, const vox_file *data) {
    zox_instance(prefab)
    set_vox_file(world, e, data);
    // todo: remove RenderDisabled and just use RenderLod?
    // i can disable these later with RenderDisabled;
    // zox_set(e, RenderDisabled, { 1 })
    zox_set(e, RenderLod, { 0 })
    zox_set(e, ChunkMeshDirty, { chunk_dirty_state_trigger })
    zox_set(e, Scale1D, { 2 })
    zox_set(e, Position3D, { { 2 * (rand() % 6), 0, 2 * (rand() % 6) }})

#ifdef zox_disable_io_voxes
    zox_delete(e)
    return 0;
#endif
    return e;
}
