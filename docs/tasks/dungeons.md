# dungeons

- dungeon goal - get sword - new blingy everyday nicer looking
- go to more dungeons, level up
- shit sword of fish spew



- world dungeons and instanced ones (seperate world)
- now we just need to spawn our world dungeon

# first pass dungeon mechanics
- [x] create a new block called dungeon core - give it a custom texture for visual
- [ ] when dungeon core spawns - spawn a world entity as child to chunk so we can give it a step function system
- [ ] every step update for dungeon block - spawn out a dungeon room
    - [ ] make spawn one block at a time
- [ ] make a hallway to a second room in the dungeon
- [ ] make the dungeon block dig voxels around it
- [ ] give dungeon block an inventory
- [ ] debug dungeon blocks inventory in ui
- [ ] spawn an enemy in the second room

# later
- [ ] simulate dungeon by steps, spawn a dungeon core, it will build dungeon block by block
- [ ] add dungeon tentacles, that come out of the dungeon core
    - [ ] these will be voxel based but with skeleton animation
    - [ ] it will be transparent so looks like ghost tentacles
    - [ ] they will hold blocks and move things around
- [ ] every 3 seconds it chooses a block around it to eat
- [ ] it can destroy blocks with its tentacles
- [ ] it can pickup items
- [ ] it can absorb corpses
- [ ] test function that adds that item to player - just add in during player character spawning
- [ ] dungeon core can spawn enemies
- [ ] dungeon core remembers where its tendrils extend to
