To-Do Main
-----

[Back](../../readme.md)

-----

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

`World Building`

- [ ] Biomes
- [ ] Overworld Dungeons
- [ ] Overworld Towns
- [ ] Cave Systems

`General`

- [ ] Press escape in game to go back to main menu
- [ ] Fix Render Ordering of UI
    - add a hashmap of render lists per layer (0, 1, etc), reset per frame
    - supporting layers (text over header, etc)
- [ ] Fix flashing when transfering cameras (from main menu camera to free roam one)
- [ ] Spawn Game UI for player when game state changes
    - [ ] Spawn a pause menu button (if touch screen)
- [ ] Change sky color, implement CameraColor (per entity) for background clearing
- [ ] Fix [resize_canvas] for web build

-----

`Next`

- [ ] Custom pixel art for mouse ui

- [ ] Create a render queue and sort system
    - http://realtimecollisiondetection.net/blog/?p=86
    - https://paroj.github.io/gltut/Positioning/Tut05%20Overlap%20and%20Depth%20Buffering.html

- [ ] 3D Particles
    - [ ] Particle3D with 3D cube mesh

- [ ] 2D / 3D line systems
- [ ] Grid UIs

- [ ] Camera Follower
    - [ ] Mouse scroll to zoom in / out on follower
    
- [ ] Character3Ds
    - [x] Basic Character 3D
    - [ ] Physics 3D
    - [ ] Jump ability
    - [ ] Textured Cube - Drawing
    - [ ] First person camera on character3D

- [ ] Load Shaders as entities
    - load with filenames
    - Dispose of them when closing game
    - Keep generic enough to use, so I can just load a list of files from resources

-----

`Doing List`

- [ ] Current [Voxels](todo-voxels.md)

- [ ] Current [Tiles](todo-tiles.md)

- [ ] Current [User Interface](todo-ui.md)

- [ ] Current [Cameras](todo-cameras.md)

- [ ] Current [Android](todo-android.md)

-----

A record of what i've done since i've started libre zoxel > [Done List](todo-done.md)

-----

`Modules`

Core

[Rendering](todo-rendering.md)

InnerCore

[User Interface](todo-ui.md)

[Tiles](todo-tiles.md)

[Voxels](todo-voxels.md)

Extra

[Tools](todo-tools.md)

[Devops](todo-devops.md)

[Fixes](todo-fixes.md)

-----

`After`

- [ ] RenderTextures - connect a texture to a camera

- [ ] Audio Module
    - [ ] Play basic sound
    - [ ] Import sounds
    - [ ] Generate sounds

- [ ] Flesh out modules
    - [ ] Voxels Module
    - [ ] Stats Module
    - [ ] Tiles Module

`Input`

- [ ] Handle multiple mouse devices
    - With IDs and Extraction
- [ ] Player to have connected devices
- [ ] Virtual Joysticks for touchscreen
    - Use for free roam

`Application Side`

- [ ] Support multiple Windows, one can be a FPS Debugger.
    - [ ] One Entity per Window
    - [ ] Viewport Component

`Flecs`

- [ ] Those queries still keep updating, they don't pass query checks
    - write better test functions for those

`Testing`

- [ ] Automated testing, run on server?
    - run tests weekly on pi
    - display output onto a ui somewhere

-----

[Back](../../readme.md)