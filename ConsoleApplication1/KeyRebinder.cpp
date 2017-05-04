#include <iostream>
#include <Windows.h>
#include <cstdio>

// ASSUME: Muting keys is not a function.
// - PURPOSE:	1) Rebind keys as fit.
//				2) Save profile of keybinds to be loaded on startup
//				3) Implement option to load new keybind profile
//				4) Offer mouse cursor macros
// TODO: create UI to do 3 things:
//		- enter rebind decision branch.
//		- exit; make user answer yes again to "are you sure?"
// TODO: create a separate class to handle rebinding.
//		- dedicate current class to handle UI
int main() {
	// ask what user would like to do
	// if rebind, enter rebinding decision branch -- TBD.
		// if user wants to exit at any point, type exit.
		// if user ever enters an invalid option, program asks to try again.
	// if exit, ask exit again.
	// if invalid option, give prompt again.
	bool isRunning = true; // possible redundancy; !!! remove later.
	int userOption = 0;

	// loop: Prompt user to either rebind key or exit program.
	do
	{
		// user input
		printf(
			"Please select an option.\n"
			"1) Rebind a key\n"
			"2) exit\n ");
		std::cin >> userOption;

		// termination prompt
		if (userOption == 2)
		{
			printf("Are you sure? Enter 2 again to exit.\n");
			std::cin >> userOption;
			if (userOption == 2)
				break;
			else
				userOption = 0;
		}
		else if (userOption == 1)
		{
			// things to learn: WORD, INPUT, MapVirtualKeyEx,
			//		reading DOCS
			//	reference: http://stackoverflow.com/questions/22419038/how-to-use-sendinput-function-c
			// We can now output a keypress.
			// next: keybind things to "SendInput";
			// accept key presses 
			// determine how UI will receive keypresses.
			WORD vkCode = 0x36;
			INPUT keyEvent = { 0 };
			keyEvent.type = INPUT_KEYBOARD;
			keyEvent.ki.wVk = vkCode;
			keyEvent.ki.wScan = MapVirtualKeyEx(vkCode, 0, NULL);
			SendInput(1, &keyEvent, sizeof(keyEvent));
		}
		else
		{
			printf("Invalid input\n");
		}

		



	} while (isRunning);

	/*int yes = 0;
	if (RegisterHotKey(NULL, 1, 0, VK_UP))
	{
		std::cout << "hotkey for VK_UP registered!" << std::endl;
	}

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (msg.wParam == 1)
		{
			std::cout << "WM_HOTKEY received\n" << std::endl;
		}
	}*/


}