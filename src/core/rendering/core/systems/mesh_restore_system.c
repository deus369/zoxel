
void MeshGPURestoreSystem(ecs_iter_t *it) {
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    for (int i = 0; i < it->count; i++) {
        MeshDirty *meshDirty = &meshDirtys[i];
        meshDirty->value = 1;
    }
} zox_declare_system(MeshGPURestoreSystem)

/*void ElementGPURestoreSystem(ecs_iter_t *it) {
    InitializeEntityMesh *initializeEntityMeshs = ecs_field(it, InitializeEntityMesh, 1);
    for (int i = 0; i < it->count; i++) {
        InitializeEntityMesh *initializeEntityMesh = &initializeEntityMeshs[i];
        initializeEntityMesh->value = 1;
    }
} zox_declare_system(ElementGPURestoreSystem)*/


// todo: restore all gpu data in systems
//      > ShaderGPULinkRestoreSystem
//      > MaterialGPULinkRestoreSystem