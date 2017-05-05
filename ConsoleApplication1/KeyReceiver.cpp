#include "stdafx.h"
#include "KeyReceiver.h"
#include <iostream>


KeyReceiver::KeyReceiver()
{
	this->flagCtrl = false;
	this->flagAlt = false;
	this->vKeyCode = 0;
}


KeyReceiver::~KeyReceiver()
{
}

// purpose: receive a single input from user
void KeyReceiver::getKeyEvent()
{
	// Read a single key press from the console input buffer
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD *inpRecordArray = new INPUT_RECORD[10];
	DWORD numEventsRead;
	LPDWORD lpNumEventsRead = &numEventsRead;

	// Set modifier-key flags and virtual-key code
	//	virtual-key code != non-modifier keys
	bool awaitingValidKey = true;
	while (awaitingValidKey) 
	{
		// reset flags if looping
		this->reset();
		// read one keypress
		ReadConsoleInput(handle, inpRecordArray, 1, lpNumEventsRead);
		this->vKeyCode = inpRecordArray->Event.KeyEvent.wVirtualKeyCode;
		// set flags and terminate if possible
		if (GetAsyncKeyState(VK_LCONTROL) && 0x8000)
			this->flagCtrl = true;
		if (GetAsyncKeyState(VK_LMENU) && 0x8000)
			this->flagAlt = true;
		if (this->vKeyCode != VK_CONTROL &&
			this->vKeyCode != VK_LCONTROL && this->vKeyCode != VK_RCONTROL &&
			this->vKeyCode != VK_LMENU && this->vKeyCode != VK_RMENU &&
			this->vKeyCode != VK_LSHIFT && this->vKeyCode != VK_RSHIFT
			&& this->vKeyCode != 18)
		{
			awaitingValidKey = false;
		}
	}
	return;
}


void KeyReceiver::reset()
{
	this->flagAlt = false;
	this->flagCtrl = false;
	this->vKeyCode = 0;
}