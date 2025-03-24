#ifndef zox_characters3D_terrain
#define zox_characters3D_terrain

#include "settings/settings.c"
#include "systems/characters3D_spawn_system.c"

void spawn_prefabs_characters3D_terrain(ecs_world_t *world) {
    set_character_terrain_settings();
}

extern ecs_entity_t prefab_character3D_npc;
// todo: pass player entity through here
void test_spawn_character_npc(ecs_world_t *world, int32_t keycode) {
    // zox_log("keydown %i\n", keycode)
    if (keycode == SDLK_l) {
        // spawn at here
        int3 chunk_position = int3_zero;
        float3 position = (float3) { 4, 12, 4 };

        const ecs_entity_t terrain = zox_get_value(local_realm, TerrainLink)
        if (!terrain) return;

        const ChunkLinks *chunk_links = zox_get(terrain, ChunkLinks)
        const ecs_entity_t chunk = int3_hashmap_get(chunk_links->value, chunk_position);
        if (!chunk) return;

        zox_log("+ spawning npc!\n")
        float4 rotation = quaternion_identity;
        byte character_lod = 0;
        byte render_disabled = 0;
        int vox_index = rand() % npc_vox_index_count;
        const ecs_entity_t vox = string_hashmap_get(files_hashmap_voxes, new_string_data(npc_voxes[vox_index]));
        const ecs_entity_2 e2 = spawn_character3D(world, prefab_character3D_npc, vox, position, rotation, character_lod, 0, 0, render_disabled);
        zox_set(e2.x, ChunkLink, { chunk })
    }
}

zox_begin_module(Characters3DTerrain)
    // todo: this kinda just spawns to be visible, perhaps keep low res characters onboard? in lower Lods SimuChunks!
    zox_system_1(Characters3DSpawnSystem, zox_pip_mainthread, [in] ChunkLodDirty, [in] ChunkOctree, [in] ChunkPosition, [in] RenderDistance, [in] RenderDisabled, [out] EntityLinks, [none] terrain.TerrainChunk)
    spawn_prefabs_characters3D_terrain(world);
    add_functions_key_down(test_spawn_character_npc);
zox_end_module(Characters3DTerrain)

#endif
