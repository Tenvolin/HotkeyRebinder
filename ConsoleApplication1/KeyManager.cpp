/**
KeyRebinder, KeyManager.cpp
purpose: main programmatic entry point. This program uses WINAPI functions made
			available from Windows.h to achieve the following: receiving
			keypress events, creating hotkeys, and handling hotkey windows 
			events.

@author Alex Chung
*/
#include "stdafx.h"
#include <Windows.h>
#include <cstdio>
#include <iostream>
#include <string>
#include "KeyReceiver.h"
#include "KeyBinder.h"


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

// assume: Muting keys is not a function.
// purpose:		1) Rebind keys as fit.
//				2) Save profile of keybinds to be loaded on startup
//				3) Implement option to load new keybind profile
// TODO: todo file located in local notes.txt
int main() {
	// Order of Operations:
	// ask what user would like to do
	// if rebind, enter rebinding decision branch
		// TODO: if user wants to exit at any point, type exit. 
		// TODO: if user ever enters an invalid option, program asks to try again.
	// if exit, ask exit again.
	// if invalid option, give prompt again.
	bool isRunning = true; // possible redundancy; !!! remove later.
	int userOption = 0;

	KeyReceiver key_receiver = KeyReceiver();
	KeyBinder key_binder = KeyBinder();
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
			key_receiver.getKeyEvent();
			kf = key_receiver.getKeyNFlag();
			key_binder.bindKey(kf.flagAlt, kf.flagCtrl, kf.vKeyCode);
			Sleep(100);

			system("CLS");
			std::cout << "Press Enter, followed by your key of action." << std::endl;

			// ? Calling cin.ignore twice seems to work best.
			std::cin.ignore(1000, '\n');
			std::cin.ignore(1000, '\n');

			key_receiver.getKeyEvent();
			key_binder.bindActionToKey(key_receiver.getKeyNFlag());
		}
		else if (userOption == 3) // Respond to hotkeys
		{
			MSG msg = { 0 };
			int id = msg.wParam;
			int numKeyEvents = 0;
			INPUT *pKeyEvents = new INPUT[100]; // array of KeyEvents
			std::map<SHORT, KeyNFlag> keyBindMap;
			int keyMode = 0; // 0-->keydown; 1-->keyUp

			while (GetMessage(&msg, NULL, 0, 0) != 0)
			{

				switch (msg.message)
				{
					id = msg.wParam;
				case WM_HOTKEY:
					// reset to write and read appropriate number of keyEvents
					keyMode = 0;
					numKeyEvents = 0;

					keyBindMap = key_binder.giveActionMap();
					kf = keyBindMap[id];

					// Keydown up to three KeyEvents.
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

					// keyUp up to three keyEvents
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
					pKeyEvents[numKeyEvents] = createKeyEvent(kf.vKeyCode, keyMode);
					numKeyEvents++;


					SendInput(numKeyEvents, pKeyEvents, sizeof(INPUT));
					break;
				default:
					// don't do anything
					break;
				}

			}
		}
		else
		{
			printf("Invalid input\n");
		}

	} while (isRunning);

}

