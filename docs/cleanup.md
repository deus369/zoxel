// dump any notes from source in here

// todo: we should just BOOT in engine, and just set settings in nexus files

// todo: destroy block voxes if removed from chunk, check hashes / current block voxes
// todo: also check if hashes exist but voxel type has changed!

// this should only trigger if voxel updates is air, or solid (vox blocks should not close same nodes)
// todo: if voxel type == CanBlockGroup
// todo: only do this on node updated! and it's parent nodes
// should be, BlockVoxesDirty
// if block meta is minivox or vox entity:
// todo: just check for spawned entity, spawn either minivox or block entity here

// should we just set nodes here?
// - note: it may need to open or close a node
//      - if solid, and its in air of higher size, now need open node
//      - if air inside solid, solid is higher, now need open node
//      - if air and only one solid, and now all air, need close node

// todo: Give Health a level too, when it takes damage or heals, it gains xp
// todo: Give HealthRegen a level, when regens more health, it gains xp
// todo: Give Strength a level, when you do actions like lifting, it gains xp (carrying things?)
// todo: create a custom debug label here with a key to toggle...

// todo: make a sub module for render cameras
// todo: use this for ViewMatrix (current use) and use ViewMatrix just as Inverted TransformMatrix
// todo: refactor cameras do they even need ScreenPosition? we should just have CanvasLinks, and each camera is linked to a bunch? idk
// todo: fix them not spawning in each chunk
// todo: draw vertical beams where they spawn for 16 + seconds to debug

// notes: to test, set terrain to 1x1x1 chunks, disable physics, enable this systems logging
// get function from AI module for now
// todo: reorganize, perhaps move t this module up to gameplay - or a world module, that handles terrain better procedural generation stuff
// default_chunk_length
// todo: predict spawn size from octree?
// todo: handle bounds resize by shifting positions

// todo: take in npc spawn meta data, like location, biome, etc



// todo: when increasing lod, generate terrain first
// todo: fix: when render lod initial set to 2, the instances dissapear

// todo: initialize event modules can hook onto for loading i/o
//      - should occur after all modules are imported, but before game is booted
// - each module should add to a load resources event for i/o game data
// #define zox_log_boot_game
// #define zox_enable_log_start_game

// todo: set block vox resolution to 5
// todo: use component max depths on terrain
// todo: fix the texture blocks - use textures generate a regular vox model

// todo: use this to trigger a check when done state on chunks
// for now we check per frame


// this fits our font_size to our given pixel_size
// todo: perhaps make this a system / propoprety so it resizes font_size based on text updates