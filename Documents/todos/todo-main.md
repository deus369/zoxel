To-Do Main
-----

[Back](../../readme.md)

-----

`Doing`

Libraries
- [ ] Find a Library that supports multiple (keyboard or otherwise) devices
- [ ] Try out Glut and see if it reduces build size
    - just need a light weight window app to replace SDL
- [ ] Audio library for playing sounds - sending them to the sound buffer?
- [ ] Image processing library - png sequencing from bytes

Textures
- [ ] Link texture data in material

UI
- [x] Material Comonent - with a GLInt reference to a material
- [ ] Push UV into Textured Material
    - [ ] Use minimal example for drawing with uvs?

- [ ] Mesh Component - for unique mesh (maybe later i can scale uis in shader?)
- [ ] BasicRenderSystem - renders unique mesh / materials
- [ ] Mouse Device + handling
- [ ] UIButton tag - prefab - instantiate one in the middle of screen
- [ ] UIRaycastSystem
    - [ ] Raycast events
    - [ ] EntityClick events
- [ ] Font Texture Generation
- [ ] Frame Texture Generation

Game UIs
- [ ] Generic Main Menu
- [ ] UI Windows Flow
- [ ] Generic Load/Save/New Game folders + ui
- [ ] Scrollview + ListUI
- [ ] Camera Renderer UI
    - [ ] Spawn Cube - Rotating
    - [ ] Spawn 2nd camera
    - [ ] ViewUI connected to 2ND Camera
- [ ] Moveable Windows - Drag by headers

Building
- [ ] Get android build to work
    - [ ] Hello world Example with C code
    - [ ] SDL example

`Documentation`
- [ ] Look into docs forge (https://github.com/engine99team/engine99)

`Flecs Testing Limitations`
- [ ] Add variables to profiler (by reflecting them)
    - https://github.com/SanderMertens/flecs/blob/master/examples/c/reflection/basics/Source/main.c
- [ ] Binary serializer for data

- [x] DestroyEntity event and systems, with disposing of allocations (OnDelete events?)
    - [x] DestroyInTimeSystem
    - Flecs had a great way to handle memory allocations
- [x] Find a better way to add new systems and components per module - organized
- [x] Try out prefabs and mass spawning / data setting
    - [x] Spawn System
- [x] Inject data into another system
- [x] Seperate out shaders from inlines
    - [ ] Find a way to package shaders into binary build
- [x] Nativearray data structure
    - can just use malloc
- [x] Customize flecs to remove some feaures to reduce build size
- [x] Why did i have to comment these out
    nanosleep getnameinfo CLOCK_MONOTONIC clock_gettime NI_NUMERICHOST NI_NUMERICSERV
    - they are non c99 codes
- [x] A single threaded system will not run on main thread
    - Follow this up
    https://github.com/SanderMertens/Imports/Flecs/issues/798
- [ ] Make opengl.c/h one file, it imports in functions
- [x] const ecs_field not available yet
    'You can assign it to a const, but I haven't yet added const checking to the C API'

`Input`
- [x] Convert SDL of keyboard into an entity

`Application Side`
- [ ] Support multiple Windows, one can be a FPS Debugger.

`Done`

- [x] Seperate out structs into component files