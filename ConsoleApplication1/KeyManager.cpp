#include <iostream>
#include <Windows.h>
#include <cstdio>
#include "KeyReceiver.h"
#include "KeyBinder.h"
#include <string>
#include <vector>

// purpose: Generate a keyEvent given a vkCode.
//			mode = 0 -> keyDownEvent
//			mode = 1 -> keyUpEvent
INPUT createKeyEvent(WORD vkCode, int mode)
{
	INPUT keyEvent = { 0 };
	keyEvent.type = INPUT_KEYBOARD;
	keyEvent.ki.wVk = vkCode;
	keyEvent.ki.wScan = MapVirtualKeyEx(vkCode, 0, NULL);
	if (mode == 1)
		keyEvent.ki.dwFlags = KEYEVENTF_KEYUP;

	return keyEvent;
}
// ASSUME: Muting keys is not a function.
// - PURPOSE:	1) Rebind keys as fit.
//				2) Save profile of keybinds to be loaded on startup
//				3) Implement option to load new keybind profile
// TODO: Consider separating keyRebinder into UI and hotkeyManager - something like that.
// TODO: Add ability to mute key; ignore for now.
// TODO: Receive a second series of keys to implement keybind.
// TODO: Increase robustness of mappings between ID and keybinds + actions;
//			in removing and adding.
// TODO: refactor loops with switch blocks;
// TODO: Allow ability to terminate in midst of hotkey binding and undo hotkey bind.
// TODO: Need to temporarily mute modifier-keys when performing binded action
// TODO: KeyNFlag will need to be refactored to allow possibility of macros -- embedded scripting
int main() {
	// Order of Operations:
	// ask what user would like to do
	// if rebind, enter rebinding decision branch -- TBD.
		// if user wants to exit at any point, type exit.
		// if user ever enters an invalid option, program asks to try again.
	// if exit, ask exit again.
	// if invalid option, give prompt again.
	bool isRunning = true; // possible redundancy; !!! remove later.
	int userOption = 0;

	KeyReceiver kr = KeyReceiver();
	KeyBinder kb = KeyBinder();
	KeyNFlag kf; // most recent received key

	// loop: Prompt user to either rebind key or exit program.
	do
	{
		// user input
		system("CLS");
		printf(
			"Please select an option.\n"
			"1) Rebind a key\n"
			"2) Exit\n"
			"3) Use hotkeys\n");
		std::cin >> userOption;


		if (userOption == 2) // termination prompt
		{
			printf("Are you sure? Enter 2 again to exit.\n");
			std::cin >> userOption;
			if (userOption == 2)
				break;
			else
				userOption = 0;
		}
		else if (userOption == 1) // create keybinds
		{
			// Receive key press from console input buffer
			//		and Create hotkey and pass on FLAGS
			std::cout << "Please enter a hotkey:" << std::endl;
			kr.getKeyEvent();
			kf = kr.getKeyNFlag();
			kb.bindKey(kf.flagAlt, kf.flagCtrl, kf.vKeyCode);

			// Prompt user for resulting action of hotkey
			system("CLS");
			printf("Select the resulting action to bind to hotkey:\n"
				"1) Keyboard input\n"
				"2) Mouse action\n"
				"3) terminate\n"
			);
			std::cin >> userOption;

			// Act on resulting userinput
			if (userOption == 1)
			{
				system("CLS");
				std::cout << "Please enter the resulting action to occur from that hotkey (One key with alt/ctrl modifiers):" << std::endl;
				kr.getKeyEvent();
				kb.bindActionToKey(kr.getKeyNFlag());
			}
			else
			{
				std::cout << "To be implemented!" << std::endl;
			}

		}
		else if (userOption == 3) // Respond to hotkeys
		{
			MSG msg = { 0 };
			int id = msg.wParam;
			int numKeyEvents = 0;
			INPUT *pKeyEvents = new INPUT[100]; // array of KeyEvents
			std::map<SHORT, KeyNFlag> keyBindMap;
			KeyNFlag kf;
			int keyMode = 0; // 0-->keydown; 1-->keyUp

			while (GetMessage(&msg, NULL, 0, 0) != 0)
			{
				if (msg.message == WM_HOTKEY)
				{
					keyBindMap = kb.giveActionMap();
					kf = keyBindMap[id];

					// each keyEvent must both keyPressDown AND keyPressUp
					// add up to first three key events.
					if (kf.flagAlt)
					{
						pKeyEvents[numKeyEvents] = createKeyEvent(VK_MENU, keyMode);
						numKeyEvents++;
					}
					if (kf.flagCtrl)
					{
						pKeyEvents[numKeyEvents] = createKeyEvent(VK_LCONTROL, keyMode);
						numKeyEvents++;
					}
					pKeyEvents[numKeyEvents] = createKeyEvent(kf.vKeyCode, keyMode);
					numKeyEvents++;


					// keyUp everything
					keyMode = 1;
					pKeyEvents[numKeyEvents] = createKeyEvent(kf.vKeyCode, keyMode);
					if (kf.flagAlt)
					{
						pKeyEvents[numKeyEvents] = createKeyEvent(VK_MENU, keyMode);
						numKeyEvents++;
					}
					if (kf.flagCtrl)
					{
						pKeyEvents[numKeyEvents] = createKeyEvent(VK_LCONTROL, keyMode);
						numKeyEvents++;
					}


					SendInput(numKeyEvents, pKeyEvents, sizeof(INPUT));

				}
			}
		}
		else
		{
			printf("Invalid input\n");
		}

	} while (isRunning);

}
// things to learn: WORD, INPUT, MapVirtualKeyEx,
//		reading DOCS
//	reference: http://stackoverflow.com/questions/22419038/how-to-use-sendinput-function-c
