#include "character_save_system.c"
#include "realm_characters.c"
#include "character3_lod_system.c"
#include "character3_type_debug.c"
zox_declare_system_state_event(RealmCharacters, GenerateRealm, zox_generate_realm_characters, spawn_realm_characters)

void define_systems_characters3(ecs_world_t *world) {
    zox_define_system_state_event_1(RealmCharacters, EcsOnLoad, realms.GenerateRealm, [none] realms.Realm)
    zox_system(CharacterSaveSystem, EcsPostUpdate,
        [in] transforms3.Position3D,
        [in] transforms3.Euler,
        [out] CharacterSaveHash,
        [none] SaveCharacter)
    zox_system(Character3LodSystem, EcsPostUpdate,
        [in] rendering.RenderLodDirty,
        // [in] rendering.RenderLod,
        [out] chunks3.ChunkMeshDirty,
        [none] Character3)
    zox_system(Character3TypeDebugSystem, EcsOnUpdate,
        [in] lines3.DebugCubeLines,
        [in] characters3.Character3Type,
        [out] colorz.Color,
        [none] Character3)
}