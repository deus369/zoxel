

extern float4x4 mainCameraMatrix;
extern void render_unique3D(const float4x4 viewMatrix, GLuint2 mesh, GLuint material, float3 position, float4 rotation, float scale1D, float brightness, int indicies_length);

void InstanceRender3D2System(ecs_iter_t *it)
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
        // printf(" - Rendering Cube\n");
        render_unique3D(mainCameraMatrix, meshGPULink->value, materialGPULink->value,
            position->value, rotation->value, scale1D->value, brightness->value, meshIndicies2->length);
    }
}
ECS_SYSTEM_DECLARE(InstanceRender3D2System);