typedef uint (*DebugLabelEvent)(
    ecs_world_t *world,
    const ecs_entity_t player,
    char *buffer,
    const uint size,
    uint index
);

typedef struct {
    DebugLabelEvent value;
} DebugLabelData;
zox_custom_component(DebugLabelData)