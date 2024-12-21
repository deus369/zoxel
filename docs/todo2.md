# now todo #

- [ ] fix fullscreening not resizing canvas
- [ ] Make a second canvas for debug uis

- [ ] reworking streaming chunks
- [ ] can add timers to spawning off chunks so its past x seconds from when they're born (bornTime)

- [x] Add PlaylistLinks to realm, and set a different playlist per scene (game/mainmenu)
- [ ] convert a directory of music files, not just one
- [-] Scenes data! main menu and game atm
- [ ] generate grass instead of using preset one
- [ ] support for multiple grass models (variations)
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


- [x] instancing on grass
    - [x] create vox mesh for realm grass
    - [x] use a block_vox with instance mesh, linking to the initial one
    - [x] instance system that adds to a grass render stack, position, rotation etc
    - [x] register instance render stack for new models, flowers

- [x] fix crash on chunk transitions - its from npcs - possibly due to mesh dirty state
- [x] investigate this, and allow for mesh state to properly transition

- make process command to process all raw files into resources
    - then pushes to any build targets

- use custom sound for music to get similar results from lmms
    - [x] convert midi to my own music file (song1.vox)
    - [x] spawn music_file prefab with same notes / frequencies
    - [ ] music play to support sound files too
        - [x] use piano.wav (convert from .orgg) to get same sounds as LMMS
        - [x] alter the pitch of the loaded sound so we can align to the note of the music when playing

// todo: add note timings, and check them all when playing
//      ^ add two sounds together
// todo: multiple musics, and playlists (musicLinks)
// todo: each music note - will check music start time - get current time, to know when to spawn sound - makes it more dynamic
