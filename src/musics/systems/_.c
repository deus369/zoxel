#include "music_play_system.c"
#include "music_generate_system.c"

void define_systems_music(ecs* world) {
    zox_system_1(MusicGenerateSystem, zoxp_mainthread,
        [in] generic.Seed,
        [in] sounds.InstrumentType,
        [out] GenerateMusic,
        [out] NoteLinks,
        [none] Music);
    zox_system_1(MusicPlaySystem, zoxp_mainthread,
        [in] MusicEnabled,
        [in] NoteLinks,
        [in] MusicSpeed,
        [out] MusicNote,
        [out] MusicTime,
        [none] Music);
}