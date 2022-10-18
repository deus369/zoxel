#ifndef Zoxel_Cameras
#define Zoxel_Cameras

// Tags
ECS_DECLARE(Camera);
ECS_DECLARE(CameraFollower2D);  // a tag for a camera that follows a Character2D
// Data
#include "Components/ViewMatrix.c"
#include "Components/ScreenDimensions.c"
#include "Components/FieldOfView.c"
// Systems
#include "Systems/CameraSpawnSystem.c"
#include "Systems/ViewMatrixSystem.c"

// Remember it will destroy the prefab ones too... *facepalm*

// The destructor should free resources.
ECS_DTOR(ViewMatrix, ptr, {
    if (ptr->value)
    {
        // printf("ECS_DTOR: Disposing view matrix [%f] \n", ptr->value[0]); // ecs_trace("Dtor");
        free(ptr->value);
    }
})

// The constructor should initialize the component value.
ECS_CTOR(ViewMatrix, ptr, {
    // ecs_trace("Ctor");
    ptr->value = NULL;
})

ECS_MOVE(ViewMatrix, dst, src, {
    // ecs_trace("Move");
    free(dst->value);
    dst->value = src->value;
    src->value = NULL;
})

ECS_COPY(ViewMatrix, dst, src, {
    if (src->value)
    {
        // printf("Copying ViewMatrix.");
        free(dst->value);
        dst->value = malloc(16 * 4);
        if (dst->value == NULL) return;          // No memory
        dst->value = memcpy(dst->value, src->value, 16 * 4);
    }
})

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

void CamerasImport(ecs_world_t *world)
{
    ECS_MODULE(world, Cameras);
    ECS_TAG_DEFINE(world, Camera);
    ECS_COMPONENT_DEFINE(world, ViewMatrix);
    ECS_COMPONENT_DEFINE(world, ScreenDimensions);
    ECS_COMPONENT_DEFINE(world, FieldOfView);
    ECS_SYSTEM_DEFINE(world, ViewMatrixSystem, EcsOnUpdate, [in] ScreenDimensions, [in] FieldOfView, [out] ViewMatrix);
    // SetMultiThreaded(world, ecs_id(ViewMatrixSystem));
    ecs_set_hooks(world, ViewMatrix, {
        // .on_remove = ViewMatrixDisposeSystem,
        .ctor = ecs_ctor(ViewMatrix),
        .move = ecs_move(ViewMatrix),
        .copy = ecs_copy(ViewMatrix),
        .dtor = ecs_dtor(ViewMatrix)
    });
    SpawnCameraPrefab(world);
}

void SpawnMainCamera(int2 screenDimensions)
{
    float3 spawnPosition = { 0, 0, 0 };
    float4 spawnRotation = { 0, 0, 0, 1 };
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
    screenDimensions->value.y = height; //{ width, height };
    ecs_modified(world, mainCamera, ScreenDimensions);
}

const float* GetMainCameraViewMatrix()
{
    if (!mainCamera || !ecs_is_alive(world, mainCamera))
    {
        return NULL;
    }
    const ViewMatrix *viewMatrix = ecs_get(world, mainCamera, ViewMatrix);
    return viewMatrix->value;
    // glUniformMatrix4fv(gl_view_matrix, 1, GL_FALSE, (const GLfloat*) viewMatrix);
}

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

#endif