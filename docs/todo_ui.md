// todo: fix window headers, make body a child, atm clicking header over another window breaks, because it restacks the window under the header ui
// todo: remember local layers for each element under window, and add those, instead of incrementally just adding like I do atm (this can be done later, not issue for now)

// done:
//      - When spawning window, set window layer
//      - count the highest children count so we can dynamically set layers_per_window
//      - also remember WindowLayer's set, so we can keep stack organized and just move window up
//      - handles new windows properly
//      - handle removal of windows in stack on update
