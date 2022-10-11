`Todos`

`Input`
- [ ] Convert SDL of keyboard into an entity. Support multiple devices.

`ECS`
- [ ] Find a better way to add new systems and components per module - organized
- [ ] Try out prefabs and mass spawning / data setting
- [ ] Make OpenGLHelpers one file.
- [ ] Seperate out shaders from inlines.
- [ ] Spawn System
- [ ] Inject data into another system
- [ ] Nativearray data structure
- [ ] DestroyEntity event and systems, with disposing

- [ ] Customize flecs to remove most feaures
    nanosleep getnameinfo CLOCK_MONOTONIC clock_gettime NI_NUMERICHOST NI_NUMERICSERV

- [ ] Multithreading / non multi threading not supported yet
    https://github.com/SanderMertens/Flecs/issues/798

- [ ] const ecs_field not available yet
    'You can assign it to a const, but I haven't yet added const checking to the C API'

`Application Side`
- [ ] Support multiple Windows.

`Done`

- [x] Seperate out structs into component files