now
- [ ] Quantity Labels for Items
- [ ] Minivox Textures
- [ ] Save/Load character User Data (items, stats, etc)
- [ ] Save/Load Chunks that are edited
- [ ] Save/Load NPCs
- [ ] Batch Rendering for Grass Models
- [ ] Animated Grass Vertices in shader
- [ ] Textured World Items
- [ ] Basic Dungeon Layout Data
- [ ] Tooltips on Taskbar Icons
- [ ] Simple Editable Text files for Character Presets (designer predefined)
- [ ] Create Dungeon Block Texture for Bricks
- [ ] UI Close event - use for taskbar toggling
- [ ] Status Window
- [ ] Mana/Energy Statbars for player ui
- [ ] Voxel Name Selection Tooltip at bottom right
- [ ] Character Name Selection Tooltip at bottom right
- [ ] 3D UI panels
    - add text to healthbars
- [ ] Spawn Dungeon Blocks into world terrain
    - give them stats
    - give block world a activate chunk distance
    - let them spawn from 10 chunks away
- [ ] Vox Combine System
    - [ ] Equipment Slot for Hat
    - [ ] Hat Item
    - [ ] Combine hat onto character
    - [ ] Equipment slot ui
    - [ ] Equip Action when drag onto equipment slot
- [ ] Make color spawning persistent properly, atm changes every loading
- [ ] Voxel Stuck System - will reposition npcs that are trapped inside voxels for more than x seconds

FPS independence:
- [ ] Fix Collision
    - it uses last position and adds delta...? that sounds okay tho??
- [ ] Fix Friction
- [ ] Fix Jumps
- [ ] Fade Out only when terrain loading confirmed
- [ ] Rename ChunkOctree to Chunk
- [ ] Remove Chunk old code
- [ ] Rename EntityLinks to ChunkLinks - more purposeful
- [ ] overrideable settings - so i can override defaults

next
- [ ] log how long loading takes in console
spawned, instead of timing, make a event call
- [ ] dungeon block to dig nearby dirt
- [ ] dungeon block to place blocks
- [ ] dungeon block to pickup dirt item using inventory

next
- [ ] generate sound data per frame while playing (use later for 3D effects)
- [ ] gpu instancing on grass / minivox meshes
- [ ] start screen before main menu spawns - for user input
- [ ] generate terrain lods based on chunk lods
- [ ] update terrain generation when lod updates, if octree data hasn't been set that far
- [ ] do the same with character voxes
- [ ] save load bounds, and update bounds only when generates latest resolution
- [ ] ChunkData save/load to savefile

never
- [ ] live updates on game data files so i can see modifications in real time

done
- [x] fix dr memory errors - EntityLinks - made single thread
- [x] Fix that random crash ?? hard to catch
- [x] Fix block world linking more than once
- [x] finish spawning map event - then spawn player character after
- [x] Fix actionbar not spawning directly after character (player) has - [x] spawn entity for dungeon blocks - add spawn entity property that block vox spawn system uses - make it a prefab link
- [x] Fix mouse lock on boot gam
- [x] optimize sound generation
