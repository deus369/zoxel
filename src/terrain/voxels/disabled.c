

void process_disabled_block_vox(ecs_world_t *world, SpawnBlock *data, byte is_unique_vox) {
    if (!disable_block_voxes) {
        return;
    }
    if (data->vox && is_unique_vox) {
        zox_delete(data->vox)
    }
    if (data->prefab_block_vox) {
        zox_delete(data->prefab_block_vox)
        data->prefab_block_vox = 0;
    }
    ecs_entity_t vox = spawn_vox_generated_invisible(world, prefab_vox_generated, color_gray);
    zox_set_unique_name(vox, "unknown");
    zox_set(vox, VoxType, { vox_type_soil })
    // settings!
    data->vox = vox;
    data->prefab_texture = prefab_vox_texture;
    data->model = 0;
    data->tag = 0;
    data->bake_vox = 1;
    data->color = color_gray;
    // data->disable_collision = 0;
}