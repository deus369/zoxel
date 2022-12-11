To-Do Rendering
-----

    Atm is uses OpenGL, perhaps I can support Vulkan in the future?

[Back](todo-main.md)

-----

`Current`

- [ ] Load Shaders as entities
    - load with filenames
    - Dispose of them when closing game
    - Keep generic enough to use, so I can just load a list of files from resources
- [ ] 2D / 3D line systems
- [ ] Fix Render Ordering
    - fps display breaks it, due to reordering of flecs tables
    - add a big array of things to render, resize array if game uses more
    - set this array per frame inside ecs, then in render systems render it
    - reorder the list into a second one, based on layyers of ui, position from camera
    - depth for camera?
- [ ] Fix Render Ordering of UI
    - add a hashmap of render lists per layer (0, 1, etc), reset per frame
    - supporting layers (text over header, etc)
- [ ] Change sky color, implement CameraColor (per camera entity) for background clearing
- [ ] 3D Particles
    - [ ] Particle3D with 3D cube mesh
- [ ] Textured Cube - Drawing
- [ ] Create a render queue and sort system
    - for Translucent textures (leaves)
    - http://realtimecollisiondetection.net/blog/?p=86
    - https://paroj.github.io/gltut/Positioning/Tut05%20Overlap%20and%20Depth%20Buffering.html

-----

`Rendering`
- [ ] Mesh Component - for unique mesh (maybe later i can scale uis in shader?)
- [ ] BasicRenderSystem - renders unique mesh / materials
- [ ] Support for Unique Mesh / Square Mesh (instance vertex data)
- [ ] Write a dynamic material / shader system
    - [ ] shader manager singleton
    - [ ] load list of shaders instead of specific
    - [ ] Handle properties better? do I need all that location reference..?

`Refactoring`
- [ ] Make opengl.c/h one file, it imports in functions