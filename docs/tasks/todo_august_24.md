now
FPS independence:
- [ ] Fix Collision
    - it uses last position and adds delta...? that sounds okay tho??
- [ ] Fix Friction
- [ ] Fix Jumps

- [ ] Fade Out only when terrain loading confirmed
- [x] fix dr memory errors - EntityLinks - made single thread
- [ ] Fix that random crash ?? hard to catch
- [ ] Rename ChunkOctree to Chunk
- [ ] Remove Chunk old code
- [ ] Rename EntityLinks to ChunkLinks - more purposeful
- [x] Fix block world linking more than once

- [ ] overrideable settings - so i can override defaults

next
- [ ] finish spawning map event - then spawn player character after
    - [ ] log how long loading takes in console
    - [ ] Fix actionbar not spawning directly after character (player) has spawned, instead of timing, make a event call
- [ ] dungeon block to dig nearby dirt
    - [ ] dungeon block to place blocks
    - [ ] dungeon block to pickup dirt item using inventory

next
- [ ] optimize sound generation
    - generate sound while playing?
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
- [x] spawn entity for dungeon blocks - add spawn entity property that block vox spawn system uses - make it a prefab link
- [x] Fix mouse lock on boot game
