To-Do Core
-----

    I added core things here together.

[Back](todo-main.md)

-----

`Core`
- [ ] Fix [resize_canvas] for web build
- [ ] Remove use of delete_hierarchy and use a observer event to destroy hierarchy of anything with a child
    - requires testing... *dread*
- [x] Sometimes crashes... from get_voxel_right macro in chunk builder (so on startup atm)
- [x] Fix flashing when transfering cameras (from main menu camera to free roam one)
- [ ] Grid UIs
- [ ] Flesh out modules
    - [ ] Voxels Module
    - [ ] Stats Module
    - [ ] Tiles Module

`Input`
- [ ] Handle multiple mouse devices
    - With IDs and Extraction
- [ ] Player to have connected devices
- [ ] Virtual Joysticks for touchscreen
    - Use for free roam

`Application Side`
- [ ] Support multiple Windows, one can be a FPS Debugger.
    - [ ] One Entity per Window
    - [ ] Viewport Component

`Flecs`
- [ ] Those queries still keep updating, they don't pass query checks
    - [x] write better test functions for those
    - [ ] write even better test funcions
