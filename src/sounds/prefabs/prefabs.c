ecs_entity_t prefab_sound;
ecs_entity_t prefab_sound_generated;
#include "sound.c"
#include "generated_sound.c"
#include "sound_filepath.c"
#include "sound_file_instance.c"
ecs_entity_t prefab_sound_filepath;

void spawn_prefabs_sounds(ecs_world_t *world) {
    prefab_sound = spawn_prefab_sound(world);
    prefab_sound_generated = spawn_prefab_generated_sound(world, prefab_sound);
    prefab_sound_filepath = spawn_prefab_sound_filepath(world);
}
