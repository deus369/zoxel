//! Simply pushes mouse data into Raycaster component
void MouseRaycasterSystem(ecs_iter_t *it)
{
    // printf("MouseRaycasterSystem [%i]\n", it->count);
    const Mouse *mouses = ecs_field(it, Mouse, 1);
    Raycaster *raycasters = ecs_field(it, Raycaster, 2);
    for (int i = 0; i < it->count; i++)
    {
        const Mouse *mouse = &mouses[i];
        Raycaster *raycaster = &raycasters[i];
        raycaster->value = mouse->position;
    }
}
zoxel_declare_system(MouseRaycasterSystem)