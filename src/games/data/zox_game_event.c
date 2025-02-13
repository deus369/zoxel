typedef struct {
    void (*value)(ecs_world_t*, ecs_entity_t, byte, byte);
} zox_game_event;

zoxel_dynamic_array(zox_game_event)
// should keep function pointers
// create_is_in_array_d(int)
