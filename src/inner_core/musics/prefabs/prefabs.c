ecs_entity_t prefab_music;
ecs_entity_t local_music;
ecs_entity_t prefab_note;
#include "music.c"
#include "note.c"

void spawn_prefabs_musics(ecs_world_t *world) {
    prefab_note = spawn_prefab_note(world);
    prefab_music = spawn_prefab_music(world);
}
