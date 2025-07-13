#include "note.c"
#include "music.c"
#include "music_generated.c"
#include "music_file.c"
#include "playlist.c"
ecs_entity_t prefab_note;
ecs_entity_t prefab_music;
ecs_entity_t prefab_music_generated;
ecs_entity_t prefab_music_file;
ecs_entity_t prefab_playlist;
// link this to realm instead
ecs_entity_t local_music;

void spawn_prefabs_musics(ecs_world_t *world) {
    prefab_note = spawn_prefab_note(world);
    prefab_music = spawn_prefab_music(world);
    prefab_music_generated = spawn_prefab_music_generated(world, prefab_music);
    prefab_music_file = spawn_prefab_music_file(world, prefab_music);
    prefab_playlist = spawn_prefab_playlist(world);
    if (prefab_realm) {
        zox_prefab_set(prefab_realm, PlaylistLink, { 0 })
        zox_prefab_set(prefab_realm, PlaylistPlaying, { 0 })
        zox_prefab_add(prefab_realm, PlaylistLinks)
    }
}
