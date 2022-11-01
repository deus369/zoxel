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

`Cameras`
- [ ] Fix rotation of camera math - Transform Matrix
    - should be rotating at point instead of around point
    - [x] Debug it in euler / position
- [ ] Free roam camera
    - [ ] Using mouse to rotate it around

`Current`
- [ ] 3D Particles
    - [x] Particle3D with 2D mesh
    - [ ] Particle3D with 3D mesh
- [ ] Character3Ds
    - [ ] Physics 3D
    - [ ] Jump ability
    - [ ] Textured Cube - Drawing

`Input`
- [ ] Mouse Device + handling

`Lines`
- [ ] Line2Ds
    - [ ] Line tag / module / prefab etc
- [ ] Line 3Ds! Grid :D

`Next Modules`
- [ ] GameUIs Module
- [ ] Voxels Module
- [ ] Stats Module
- [ ] Audio Module
- [ ] Tiles Module

`Game UIs`
- [ ] Generic Main Menu
- [ ] UI Windows Flow
- [ ] Generic Load/Save/New Game folders + ui
- [ ] Scrollview + ListUI
- [ ] Camera Renderer UI
    - [ ] Spawn Cube - Rotating
    - [ ] Spawn 2nd camera
    - [ ] ViewUI connected to 2ND Camera
- [ ] Moveable Windows - Drag by headers

`Flecs Testing Limitations`
- [ ] Binary serializer for data
- [ ] Add variables to profiler (by reflecting them)
    - https://github.com/SanderMertens/flecs/blob/master/examples/c/reflection/basics/Source/main.c

`Application Side`
- [ ] Support multiple Windows, one can be a FPS Debugger.
    - [ ] One Entity per Window
    - [ ] Viewport Component