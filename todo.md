# zoxel todo list

[Back](readme.md)

-----

## core

- [ ] multiple apps for network testing
- [ ] get a working change filter working for flecs
    - using a simple byte component to check when it changes
    - next replicate onto my systems

## ui

- [ ] finish other modules ui parts
- [ ] finish sub modules

    ### core

    - [ ] slider ui
    - [ ] input field
    - [ ] list ui
    - [ ] basic tooltip ui

## debug

- [ ] fps frame rate viewer - line ui for last x (3) seconds

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

## networking

- [ ] finish sub modules

    ### ui

    - [ ] lobby ui
    - [ ] chat ui

## devices

- [ ] remake data links for player with multiple devices

    ### ui

    - [ ] a devices ui that shows connected devices
    - [ ] a connect ui, when opened, shows all not connected devices

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

## voxels

- [ ] complete all sub modules

    ### core

    - [ ] bake mesh on gpu test
    - [ ] stream functions, loading/unloading chunks based on camera
    - [ ] bake voxels on gpu (implementation)

    ### terrain

    - [ ] rewrite terrain function in octree
    - [ ] voxel lighting systems

    ### vox

    - [ ] use octree chunks for vox models
    - [ ] greedy mesh to cull faces
    - [ ] ambient occlusion on models

    ## skeletons

    - [ ] bone entities
    - [ ] bone debug tool - overlay over vox model
    - [ ] bone shader and deformation for bone matrices (bone deformation)

        ### ui

        - [ ] animation viewer for testing
        - [ ] space key to toggle animation

    ### extra

    - [ ] fog of war, to encourage player exploration
    - [ ] place entity inside chunk, entity has a bounds, gets closest position available

## physics3D

- [ ] voxel collision system
- [ ] voxel collision response system

## players

- [ ] a fps controller, spawns a child camera and links to player character3D for movement

## sounds

- [ ] sound ui - show soundwave of latest sounds

## music

- [ ] finish sub modules

    ### ui

    - [ ] music editor / viewer ui showing notes and sound types
    - [ ] space key to toggle music playing
    - [ ] tooltip ui

## portals

- [ ] render textures
- [ ] portal camera and portal entities
- [ ] portal camera position systems

## post processing

- [ ] noise effect (adds noise on top)
- [ ] vignette effect (dark edges, exponential foggy)
- [ ] depth of field (add blur on distance)
- [ ] bloom (make sunny suns)

## game

- [ ] complete all sub modules

    ### core

    - [ ] save games

    ### ui

    - [ ] load save game ui, with new game, delete game buttons
    - [ ] new game ui
    - [ ] confirm ui for deletion

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