extern unsigned char renderer_layer;
extern void render_entity_material2D_and_mesh(const float4x4 viewMatrix, GLuint2 mesh, GLuint material, GLuint texture, float2 position,
    float angle, float scale, float brightness, unsigned char layer);

//! Render 2D entities.
void RenderMeshMaterial2DSystem(ecs_iter_t *it)
{
    Position2D *position2Ds = ecs_field(it, Position2D, 1);
    Rotation2D *rotation2Ds = ecs_field(it, Rotation2D, 2);
    Scale1D *scale2Ds = ecs_field(it, Scale1D, 3);
    Layer2D *layer2Ds = ecs_field(it, Layer2D, 4);
    Brightness *brightnesses = ecs_field(it, Brightness, 5);
    MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 6);
    MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 7);
    TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 8);
    for (int i = 0; i < it->count; i++)
    {
        const Layer2D *layer2D = &layer2Ds[i];
        if (layer2D->value != renderer_layer)
        {
            continue;
        }
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
                zoxel_log("RenderMaterial2DSystem Material Error: At [%i]. Entity [%lu].\n", i, (long int) (it->entities[i]));
            }
            continue;
        }
        else
        {
            if (isDebugRenderMaterial2DSystem)
            {
                zoxel_log("RenderMaterial2DSystem Material: At [%i]. Entity [%lu].\n", i, (long int) (it->entities[i]));
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
            position->value, rotation2D->value, scale1D->value, brightness->value, layer2D->value);
        // zoxel_log("Rendering 2D mesh material [%lu]\n", (long int) it->entities[i]);
    }
}
zoxel_declare_system(RenderMeshMaterial2DSystem)