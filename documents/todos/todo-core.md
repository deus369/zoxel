To-Do Core
-----

    I added core things here together.

[Back](todo-main.md)

-----

`Core`
- [ ] Fix [resize_canvas] for web build
- [x] Sometimes crashes... from get_voxel_right macro in chunk builder (so on startup atm)
- [x] Fix flashing when transfering cameras (from main menu camera to free roam one)
- [ ] Flesh out modules
    - [x] Voxels Module
    - [ ] Stats Module
    - [ ] Tiles Module

`Transforms`
- [ ] Remove use of delete_hierarchy and use a observer event to destroy hierarchy of anything with a child
    - requires testing... *dread*

`Application Side`
- [ ] Support multiple Windows
    - [ ] one can be a FPS Debugger UI
    - [ ] One Entity per Window
    - [ ] Viewport Component linked to cameras

`Flecs`
- [ ] Those queries still keep updating, they don't pass query checks
    - [x] write better test functions for those
    - [ ] write even better test funcions
