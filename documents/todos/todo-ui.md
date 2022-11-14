To-Do UI
-----

[Back](todo-main.md)

-----

`Current`

- [x] Window not spawning with system
    - added EntityInitialize component for generating buffers on main thread
    - Position2D is gone after spawning window?
    - Possible soluion: remove ecs_get from function and pass in parent info when spawning children.

- [ ] FPS Display (top right)

- [x] Generate Mesh - in an initialize system - instead of in main thread.

- [ ] UIRaycastSystem
    - [x] UI Select events
    - [x] UI Click events
    - [ ] UI Drag events

- [ ] Window Entities
    - [x] A header UI with text
    - [x] A close button
    - [x] A close window event
            - closed / confirm / cancel
    - [ ] Drag window around to reposition
    - [ ] Drag window corner to resize it

- [ ] UI Windows Flow
    - [ ] Using Close Events, spawn a 2nd window
    
- [ ] Scrollview + ListUI

- [ ] Taskbar - with windows  you can open (icons)

-----

`Bugs`

- [ ] Resizing in web build, breaks ui, due to mouse position being offset by screen size change..

-----

`UI Core`

- [ ] Finish fonts
    - [ ] Use hashmap for ascii conversion to byte data
    - [ ] Add in special characters
    - [ ] Add in upper case characters

- [ ] Text Font Editor
    - [ ] Editor Grid with lines
    - [ ] show where mouse is pointing in grid
    - [ ] Load / Save a font file
    - [ ] Load / Save a font style
    - [ ] Preview Generation from the points editing

- [ ] Update Text System


- [ ] More Prefab Testing
    - [ ] Labels
    - [ ] Buttons
    - [ ] Windows