# bugs

- [ ] sometimes lags and does not spawn actionbar, make this not time dependent
    - [ ] voxel items failed ' ! voxel_texture_data->value is null'
- [ ] collision failed because of 30 fps
- [ ] catch crashes created by latest code

# load bugs
- [x] when loding chunks lag spikes
- [x] chunks should load before player character

# physics bugs
- [ ] during low frame rates, falls through map
    - [ ] create a button that lowers frame rate for testing
    - [ ] on windows, when loading save game, falls through map
- [ ] low frames make you clip map
    - [ ] make a fixer system that repositions.. until i can perfect physics
- [ ] clip bug if you are exactly 2 voxels tall you can walk through bottom voxel (doesn't check properly)

# rendering bugs
- [ ] sometimes meshes dissapear in chunk loding..
- [ ] on android, lines are being weird
- [ ] on android, sometimes voxel gizmo flickers (low frames?)

# unsorted bugs
- [ ] when running 2D game and closing, errors out on close game (have to start game first)
