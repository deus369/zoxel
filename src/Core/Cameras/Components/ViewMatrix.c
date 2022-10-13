//! Used in OpenGL for rendering.
typedef struct
{
    float4x4 value;
} ViewMatrix;
ECS_COMPONENT_DECLARE(ViewMatrix);