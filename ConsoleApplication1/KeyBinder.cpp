#include "stdafx.h"
#include "KeyBinder.h"
#include <iostream>



KeyBinder::KeyBinder()
{
	this->numKeyBinds = 0;
}


KeyBinder::~KeyBinder()
{
}

int KeyBinder::bindKey(bool flagAlt, bool flagCtrl, WORD vKeyCode)
{
	int success = 0;
	DWORD fsModifiers = 0;

	if (flagAlt)
		fsModifiers |= MOD_ALT;
	if (flagCtrl)
		fsModifiers |= MOD_CONTROL;

	if (success = RegisterHotKey(NULL, this->numKeyBinds, fsModifiers, vKeyCode))
	{
		// add ID:vKeyCode to map
		std::cout << "Hotkey Registered!" << std::endl;
		this->keyBindIds[numKeyBinds] = vKeyCode;
		this->numKeyBinds++;
	}

	return success;
}

std::map<SHORT, WORD> KeyBinder::giveKeyBinds()
{
	return this->keyBindIds;
}



