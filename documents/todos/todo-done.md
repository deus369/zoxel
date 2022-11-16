To-Do Done
-----

Things that are done. A big ole list. To clean up other todo files.

[Back](todo-main.md)

-----

`UI`
- [x] UIRaycastSystem
    - [x] UI Select events
    - [x] UI Click events
- [x] Window Entities
    - [x] A header UI with text
    - [x] A close button
    - [x] A close window event
            - closed / confirm / cancel
- [x] Window not spawning with system
    - added EntityInitialize component for generating buffers on main thread
    - Position2D is gone after spawning window?
    - Possible soluion: remove ecs_get from function and pass in parent info when spawning children.
- [x] FPS Display (top right)
- [x] Generate Mesh - in an initialize system - instead of in main thread.
- [x] Fix fullscreen - hiding UI?!?!
- [x] Raycast only child ui first, before parents. Don't raycast window when header is in front of it.
    - Add layer component
    - Cycle through all uis, and keep the top most one.
- [x] Text UI Update system
    - [x] animate text to a random word every 3 seconds! (for testing)
- [x] Scale textures of ui properly
    - Use Unique Meshes - generated based on ui size
- [x] Position perfectly
- [x] when resize viewport - resize uis there
- [x] Camera Renderer UI
    - [x] Spawn Cube - Rotating
    - [x] Spawn 2nd camera
- [x] Font
    - [x] Generate Font Texture
- [x] Texts
    - [x] Assemble from a Text data
- [x] Font Texture Generation
- [x] Frame Texture Generation
- [x] UIButton tag - prefab - instantiate one in the middle of screen

`Particles`
- [x] Particle3D with 2D mesh

`Cameras`
- [x] Fix rotation of camera math - Transform Matrix
    - should be rotating at point instead of around point
    - [x] Debug it in euler / position
- [x] Free roam camera
    - [x] Using mouse to rotate it around

`Inputs`
- [x] Mouse Device + handling
- [x] Convert SDL of keyboard into an entity

`Rendering`
- [x] Push UV into Textured Material
    - [x] Use minimal example for drawing with uvs?
- [x] Material Comonent - with a GLInt reference to a material
- [x] Link texture data in material

`Extra`
- [x] Create minimal example of setting a 'material' integer link as a test for the upgrade bug
- [x] Web build doesn't resize canvas - fix 
- [x] Seperate out structs into component files
- [x] DestroyEntity event and systems, with disposing of allocations (OnDelete events?)
    - [x] DestroyInTimeSystem
    - Flecs had a great way to handle memory allocations
- [x] Find a better way to add new systems and components per module - organized
- [x] Try out prefabs and mass spawning / data setting
    - [x] Spawn System
- [x] Inject data into another system
- [x] Seperate out shaders from inlines
    - [x] Find a way to package shaders into binary build
- [x] Nativearray data structure
    - can just use malloc
- [x] Customize flecs to remove some feaures to reduce build size
- [x] Why did i have to comment these out
    nanosleep getnameinfo CLOCK_MONOTONIC clock_gettime NI_NUMERICHOST NI_NUMERICSERV
    - they are non c99 codes
- [x] A single threaded system will not run on main thread
    - Follow this up
    https://github.com/SanderMertens/imports/issues/798
- [x] const ecs_field not available yet
    'You can assign it to a const, but I haven't yet added const checking to the C API'