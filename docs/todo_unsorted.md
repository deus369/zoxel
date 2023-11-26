## web build

- [ ] Fix terrain rendering not showing visually, opengl errors?
- [ ] Fix EM_JS functions not working anymore (platforms/util/webasm_util.c)
- [ ] Fix Pipeline, 'make push-web' should push to a zox-web git repo the latest build

## cross compile to windows

- [x] get a 'make build/zoxel.exe' build working

## steamdeck steam

- [x] install_sdk for steamworks
- [ ] add steamworks to zoxel compilation with a toggle option
- [ ] 'make is_steamworks' check if steamworks is in build
- [ ] make toggle_steamworks - add steamworks includes to build settings?
- [ ] test achievement for killing first npc - [noob] Vox Slayer! You have started your journey into the path of carnage.

## devops

- [ ] automate builds every morning it should perform all builds
- [ ] test results can be displayed in a simple text file
- [ ] push builds to git repo every week on a saturday

=================================
    builds started at [3.18PM - 11/23/23]
=================================
    linux x86_64 [passed]
    linux x86_32 [passed]
    windows x86_64 [passed]
    windows x86_32 [passed]
    webasm [passed]
    android [failed]
    linux arm64 [passed]
=================================
    builds completed at [6.18PM - 11/23/23]
=================================

## io

- [ ] load vox, texture & sound files dynamically
- [ ] save file in multithread?

## game

- [ ] link user skill to a texture
- [ ] link actionbar ui to character
- [ ] spawn player character user action entities
- [ ] spawn player character user skill entities

## ui

- [x] fix editor issue where hierarchy and inspector spawn but children fails
- [x] inspector - update list dynamically with scroll
- [ ] window  sorting by last clicked one (make a window stack)
- [ ] input field ui on terminal window
- inspector
    - [ ] if entity dies, perhaps remove selection off inspector
    - [ ] set position of labels to left of the ui in the list, left anchoring
        - [ ] tab out based on a 'tab' character
    - [ ] add float3, float4, entity, doubles (deadtime) and anything else i can too editor values
    - [ ] don't delete old children just reuse for list updates
