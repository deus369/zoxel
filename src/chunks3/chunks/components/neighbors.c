#define chunk_neighbors_length 6
typedef struct {
    ecs_entity_t value[chunk_neighbors_length];
} ChunkNeighbors;
zox_custom_component(ChunkNeighbors)