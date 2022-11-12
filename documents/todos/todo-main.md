To-Do Main
-----

[Back](../../readme.md)

-----

`Core`

[Rendering](todo-rendering.md)

`InnerCore`

[User Interface](todo-ui.md)

[Voxels](todo-voxels.md)

`Extra`

[Tools](todo-tools.md)

[Devops](todo-devops.md)

[Fixes](todo-fixes.md)

-----

`Current`

- [ ] Current [User Interface](todo-ui.md)

- [ ] Line2Ds
    - [ ] Line tag / module / prefab etc
    - [ ] Grid2Ds for testing

- [ ] GameUIs Module
    - [ ] Generic Main Menus
        - spawn_main_menu_prefab function
        - game label
        - play button
        - options button
        - exit button
    - [ ] Generic Load/Save/New Game folders + uis
        - load directory folder names into a list
        - preview the selected file events (for example, show time played in that game folder)

-----

`Next`

- [ ] Custom pixel art for mouse ui

- [ ] Create a render queue and sort system
    - http://realtimecollisiondetection.net/blog/?p=86
    - https://paroj.github.io/gltut/Positioning/Tut05%20Overlap%20and%20Depth%20Buffering.html


- [ ] Load Shaders as entities
    - Dispose of them when closing game
    - Keep generic enough to use, so I can just load a list of files from resources

- [ ] 3D Particles
    - [ ] Particle3D with 3D mesh

- [ ] Line 3Ds! Grid3D :D
    
- [ ] Character3Ds
    - [ ] Physics 3D
    - [ ] Jump ability
    - [ ] Textured Cube - Drawing
    - [ ] First person camera on character3D

- [ ] Character2Ds
    - [ ] Mouse scroll to zoom in / out on follower

`Input`
- [ ] Handle multiple mouse devices
    - With IDs and Extraction
- [ ] Player to have connected devices
- [ ] Virtual Joysticks for touchscreen
    - Use for free roam

-----

`After`

- [ ] RenderTextures - connect a texture to a camera

- [ ] Flesh out modules
    - [ ] Voxels Module
    - [ ] Stats Module
    - [ ] Audio Module
    - [ ] Tiles Module

`Application Side`
- [ ] Support multiple Windows, one can be a FPS Debugger.
    - [ ] One Entity per Window
    - [ ] Viewport Component

`Flecs`
- [ ] Those queries still keep updating, they don't pass query checks