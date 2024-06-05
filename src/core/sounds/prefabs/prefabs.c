ecs_entity_t prefab_sound;
ecs_entity_t prefab_sound_generated;
#include "sound.c"
#include "generated_sound.c"

void spawn_prefabs_sounds(ecs_world_t *world) {
    prefab_sound = spawn_prefab_sound(world);
    prefab_sound_generated = spawn_prefab_generated_sound(world, prefab_sound);
}
