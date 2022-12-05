//! This script tests array component inside multithreaded system

// Build:
// cc -std=c99 -D_DEFAULT_SOURCE -o test_array_crash include/flecs.c tests/flecs/test_array_crash.c; ./test_array_crash;

#include "../../include/flecs.h"
#include "stdlib.h"
#include "stdio.h"

const int chunk_array_length = 16 * 128 * 16;

// First define the macros I am using

//! Define a Memory component, with an array of a single data type.
#define zoxel_memory_component(name, type)\
typedef struct\
{\
    int length;\
    type *value;\
} name;\
ECS_COMPONENT_DECLARE(name);\
ECS_CTOR(name, ptr,\
{\
    ptr->length = 0;\
    ptr->value = NULL;\
})\
ECS_DTOR(name, ptr,\
{\
    if (ptr->value)\
    {\
        free(ptr->value);\
    }\
})\
ECS_MOVE(name, dst, src,\
{\
    if (dst->length != 0)\
    {\
        free(dst->value);\
    }\
    dst->value = src->value;\
    src->value = NULL;\
    dst->length = src->length;\
    src->length = 0;\
})\
ECS_COPY(name, dst, src, {\
    if (src->value)\
    {\
        if (dst->length != 0)\
        {\
            free(dst->value);\
        }\
        int memory_length = src->length * sizeof(type);\
        dst->length = src->length;\
        dst->value = malloc(memory_length);\
        if (dst->value != NULL) \
        {\
            dst->value = memcpy(dst->value, src->value, memory_length);\
        }\
    }\
})

#define zoxel_memory_component_define(world, ComponentName)\
{\
    ECS_COMPONENT_DEFINE(world, ComponentName);\
    ecs_set_hooks(world, ComponentName, {\
        .ctor = ecs_ctor(ComponentName),\
        .move = ecs_move(ComponentName),\
        .copy = ecs_copy(ComponentName),\
        .dtor = ecs_dtor(ComponentName)\
    });\
}

#define zoxel_component(name, type)\
typedef struct\
{\
    type value;\
} name;\
ECS_COMPONENT_DECLARE(name)

//! Multithreaded System Definition
#define zoxel_system(world, id_, phase, ...)\
{ \
    ecs_system_desc_t desc = {0}; \
    ecs_entity_desc_t edesc = {0}; \
    edesc.id = ecs_id(id_);\
    edesc.name = #id_;\
    edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0); \
    edesc.add[1] = (phase); \
    desc.entity = ecs_entity_init(world, &edesc);\
    desc.query.filter.expr = #__VA_ARGS__; \
    desc.callback = id_; \
    desc.multi_threaded = 1; \
    ecs_id(id_) = ecs_system_init(world, &desc); \
} \
ecs_assert(ecs_id(id_) != 0, ECS_INVALID_PARAMETER, NULL);

//! Adds a component but also adds override to an entity.
#define zoxel_add(world, entity, T)\
    ecs_add(world, entity, T);\
    ecs_override(world, entity, T)

#define zoxel_set(world, entity, T, ...)\
    ecs_set_id(world, entity, ecs_id(T), sizeof(T), &(T)__VA_ARGS__);\
    ecs_override_id(world, entity, ecs_id(T))

#define initialize_memory_component_non_pointer(component, dataType, length_)\
    component.length = length_;\
    component.value = (dataType*) malloc(length_ * sizeof(dataType));

#define initialize_memory_component(component, dataType, length_)\
{\
    component->length = length_;\
    component->value = (dataType*) malloc(length_ * sizeof(dataType));\
}

zoxel_memory_component(Chunk, unsigned char);
zoxel_memory_component(ChunkNeighbors, ecs_entity_t);
zoxel_component(ChunkGenerate, unsigned char);
zoxel_component(ChunkDirty, unsigned char);

// Randomizes chunk data
void set_chunk_data(ecs_world_t *world, ecs_entity_t e)
{
    Chunk chunk = { };
    initialize_memory_component_non_pointer(chunk, unsigned char, chunk_array_length);
    for (int i = 0; i < chunk_array_length; i++)
    {
        chunk.value[0] = rand() % 256;
    }
    ecs_set(world, e, Chunk, { chunk.length, chunk.value });
}

void set_chunk_neighbors(ecs_world_t *world, ecs_entity_t e, ecs_entity_t chunk_other)
{
    ChunkNeighbors chunkNeighbors = { };
    initialize_memory_component_non_pointer(chunkNeighbors, ecs_entity_t, 1);
    chunkNeighbors.value[0] = chunk_other;
    ecs_set(world, e, ChunkNeighbors, { chunkNeighbors.length, chunkNeighbors.value });
}

