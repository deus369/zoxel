void MeshDirtyRestoreSystem(ecs_iter_t *it) {
    zox_field_out(MeshDirty, meshDirtys, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(MeshDirty, meshDirtys, meshDirty)
        meshDirty->value = 1;
    }
} zox_declare_system(MeshDirtyRestoreSystem)

void MeshGPURestoreSystem(ecs_iter_t *it) {
    zox_field_out(MeshGPULink, meshGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(MeshGPULink, meshGPULinks, meshGPULink)
        meshGPULink->value.x = spawn_gpu_generic_buffer();
        meshGPULink->value.y = spawn_gpu_generic_buffer();
    }
} zox_declare_system(MeshGPURestoreSystem)

void UvsGPULinkRestoreSystem(ecs_iter_t *it) {
    zox_field_out(UvsGPULink, uvsGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(UvsGPULink, uvsGPULinks, uvsGPULink)
        uvsGPULink->value = spawn_gpu_generic_buffer();
    }
} zox_declare_system(UvsGPULinkRestoreSystem)

void ColorsGPULinkRestoreSystem(ecs_iter_t *it) {
    zox_field_out(ColorsGPULink, colorsGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ColorsGPULink, colorsGPULinks, colorsGPULink)
        colorsGPULink->value = spawn_gpu_generic_buffer();
    }
} zox_declare_system(ColorsGPULinkRestoreSystem)

void TextureRestoreSystem(ecs_iter_t *it) {
    zox_field_out(TextureGPULink, textureGPULinks, 1)
    zox_field_out(TextureDirty, textureDirtys, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(TextureGPULink, textureGPULinks, textureGPULink)
        zox_field_o(TextureDirty, textureDirtys, textureDirty)
        textureGPULink->value = spawn_gpu_texture_buffer();
        textureDirty->value = 1;
    }
} zox_declare_system(TextureRestoreSystem)
