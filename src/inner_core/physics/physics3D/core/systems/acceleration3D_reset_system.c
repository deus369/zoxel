//! Adds force to the velocity per frame.
void Acceleration3DResetSystem(ecs_iter_t *it) {
    Acceleration3D *acceleration3Ds = ecs_field(it, Acceleration3D, 1);
    for (int i = 0; i < it->count; i++) {
        Acceleration3D *acceleration3D = &acceleration3Ds[i];
        acceleration3D->value.x = 0;
        acceleration3D->value.y = 0;
        acceleration3D->value.z = 0;
    }
}
zoxel_declare_system(Acceleration3DResetSystem)