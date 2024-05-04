void MeshDirtyRestoreSystem(ecs_iter_t *it) {
    zox_field_out(MeshDirty, meshDirtys, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(MeshDirty, meshDirtys, meshDirty)
        meshDirty->value = 1;
    }
} zox_declare_system(MeshDirtyRestoreSystem)

void MeshGPURestoreSystem(ecs_iter_t *it) {
    zox_field_out(MeshGPULink, meshGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(MeshGPULink, meshGPULinks, meshGPULink)
        meshGPULink->value.x = spawn_gpu_generic_buffer();
        meshGPULink->value.y = spawn_gpu_generic_buffer();
    }
} zox_declare_system(MeshGPURestoreSystem)

void UvsGPULinkRestoreSystem(ecs_iter_t *it) {
    zox_field_out(UvsGPULink, uvsGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(UvsGPULink, uvsGPULinks, uvsGPULink)
        uvsGPULink->value = spawn_gpu_generic_buffer();
    }
} zox_declare_system(UvsGPULinkRestoreSystem)

void ColorsGPULinkRestoreSystem(ecs_iter_t *it) {
    zox_field_out(ColorsGPULink, colorsGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(ColorsGPULink, colorsGPULinks, colorsGPULink)
        colorsGPULink->value = spawn_gpu_generic_buffer();
    }
} zox_declare_system(ColorsGPULinkRestoreSystem)

void TextureRestoreSystem(ecs_iter_t *it) {
    zox_field_out(TextureGPULink, textureGPULinks, 1)
    zox_field_out(TextureDirty, textureDirtys, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(TextureGPULink, textureGPULinks, textureGPULink)
        zox_field_i_out(TextureDirty, textureDirtys, textureDirty)
        textureGPULink->value = spawn_gpu_texture_buffers();
        textureDirty->value = 1;
    }
} zox_declare_system(TextureRestoreSystem)
