extern float4x4 main_camera_matrix;

void Render3DSystem(ecs_iter_t *it)
{
    const Position *positions = ecs_field(it, Position, 1);
    const Rotation *rotations = ecs_field(it, Rotation, 2);
    const Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    const Brightness *brightnesses = ecs_field(it, Brightness, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 6);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 7);
    for (int i = 0; i < it->count; i++)
    {
        const Position *position = &positions[i];
        const Rotation *rotation = &rotations[i];
        const Scale1D *scale1D = &scale1Ds[i];
        const Brightness *brightness = &brightnesses[i];
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const MaterialGPULink *materialGPULink = &materialGPULinks[i];
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        // printf(" - Rendering 3D Mesh [%lu]\n", (long int) it->entities[i]);
        if (opengl_set_material(materialGPULink->value))
        {
            opengl_set_mesh(meshGPULink->value);
            if (opengl_set_material3D_properties(materialGPULink->value,
                main_camera_matrix, position->value, rotation->value, scale1D->value, brightness->value) == -1)
            {
                return;
            }
            opengl_draw_triangles(meshIndicies2->length);
            opengl_disable_opengl_program();
            // printf("Render3DSystem [%lu]\n", (long int) it->entities[i]);
        }
    }
}
ECS_SYSTEM_DECLARE(Render3DSystem);