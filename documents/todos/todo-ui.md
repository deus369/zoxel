To-Do UI
-----

[Back](todo-main.md)

-----

`Current`

- [ ] Fix fullscreen - hiding UI?!?!

- [x] Raycast only child ui first, before parents. Don't raycast window when header is in front of it.
    - Add layer component
    - Cycle through all uis, and keep the top most one.
- [ ] Text UI Update system
    - [ ] animate text to a random word every 3 seconds! (for testing)

- [ ] UIRaycastSystem
    - [x] UI Select events
    - [ ] UI Click events
    - [ ] UI Drag events

- [ ] Window Entities
    - [x] A header UI with text
    - [x] A close button
    - [ ] A close window event
            - closed / confirm / cancel
    - [ ] Drag window around to reposition
    - [ ] Drag window corner to resize it

- [ ] UI Windows Flow
    - Using Close Events
    
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