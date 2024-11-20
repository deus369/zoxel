# now todo #

- [ ] instancing on grass
    - [ ] create vox mesh for realm grass
    - [ ] use a block_vox with instance mesh, linking to the initial one
    - [ ] instance system that adds to a grass render stack, position, rotation etc
    - [ ] register instance render stack for new models, flowers
    - [ ] support for multiple grass models

- [ ] start screen
- [ ] influence sphere for bones
- [ ] debug bone influence spheres
- [ ] support for bigger vox meshes
    - [ ] needs multiple chunks
    - [ ] pass in bones to each child chunk
- [ ] join head and body as single vox (add head onto body, use this)
    - [ ] join_vox(body_vox, head_vox, 0, 22, -3) last is offset
    - [ ] for hips, we just join it again
- [ ] fix item voxel textures - world items
- [ ] fix vox item textures - block voxes


- [ ] refactor transform to use flecs relationships EcsChildOf
    - [ ] do this for bones for now
    - [ ] test initially for main functions
