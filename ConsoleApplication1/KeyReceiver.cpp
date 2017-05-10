#include "stdafx.h"
#include "KeyReceiver.h"
#include <iostream>


KeyReceiver::KeyReceiver()
{
	this->reset();
}


KeyReceiver::~KeyReceiver()
{
}


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
		// reset flags; receive and store keypress.
		this->reset();
		ReadConsoleInput(handle, inpRecordArray, 1, lpNumEventsRead);
		this->vKeyCode = inpRecordArray->Event.KeyEvent.wVirtualKeyCode;

		// logic:	Upon pressing alt and/or control the loop will continue,
		//			and reset; BUT this allows us to immediately introduce a
		//			non-modifer key WHILE the alt and/or ctrl key is held.
		//			e.g. affording us the "ctrl+alt+k" hotkey.
		if (GetAsyncKeyState(VK_LCONTROL) && 0x8000)
			this->flagCtrl = true;
		if (GetAsyncKeyState(VK_LMENU) && 0x8000)
			this->flagAlt = true;
		// if non-modifier key, terminate!
		if (this->vKeyCode != VK_CONTROL && this->vKeyCode != 18 &&
			this->vKeyCode != VK_LCONTROL && this->vKeyCode != VK_RCONTROL &&
			this->vKeyCode != VK_LMENU && this->vKeyCode != VK_RMENU &&
			this->vKeyCode != VK_LSHIFT && this->vKeyCode != VK_RSHIFT)
		{
			awaitingValidKey = false;
		}
	}
	
	return;
}

KeyNFlag KeyReceiver::getKeyNFlag()
{
	KeyNFlag kf;
	kf.flagAlt = this->flagAlt;
	kf.flagCtrl = this->flagCtrl;
	kf.vKeyCode = this->vKeyCode;
	return kf;
}


void KeyReceiver::reset()
{
	this->flagAlt = false;
	this->flagCtrl = false;
	this->vKeyCode = 0;
}