To-Do Voxels
-----

    Our worlds will be voxels.

[Back](todo-main.md)

-----

`Current`

- [ ] Chunk Neighbors
    - [ ] use hashmap lookups to quickly get chunk neighbors during build step
- [ ] Render Voxel chunks in grid - terrain
    - option for single layer chunks - 128 height, etc
    - options for 3D chunks of xyz size
    - option for textured or colored terrain
- [ ] Stream Chunks when camera enters new chunk
    - debug with arrow keys to scroll through
    - debug option test for flying through
- [ ] Rotate Planet slowly

`Improved Voxels`

- [ ] Test out smoothish like meshes for voxel grid
- [ ] Octree data for chunks
    - generate terrain in octree, opening only some nodes
    - debug nodes with lines
    - Render systems for octree
    - Start with 2x2x2 node
- [ ] Decrease octree max division as you go further from center chunk
    - highest definition around cameras
    - update chunk detail definition event, will reproduce the mesh
- [ ] Camera - ChunkStream - Move chunk event
- [ ] Generate multiple dirt textures and randomize the uvs per voxel
- [ ] Per voxel material / texture support
    - [ ] Support for Transparent Chunk Materials
    - [ ] Fix Render Ordering of Transparent Chunk Materials
- [ ] Raycast voxels
    - left click to erase
    - right click to place

-----

`Next`

- [ ] Texture voxel material support
- [ ] Chunk lighting
- [ ] Chunk Collisions

-----

`Voxels`

- [ ] Stream in chunks - based on stream chunk positions
    - [ ] if one changes position / load / unload chunks
    - [ ] pool leftover chunks?
- [ ] Create Octree Data set
    - [ ] Randomize data in chunks
    - [ ] Spawn chunks - 10k - test speed of spawning
- [ ] Draw lines around voxel nodes
- [ ] Write Test functions for voxel module

`Research`

- [ ] Research building mesh on the compute shader
    - test a compute shader first
    - test a simple triangle adding to buffer
- [ ] Investigate Raycasting method of drawing
    - https://www.shadertoy.com/view/ssGSzw
- [ ] Voxel Realtime Lighting?

-----

`Done`

First just generate a basic sphere. Next create streaming voxel world systems.
Then generate simple noise in each chunk.

- [x] Cull voxel sides during mesh building step
- [x] Render basic Voxel data
- [x] Cull edge of chunks