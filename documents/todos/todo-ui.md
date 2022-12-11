To-Do UI
-----

    User Interfaces for data visualizations and game flow.

[Back](todo-main.md)

-----

`Current`
- [ ] Press escape in game to open pause ui
    - [ ] (when game state changes) for touch ui, add button at bottom left for this
- [ ] Generic Pause Menu
    - [ ] Resume
    - [ ] Exit
    - [ ] Pause game if, game can be paused
    - [ ] Options
- [ ] GameUIs Module
    - [ ] Generic Load/Save/New Game folders + uis
        - load directory folder names into a list
        - preview the selected file events (for example, show time played in that game folder)
    - [ ] Generic Save Games
        - [ ] Load list of folder names for games
        - [ ] Load selected save game
        - [ ] Show played time so far
- [ ] UI Windows Flow
    - [ ] Using Close Events, spawn a 2nd window
- [ ] Scrollview + ListUI
    - [ ] Toggle group to select one in list

-----

`Extra`
- [ ] Taskbar - with windows  you can open (icons)
- [ ] Custom pixel art for mouse ui
- [ ] Drag window corner to resize it

`Core`
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

`Bugs`
- [ ] Resizing in web build, breaks ui, due to mouse position being offset by screen size change..

-----

`UI Done`

- [x] More Prefab Testing
    - [x] Labels
    - [x] Buttons
    - [x] Windows
- [x] Update Text System
- [x] Draggable Windows
    - [x] UI Drag events
    - [x] Drag window around to reposition
- [x] Generic Main Menus
    - spawn_main_menu_prefab function
    - game label
    - play button
    - options button
    - exit button
- [x] Fix element positioning bug for windows (parent_pixel_size was position)
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
- [x] Move main menu stuff from window  into main menu / game ui module
- [x] Fix bug - repositioning ui on resize canvas broken
- [x] Main Menu
    - Play button - to delete the AI camera and create the free roam one
    - Exit button - close game