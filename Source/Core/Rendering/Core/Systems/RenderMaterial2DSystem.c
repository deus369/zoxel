//! External data/function.
extern float4x4 mainCameraMatrix;
extern void RenderEntityMaterial2D(const float4x4 viewMatrix, GLuint material, GLuint texture, float2 position, float angle, float scale, float brightness);

//! Render 2D entities.
void RenderMaterial2DSystem(ecs_iter_t *it)
{
    Position2D *position2Ds = ecs_field(it, Position2D, 1);
    Rotation2D *rotation2Ds = ecs_field(it, Rotation2D, 2);
    Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    Brightness *brightnesses = ecs_field(it, Brightness, 4);
    Material *materials = ecs_field(it, Material, 5);
    TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 6);
    for (int i = 0; i < it->count; i++)
    {
        const Position2D *position = &position2Ds[i];
        const Rotation2D *rotation2D = &rotation2Ds[i];
        const Scale1D *scale1D = &scale1Ds[i];
        const Brightness *brightness = &brightnesses[i];
        const Material *material = &materials[i];
        const TextureGPULink *textureGPULink = &textureGPULinks[i];
        // Add to Render Queue
        // printf("    Bob's Position2D is {%f, %f}\n", position.value.x, position.value.y);
        RenderEntityMaterial2D(mainCameraMatrix, material->value, textureGPULink->value,
            position->value, rotation2D->value, scale1D->value, brightness->value);
    }
}
ECS_SYSTEM_DECLARE(RenderMaterial2DSystem);