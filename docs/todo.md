# zoxel todo list

    A todo list for zoxel porting and beyond

[Back](../readme.md)

-----

the core game: voxels > physics3D > devices > players > game

flesh out core: ui > blueprints > skeletons > animations > sounds > music

gameplay elements: stats > items > actions > skills > quests > dialogue

-----

## voxels

- [-]

    ### core

    - [ ] speed up terrain generation OctreeTerrainChunkSystem
    - [x] speed up mesh building on cpu OctreeChunkUVsBuildSystem
    - [ ] stream functions, loading new/unloading chunks based on camera
    - [ ] frustrum camera culling with chunk bounds

        #### gpu meshing

        - [x] bake mesh on gpu test
        - [ ] bake a voxel mesh on gpu test
        - [ ] bake voxels on gpu (implementation)

    ### terrain

    - [x] rewrite terrain function in octree
    - [ ] voxel lighting
    - [ ] voxel gravity
    - [ ] voxel logic (redstone)

    ### voxes

    - [ ] use octree chunks for vox models
    - [ ] greedy mesh to cull faces
    - [ ] ambient occlusion on models
    - [ ] optional black outline like before

## physics3D

- [x] basic voxel collision system
- [ ] variable gravity
- [ ] interact with chunk gravity fields

## devices

- [ ] remake data links for player with multiple devices

    ### ui

    - [ ] a devices ui that shows connected devices
    - [ ] a connect ui, when opened, shows all not connected devices

## players

- [ ] a fps controller, spawns a child camera and links to player character3D for movement

## game

- [-]

    ### core

    - [ ] save games

    ### ui

    - [ ] load save game ui, with new game, delete game buttons
    - [ ] new game ui
    - [ ] confirm ui for deletion

## ui

- [-]

    ### core

    - [ ] slider ui
    - [ ] input field
    - [ ] list ui
    - [ ] basic tooltip ui
    - [ ] add padding on buttons

    ### font

    - [ ] point editor for font
    - [ ] style data files, binary and text support?
    - [ ] ZextColor & ZextOutlineColor components
    - [ ] ui style so buttons have same or similar color/s
    - [ ] animate font with slight jiggly

## blueprints

- [ ] blueprint entities, prefabs, module, etc
- [ ] process blueprint node events
- [ ] process blueprint complete event

    ### ui

    - [ ] blueprint editor ui
    - [ ] pan view port
    - [ ] input and output nodes
    - [ ] texture output node (extend output prefab)
    - [ ] full screen toggle
    - [ ] save/load blueprints to binary files

## vox skeletons

- [ ] bone entities
- [ ] bone debug tool - overlay over vox model
- [ ] bone shader and deformation for bone matrices (bone deformation)

    ### ui

    - [ ] animation viewer for testing
    - [ ] space key to toggle animation

## animations

- [ ] animation curves on bones
- [ ] curve viewer
- [ ] blending between anims
- [ ] possibly a animation controller

## sounds

- [ ] sound ui - show soundwave of latest sounds

## music

- [-]

    ### ui

    - [ ] music editor / viewer ui showing notes and sound types
    - [ ] space key to toggle music playing
    - [ ] tooltip ui

## stats

- [ ] create basic stat and stat meta entities
- [ ] link stats to a test entity
- [ ] stat types: base, stat, state, regen, attribute, buff, etc
- [ ] damage systems
- [ ] test function with 10k stat entities
- [ ] save/load many entities stats at once into binary files

    ### ui

    - [ ] bar overlays (for health)
    - [ ] stat list ui, toggle key for test entity

## skills

- [ ] basic entities, module, prefabs, etc

## items

- [ ] basic entities, module, prefabs, etc

## actions

- [ ] basic entities, module, prefabs, etc

    ### ui

    - [ ] actionbar frame + icon ui
    - [ ] actionbar ui

## quests

- [ ] basic entities, module, prefabs, etc

## dialogue

- [ ] basic entities, module, prefabs, etc
- [ ] dialogue tree is simply a series of dialogue node entities, the root node is the first one

    ### ui

    - [ ] extend node window for a dialogue editor
    - [ ] extend node ui for dialogue node ui
    - [ ] add dialogue input for dialogue node ui

## achievements

- [ ] basic entities, module, prefabs, etc

## lore

- [ ] basic entities, module, prefabs, etc

## options

- [ ] a master volume option that effects all others, using curve values from 0 to 10
- [ ] music volume option
- [ ] sound volume option
- [ ] render distance option
- [ ] options entities that save these simple settings with ids
- [ ] option meta data that links ids saved to names / functions
- [ ] save / load options to user file

    ### ui

    - [ ] an options ui with sliders for the above options, generically for option entities

## networking

- [ ] finish sub modules

    ### ui

    - [ ] lobby ui
    - [ ] chat ui

## portals

- [ ] render textures
- [ ] portal camera and portal entities
- [ ] portal camera position systems

## post processing

- [ ] noise effect (adds noise on top)
- [ ] vignette effect (dark edges, exponential foggy)
- [ ] depth of field (add blur on distance)
- [ ] bloom (make sunny suns)

## core

- [ ] multiple apps for network testing
- [ ] get a working change filter working for flecs
    - using a simple byte component to check when it changes
    - next replicate onto my systems

## extra

- [ ] fog of war, to encourage player exploration
- [ ] place entity inside chunk, entity has a bounds, gets closest position available ??

## debug

- [ ] fps frame rate viewer - line ui for last x (3) seconds