void ChunkGenerateSystem(ecs_iter_t *it)
{
    ChunkGenerate *chunkGenerates = ecs_field(it, ChunkGenerate, 1);
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 2);
    Chunk *chunks = ecs_field(it, Chunk, 3);
    for (int i = 0; i < it->count; i++)
    {
        ChunkGenerate *chunkGenerate = &chunkGenerates[i];
        if (chunkGenerate->value != 1)
        {
            continue;
        }
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value != 0)
        {
            continue;
        }
        chunkGenerate->value = 0;
        chunkDirty->value = 1;
        Chunk *chunk = &chunks[i];
        initialize_memory_component(chunk, unsigned char, chunk_array_length);
        printf("Generating chunk [%lu]\n", (long int) it->entities[i]);
        for (int j = 0; j < chunk_array_length; j++)
        {
            chunk->value[j] = rand() % 256;
            if (j < 16)
            {
                printf("     [%i]\n", (int) chunk->value[j]);
            }
        }
        printf("Generated chunk [%lu]\n", (long int) it->entities[i]);
    }
}
ECS_SYSTEM_DECLARE(ChunkGenerateSystem);

//! Builds a mesh data from the chunk!
void ChunkBuildSystem(ecs_iter_t *it)
{
    // printf("[ChunkBuildSystem] GenerateChunk was changed.\n");
    ChunkDirty *entityDirtys = ecs_field(it, ChunkDirty, 1);
    const Chunk *chunks = ecs_field(it, Chunk, 2);
    const ChunkNeighbors *chunkNeighbors = ecs_field(it, ChunkNeighbors, 3);
    for (int i = 0; i < it->count; i++)
    {
        ChunkDirty *chunkDirty = &entityDirtys[i];
        if (chunkDirty->value != 1)
        {
            continue;
        }
        chunkDirty->value = 0;
        const Chunk *chunk = &chunks[i];
        const ChunkNeighbors *chunkNeighbors2 = &chunkNeighbors[i];
        // now get neighbor and do checks
        const Chunk *chunk_other = chunkNeighbors2->value[0] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[0], Chunk);
        //const Chunk *chunk_other = NULL;
        // now just test by accessing other chunks array
        printf("Building chunk [%lu]\n", (long int) it->entities[i]);
        if (chunk_other == NULL)
        {
            printf("    -> chunk_other is NULL\n");
        }
        else
        {
            for (int j = 0; j < 16; j++)
            {
                printf("     [%i]\n", (int) chunk_other->value[j]);
            }
        }
        printf("Built chunk [%lu]\n", (long int) it->entities[i]);
    }
}
ECS_SYSTEM_DECLARE(ChunkBuildSystem);

int main(int argc, char *argv[])
{
    ecs_world_t *world = ecs_init_w_args(argc, argv);
    zoxel_memory_component_define(world, Chunk);
    zoxel_memory_component_define(world, ChunkNeighbors);
    ECS_COMPONENT_DEFINE(world, ChunkGenerate);
    ECS_COMPONENT_DEFINE(world, ChunkDirty);
    // spawn system
    zoxel_system(world, ChunkGenerateSystem, EcsPostLoad, [out] ChunkGenerate, [out] ChunkDirty, [out] Chunk);
    zoxel_system(world, ChunkBuildSystem, EcsOnUpdate, [out] ChunkDirty, [in] Chunk, [in] ChunkNeighbors);
    // spawn 2 chunks
    ecs_entity_t chunk_prefab = ecs_new_prefab(world, "chunk_prefab");
    zoxel_add(world, chunk_prefab, Chunk);
    zoxel_add(world, chunk_prefab, ChunkNeighbors);
    zoxel_set(world, chunk_prefab, ChunkDirty, { 0 });
    zoxel_set(world, chunk_prefab, ChunkGenerate, { 1 });
    printf("Spawned chunk_prefab [%lu]\n", (long int) chunk_prefab);
    ecs_progress(world, 0);

    ecs_entity_t e1 = ecs_new_w_pair(world, EcsIsA, chunk_prefab);
    // set_chunk_data(world, e1);
    printf("Spawned chunk [%lu]\n", (long int) e1);
    ecs_entity_t e2 = ecs_new_w_pair(world, EcsIsA, chunk_prefab);
    // set_chunk_data(world, e2);
    printf("Spawned chunk [%lu]\n", (long int) e2);
    // set link from one to another
    set_chunk_neighbors(world, e1, e2);
    set_chunk_neighbors(world, e2, 0); // e1);
    // progress once
    for (int i = 0; i < 16; i++)
    {
        ecs_progress(world, 0);
    }
    // le end - if made it this far it's a success
    printf("RESULT: SUCCESS\n");
    return ecs_fini(world);
}