
void MeshDirtyRestoreSystem(ecs_iter_t *it) {
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    for (int i = 0; i < it->count; i++) {
        MeshDirty *meshDirty = &meshDirtys[i];
        meshDirty->value = 1;
    }
} zox_declare_system(MeshDirtyRestoreSystem)

void MeshGPURestoreSystem(ecs_iter_t *it) {
    MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 1);
    for (int i = 0; i < it->count; i++) {
        MeshGPULink *meshGPULink = &meshGPULinks[i];
        meshGPULink->value.x = spawn_gpu_generic_buffer();
        meshGPULink->value.y = spawn_gpu_generic_buffer();
    }
} zox_declare_system(MeshGPURestoreSystem)

void UvsGPULinkRestoreSystem(ecs_iter_t *it) {
    UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 1);
    for (int i = 0; i < it->count; i++) {
        UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        uvsGPULink->value = spawn_gpu_generic_buffer();
    }
} zox_declare_system(UvsGPULinkRestoreSystem)

void ColorsGPULinkRestoreSystem(ecs_iter_t *it) {
    ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 1);
    for (int i = 0; i < it->count; i++) {
        ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        colorsGPULink->value = spawn_gpu_generic_buffer();
    }
} zox_declare_system(ColorsGPULinkRestoreSystem)

/*void ElementGPURestoreSystem(ecs_iter_t *it) {
    InitializeEntityMesh *initializeEntityMeshs = ecs_field(it, InitializeEntityMesh, 1);
    for (int i = 0; i < it->count; i++) {
        InitializeEntityMesh *initializeEntityMesh = &initializeEntityMeshs[i];
        initializeEntityMesh->value = 1;
    }
} zox_declare_system(ElementGPURestoreSystem)*/
