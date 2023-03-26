//! Destroys events after one frame.
void DestroyInFrameSystem(ecs_iter_t *it) {
    for (int i = 0; i < it->count; i++)
    {
        ecs_delete(it->world, it->entities[i]);
    }
}
zoxel_declare_system(DestroyInFrameSystem)