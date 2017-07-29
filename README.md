# HotkeyRebinder
This is a program designed to mute, create and rebind hotkeys. This program makes use of WINAPI and thus only works on Windows.

# How to Use
The user will be prompted to keypress a hotkey, before keypressing a resulting action. After binding, the user has to begin the event handling loop. At this point, the program will now globally register all hotkey presses and output the associated action. 

On keybinding and registering an action, the alt and ctrl keys will also be registered. This allows for more variety in keybinds.

# Files Involved
There are three main files(and their corresponding headers): KeyBinder.cpp, KeyManager.cpp, and KeyReceiver.cpp.

KeyManager is the main entry point where keys are bound and Windows messages are handled; resulting in functional rebinds.

KeyReceiver reads a single key press from the user and can return a struct containing the following: virtual key code and any alt+ctrl flags (a KeyNFlag struct). 

KeyBinder performs the act of binding a key press to an action; the key press or action may have alt or ctrl flags.
