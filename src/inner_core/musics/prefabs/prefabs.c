#include "note.c"
#include "music.c"
#include "music_generated.c"
#include "music_file.c"
ecs_entity_t prefab_note;
ecs_entity_t prefab_music;
ecs_entity_t prefab_music_generated;
ecs_entity_t prefab_music_file;
// link this to realm instead
ecs_entity_t local_music;

void spawn_prefabs_musics(ecs_world_t *world) {
    prefab_note = spawn_prefab_note(world);
    prefab_music = spawn_prefab_music(world);
    prefab_music_generated = spawn_prefab_music_generated(world, prefab_music);
    prefab_music_file = spawn_prefab_music_file(world, prefab_music);
}
