#ifndef Zoxel_Cameras
#define Zoxel_Cameras

// Tags
ECS_DECLARE(Camera);
ECS_DECLARE(CameraFollower2D);  // a tag for a camera that follows a Character2D
// Data
#include "Components/ViewMatrix.c"
#include "Components/ScreenDimensions.c"
#include "Components/FieldOfView.c"
// Prefabs
#include "Prefabs/Camera2D.c"
// Systems
#include "Systems/CameraSpawnSystem.c"
#include "Systems/ViewMatrixSystem.c"

// Remember it will destroy the prefab ones too... *facepalm*

void CamerasImport(ecs_world_t *world)
{
    ECS_MODULE(world, Cameras);
    ECS_TAG_DEFINE(world, Camera);
    ECS_TAG_DEFINE(world, CameraFollower2D); // Until fix is found. \todo Fix this, readd it back here where it belongs.
    ECS_COMPONENT_DEFINE(world, ViewMatrix);
    ECS_COMPONENT_DEFINE(world, ScreenDimensions);
    ECS_COMPONENT_DEFINE(world, FieldOfView);
    ECS_SYSTEM_DEFINE(world, ViewMatrixSystem, EcsOnUpdate, [in] ScreenDimensions, [in] FieldOfView, [out] ViewMatrix);
    SpawnCameraPrefab(world);
    ecs_add(world, cameraPrefab, CameraFollower2D);
}

void SpawnMainCamera(int2 screenDimensions)
{
    float3 spawnPosition = { 0, -0.0f, 0.8 };
    // imagine this is a forward rotation
    float4 flipRotation = quaternion_from_euler( (float3) { 0, 180 * degreesToRadians, 0 });
    float4 spawnRotation = quaternion_from_euler( (float3) { 0 * degreesToRadians, 0 * degreesToRadians, 0 * degreesToRadians });
    spawnRotation = quaternion_rotate(flipRotation, spawnRotation);
    SpawnCamera(world, spawnPosition, spawnRotation, screenDimensions);
}

void ResizeCameras(int width, int height)
{
    if (!mainCamera || !ecs_is_alive(world, mainCamera))
    {
        return;
    }
    ScreenDimensions *screenDimensions = ecs_get_mut(world, mainCamera, ScreenDimensions);
    screenDimensions->value.x = width;
    screenDimensions->value.y = height;
    ecs_modified(world, mainCamera, ScreenDimensions);
}

const float4x4 GetMainCameraViewMatrix()
{
    if (!mainCamera || !ecs_is_alive(world, mainCamera))
    {
        return CreateZeroMatrix();
    }
    const ViewMatrix *viewMatrix = ecs_get(world, mainCamera, ViewMatrix);
    return viewMatrix->value;
    // glUniformMatrix4fv(gl_view_matrix, 1, GL_FALSE, (const GLfloat*) viewMatrix);
}

//! View Matrix multipled by projection and used to distort pixel magic.
float4x4 CalculateViewMatrix(float3 position, float3 forward, float3 up)
{
    float4x4 matrix = CreateIdentityMatrix();
    float3 side = { };
    side = cross(forward, up);
    side = normalize(side);
    // float* matrix2 = (float*) &matrix;
    matrix.x.x = side.x;
    matrix.y.x = side.y;
    matrix.z.x = side.z;
    matrix.x.y = up.x;
    matrix.y.y = up.y;
    matrix.z.y = up.z;
    matrix.x.z = -forward.x;
    matrix.y.z = -forward.y;
    matrix.z.z = -forward.z;
    matrix.w.x = -position.x;
    matrix.w.y = -position.y;
    matrix.w.z = -position.z;
    return matrix;
}

void RotateMatrix(float4x4 *matrix, const float4 rotation)
{
    matrix->x.x *= rotation.x;
    matrix->y.x *= rotation.x;
    matrix->z.x *= rotation.x;
    matrix->w.x *= rotation.x;
    matrix->x.y *= rotation.y;
    matrix->y.y *= rotation.y;
    matrix->z.y *= rotation.y;
    matrix->w.y *= rotation.y;
    matrix->x.z *= rotation.z;
    matrix->y.z *= rotation.z;
    matrix->z.z *= rotation.z;
    matrix->w.z *= rotation.z;
    matrix->x.w *= rotation.w;
    matrix->y.w *= rotation.w;
    matrix->z.w *= rotation.w;
    matrix->w.w *= rotation.w;
}

    // ecs_system_enable_multithreading(world, ecs_id(ViewMatrixSystem));
    /*ecs_set_hooks(world, ViewMatrix, {
        // .on_remove = ViewMatrixDisposeSystem,
        .ctor = ecs_ctor(ViewMatrix),
        .move = ecs_move(ViewMatrix),
        .copy = ecs_copy(ViewMatrix),
        .dtor = ecs_dtor(ViewMatrix)
    });*/

// float* GetMainCameraViewMatrix2()
// {
//     if (!mainCamera || !ecs_is_alive(world, mainCamera))
//     {
//         return NULL;
//     }
//     ViewMatrix *viewMatrix = ecs_get(world, mainCamera, ViewMatrix);
//     return viewMatrix->value;
//     // glUniformMatrix4fv(gl_view_matrix, 1, GL_FALSE, (const GLfloat*) viewMatrix);
// }

    /*ecs_filter_t *Camera = ecs_filter(world, {
        .terms = {
            { ecs_id(Camera) }, 
            { ecs_id(OrthoCamera), .oper = EcsNot }
        }
    });*/
    // how to exclude
    // { ecs_id(Velocity), .oper = EcsNot }
    // ViewMatrixSetSystem - add observer for on set
    /*ecs_observer_init(world, &(ecs_observer_desc_t) {
        .filter.terms = { { ecs_id(ViewMatrix) } },
        .events = EcsOnSet,
        .callback = ViewMatrixSetSystem
    });*/
    // Add on destroy observer
    /*ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = { { ecs_id(ViewMatrix) } },
        .events = EcsOnRemove,   // EcsOnSet
        .callback = ViewMatrixDisposeSystem
    });*/
    // EcsOnSet, calculate view frustrum when screen dimensions change
    // ecs_set_hooks(world, ViewMatrix, { .dtor = ecs_dtor(ViewMatrix) });
    /*ecs_set_hooks(world, ViewMatrix, {
        // .dtor = ecs_dtor(ViewMatrix),
        //.on_set = ViewMatrixSetSystem,
        .on_remove = ViewMatrixDisposeSystem,
    });*/

    // ecs_set_hooks(world, ViewMatrix, { .dtor = ecs_dtor(ViewMatrix) });

//! Sets the ViewMatrix as thing
/*void ViewMatrixDisposeSystem(ecs_iter_t *it)
{
    ViewMatrix *viewMatrixs = ecs_field(it, ViewMatrix, 1);
    for (int i = 0; i < it->count; i++)
    {
        ViewMatrix *viewMatrix = &viewMatrixs[i];
        if (viewMatrix->value)
        {
            printf("ViewMatrixDisposeSystem: [%f]\n", viewMatrix->value[0]);
        }
        //free(viewMatrix->value);
    }
}*/

/*void ZOXEL_DECLARE_MEMORY_COMPONENT(ecs_world_t *world, void* component)
{
    ECS_COMPONENT_DEFINE(world, component);
    ecs_set_hooks(world, component, {
        .ctor = ecs_ctor(component),
        .move = ecs_move(component),
        .copy = ecs_copy(component),
        .dtor = ecs_dtor(component)
    });
}*/

#endif