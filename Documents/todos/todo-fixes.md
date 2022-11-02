To-Do Fixes
-----

Things to just fix after. Technical Debt. Bugs. Etc.

[Back](todo-main.md)

-----

`Fixes`
- [ ] Keep a property reference upon creating materials (atm its doing it per frame)
- [ ] Disable rotation for first movement
- [ ] Smooth camera rotations

`Flecs`
- [ ] Get ctx to input two queries for PlayerRoamSystem
- [ ] Use entity link (character2DLink) in CameraFollow2DSystem
- [ ] Why does sprite mess up when updating flecs?? Investigate.

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