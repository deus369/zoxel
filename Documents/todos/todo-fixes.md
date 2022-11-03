To-Do Fixes
-----

Things to just fix after. Technical Debt. Bugs. Etc.

[Back](todo-main.md)

-----

- [ ] Add zoom - mouse scroll - for camera follower - with min/max setting

- [ ] Name my modules properly
    - https://github.com/SanderMertens/flecs/blob/master/include/flecs/addons/module.h

- [ ] Use entity link (character2DLink) in CameraFollow2DSystem
- [ ] Go through relationships, try it out for Camera?.... 
    - [ ] This is going to be a mess omg... I need hash map components?
    - https://github.com/flecs-hub/flecs-game/blob/main/src/world_cells.c
    - https://github.com/SanderMertens/flecs/tree/master/examples/c/relationships
    - https://github.com/SanderMertens/flecs/tree/master/examples/c/relationships
    - https://www.flecs.dev/flecs/#/docs/Relationships

`Fixes`
- [ ] Keep a property reference upon creating materials (atm its doing it per frame)
- [ ] Disable rotation for first movement
- [ ] Smooth camera rotations

`Flecs`
- [ ] Get ctx to input two queries for CameraFreeRoamToggleSystem
- [ ] Why does sprite mess up when updating flecs?? Investigate.
- [ ] Binary serializer for data
- [ ] Add variables to profiler (by reflecting them)
    - https://github.com/SanderMertens/flecs/blob/master/examples/c/reflection/basics/Source/main.c

`Weird`
- [ ] Bulk Spawning issues - Crashes
    - Write up a test for it, so it tests bulk spawning, but multiple times to get error
    - Write a Individual Spawning function temporary fix
- [ ] When the threading issue is fixed:
    - [ ] Replace Texture queue with mainthread updates `TextureUpdateSystem`
    - [ ] Make render systems work in pipeline and remove from main.c
- [x] Find out why NoiseTextureSystem filter for GenerateTexture only triggers one texture instead of all of them
- [x] Cleanup GPUMaterial and GPUTexture components after destroyed. Use DTOR hooks.
- [x] Find out why CameraFollower2D tag cannot be added in Players Module
    - [x] Write minimal example and submit as bug report