To-Do Flecs
-----

Any pending flecs issues, don't fix them constantly as it interupts main work.

[Back](todo-main.md)

-----

- [ ] Query updates are being weird, check them out more.
    - [ ] Make a test that checks how change updates work with update components.

- [ ] Cannot set entity in multi thread. Perhaps pass in zigels with a filter for that.
    - Had this issue with ZextUpdateSystem
    
- [ ] Investigate Entity relationships
    - Checkout those flecs articles on it

- [ ] Setting many linked components, with many setter systems may be slow
    - avoid for now
    - later if really needed, use a hashmap to speed up entity -> component indexes

- [ ] Investigate relationships more, over traditional entity links

- [ ] Create custom Pipelines for systems to organize them better
    - create a diagram flow chart for that