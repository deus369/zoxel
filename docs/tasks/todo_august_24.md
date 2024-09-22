now
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
