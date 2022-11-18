//! External data/function.
bool isDebugRenderMaterial2DSystem = false;
extern float4x4 main_camera_matrix;
extern void render_entity_material2D(const float4x4 viewMatrix, GLuint material, GLuint texture, float2 position, float angle, float scale, float brightness);

//! Render 2D entities.
void RenderMaterial2DSystem(ecs_iter_t *it)
{
    // printf("RenderMaterial2DSystem %i.\n", it->count);
    Position2D *position2Ds = ecs_field(it, Position2D, 1);
    Rotation2D *rotation2Ds = ecs_field(it, Rotation2D, 2);
    Scale1D *scale2Ds = ecs_field(it, Scale1D, 3);
    Brightness *brightnesses = ecs_field(it, Brightness, 4);
    MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 5);
    TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 6);
    for (int i = 0; i < it->count; i++)
    {
        const Position2D *position = &position2Ds[i];
        const Rotation2D *rotation2D = &rotation2Ds[i];
        const Scale1D *scale1D = &scale2Ds[i];
        const Brightness *brightness = &brightnesses[i];
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
        render_entity_material2D(viewMatrix, materialGPULink->value, textureGPULink->value,
            position->value, rotation2D->value, scale1D->value, brightness->value);
    }
}
ECS_SYSTEM_DECLARE(RenderMaterial2DSystem);

/*
extern void RenderEntityMaterial2D2(const float4x4 viewMatrix, GLuint material, GLuint texture, float2 position, float angle, float2 scale, float brightness);

//! Render 2D entities.
void RenderMaterial2DScale2DSystem(ecs_iter_t *it)
{
    // printf("RenderMaterial2DScale2DSystem.\n");
    Position2D *position2Ds = ecs_field(it, Position2D, 1);
    Rotation2D *rotation2Ds = ecs_field(it, Rotation2D, 2);
    Scale2D *scale2Ds = ecs_field(it, Scale2D, 3);
    Brightness *brightnesses = ecs_field(it, Brightness, 4);
    MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 5);
    TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 6);
    for (int i = 0; i < it->count; i++)
    {
        const Position2D *position = &position2Ds[i];
        const Rotation2D *rotation2D = &rotation2Ds[i];
        const Scale2D *scale2D = &scale2Ds[i];
        const Brightness *brightness = &brightnesses[i];
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
        RenderEntityMaterial2D2(viewMatrix, materialGPULink->value, textureGPULink->value,
            position->value, rotation2D->value, scale2D->value, brightness->value);
    }
}
ECS_SYSTEM_DECLARE(RenderMaterial2DScale2DSystem);
*/