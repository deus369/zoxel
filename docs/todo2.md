# now todo #

- [ ] instancing on grass
    - [x] create vox mesh for realm grass
    - [x] use a block_vox with instance mesh, linking to the initial one
    - [x] instance system that adds to a grass render stack, position, rotation etc
    - [ ] register instance render stack for new models, flowers
    - [ ] generate grass instead of using preset one
    - [ ] support for multiple grass models

- [x] fix crash on chunk transitions - its from npcs - possibly due to mesh dirty state
- [ ] investigate this, and allow for mesh state to properly transition

- make process command to process all raw files into resources
    - then pushes to any build targets

- use custom sound for music to get similar results from lmms
    - [x] convert midi to my own music file (song1.vox)
    - [x] spawn music_file prefab with same notes / frequencies
    - [ ] music play to support sound files too
        - [ ] use piano.wav (convert from .orgg) to get same sounds as LMMS
        - [ ] alter the pitch of the loaded sound so we can align to the note of the music when playing

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
