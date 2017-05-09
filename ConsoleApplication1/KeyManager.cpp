#include <iostream>
#include <Windows.h>
#include <cstdio>
#include "KeyReceiver.h"
#include "KeyBinder.h"


// ASSUME: Muting keys is not a function.
// - PURPOSE:	1) Rebind keys as fit.
//				2) Save profile of keybinds to be loaded on startup
//				3) Implement option to load new keybind profile
// TODO: Consider separating keyRebinder into UI and hotkeyManager - something like that..
// TODO: Add ability to mute key; ignore for now.
// TODO: Receive a second series of keys to implement keybind.
// TODO: Increase robustness of mappings between ID and keybinds + actions;
//			in removing and adding.
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

	// loop: Prompt user to either rebind key or exit program.
	do
	{
		// user input
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
			KeyNFlag kf;

			std::cout << "Please enter a hotkey:" << std::endl;
			// Receive key press from console input buffer
			kr.getKeyEvent();
			kf = kr.getKeyNFlag();
			// Create hotkey and pass on FLAGS
			kb.bindKey(kf.flagAlt, kf.flagCtrl, kf.vKeyCode);

			// TODO: Only initiate second getKeyEvent on KeyUpEvent of vKeyCode;
			//			getAsyncKeyState <-- use;
			// Receive another KeyEvent, and insert to IdToActionMap.
			/*std::cout << "Please enter the resulting action to occur from that hotkey (One key with alt/ctrl modifiers):" << std::endl;
			kr.getKeyEvent();
			kb.bindActionToKey(kr.getKeyNFlag()); */

			
			
			

		}
		else if (userOption == 3) // Respond to hotkeys
		{
			MSG msg = { 0 };
			while (GetMessage(&msg, NULL, 0, 0) != 0)
			{
				if (msg.message == WM_HOTKEY)
				{
					std::map<SHORT, WORD> keybindmap = kb.giveKeyBinds();
					WORD dog = kb.giveKeyBinds()[msg.wParam];

					// array of KeyEvents
					INPUT pKeyEvents[5];

					WORD vkCode = 0x12; // alt
					INPUT keyEvent1 = { 0 };
					keyEvent1.type = INPUT_KEYBOARD;
					keyEvent1.ki.wVk = vkCode;
					keyEvent1.ki.wScan = MapVirtualKeyEx(vkCode, 0, NULL);

					vkCode = 0x73; // f4
					INPUT keyEvent3 = { 0 };
					keyEvent3.type = INPUT_KEYBOARD;
					keyEvent3.ki.wVk = vkCode;
					keyEvent3.ki.wScan = MapVirtualKeyEx(vkCode, 0, NULL);

					vkCode = 0x12; // alt
					INPUT keyEvent2 = { 0 };
					keyEvent2.type = INPUT_KEYBOARD;
					keyEvent2.ki.wVk = vkCode;
					keyEvent2.ki.wScan = MapVirtualKeyEx(vkCode, 0, NULL);
					keyEvent2.ki.dwFlags = KEYEVENTF_KEYUP;

					vkCode = 0x73; // f4
					INPUT keyEvent4 = { 0 };
					keyEvent4.type = INPUT_KEYBOARD;
					keyEvent4.ki.wVk = vkCode;
					keyEvent4.ki.wScan = MapVirtualKeyEx(vkCode, 0, NULL);
					keyEvent4.ki.dwFlags = KEYEVENTF_KEYUP;

					
					pKeyEvents[0] = keyEvent1;
					pKeyEvents[1] = keyEvent3;
					pKeyEvents[2] = keyEvent2;
					pKeyEvents[3] = keyEvent4;

					SendInput(4, pKeyEvents, sizeof(keyEvent1));

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
