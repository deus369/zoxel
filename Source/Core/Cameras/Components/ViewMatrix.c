//! Used in OpenGL for rendering. A Camera Frustrum.
/**
 * Refactor to use float4x4.
*/
ZOXEL_COMPONENT(ViewMatrix, float4x4);

/*typedef struct
{
    float4x4 value;
    // float value[16];
    // float* value;   // float4x4
} ViewMatrix;
ECS_COMPONENT_DECLARE(ViewMatrix);*/

// The destructor should free resources.
/*ECS_DTOR(ViewMatrix, ptr,
{
    if (ptr->value)
    {
        // printf("ECS_DTOR: Disposing view matrix [%f] \n", ptr->value[0]); // ecs_trace("Dtor");
        free(ptr->value);
    }
})

// The constructor should initialize the component value.
ECS_CTOR(ViewMatrix, ptr,
{
    // ecs_trace("Ctor");
    ptr->value = NULL;
})

ECS_MOVE(ViewMatrix, dst, src,
{
    // ecs_trace("Move");
    free(dst->value);
    dst->value = src->value;
    src->value = NULL;
})

ECS_COPY(ViewMatrix, dst, src,
{
    if (src->value)
    {
        // printf("Copying ViewMatrix.");
        free(dst->value);
        dst->value = malloc(16 * 4);
        if (dst->value == NULL) return;          // No memory
        dst->value = memcpy(dst->value, src->value, 16 * 4);
    }
})*/