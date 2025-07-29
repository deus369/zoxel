#ifndef zox_dungeons
#define zox_dungeons

#include "settings/_.c"
zox_declare_tag(Dungeon)
zox_declare_tag(DungeonCore)
#include "prefabs/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Dungeons)
    zox_define_tag(Dungeon)
    zox_define_tag(DungeonCore)
    // main thread as it spawns currently
    zox_system_1(DungeonBlockSystem, EcsOnUpdate,
            [in] timing.TimerState,
            [in] chunks3.ChunkLink,
            [none] blocks.BlockDungeon)
    add_hook_spawn_blocks(&spawn_block_dungeon_blocks);
    add_hook_spawned_block(&spawn_world_dungeon_core);
zox_end_module(Dungeons)

#endif