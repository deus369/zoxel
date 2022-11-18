

extern void render_entity_material2D_and_mesh(const float4x4 viewMatrix, GLuint2 mesh, GLuint material, GLuint texture, float2 position, float angle, float scale, float brightness);

//! Render 2D entities.
void RenderMeshMaterial2DSystem(ecs_iter_t *it)
{
    // printf("RenderMeshMaterial2DSystem %i.\n", it->count);
    Position2D *position2Ds = ecs_field(it, Position2D, 1);
    Rotation2D *rotation2Ds = ecs_field(it, Rotation2D, 2);
    Scale1D *scale2Ds = ecs_field(it, Scale1D, 3);
    Brightness *brightnesses = ecs_field(it, Brightness, 4);
    MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 6);
    TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 7);
    for (int i = 0; i < it->count; i++)
    {
        const Position2D *position = &position2Ds[i];
        const Rotation2D *rotation2D = &rotation2Ds[i];
        const Scale1D *scale1D = &scale2Ds[i];
        const Brightness *brightness = &brightnesses[i];
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const MaterialGPULink *materialGPULink = &materialGPULinks[i];
        const TextureGPULink *textureGPULink = &textureGPULinks[i];
        if (materialGPULink->value == 0)
        {
            if (isDebugRenderMaterial2DSystem)
            {
                printf("RenderMaterial2DSystem Material Error: At [%i]. Entity [%lu].\n", i, (long int) (it->entities[i]));
            }
            continue;
        }
        else
        {
            if (isDebugRenderMaterial2DSystem)
            {
                printf("RenderMaterial2DSystem Material: At [%i]. Entity [%lu].\n", i, (long int) (it->entities[i]));
            }
        }
        float4x4 viewMatrix;
        if (!ecs_has(it->world, it->entities[i], ElementRender))
        {
            viewMatrix = main_camera_matrix;
        }
        else
        {
            viewMatrix = ui_camera_matrix;
        }
        render_entity_material2D_and_mesh(viewMatrix, meshGPULink->value, materialGPULink->value, textureGPULink->value,
            position->value, rotation2D->value, scale1D->value, brightness->value);
        // printf("Rendering 2D mesh material [%lu]\n", (long int) it->entities[i]);
    }
}
ECS_SYSTEM_DECLARE(RenderMeshMaterial2DSystem);
