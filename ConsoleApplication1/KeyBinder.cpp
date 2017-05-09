#include "stdafx.h"
#include "KeyBinder.h"
#include <iostream>
#include <string>
#include <map>


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
	int id = this->numKeyBinds;

	if (flagAlt)
		fsModifiers |= MOD_ALT;
	if (flagCtrl)
		fsModifiers |= MOD_CONTROL;

	// Ids of each keybind == keyBindNumber
	if (success = RegisterHotKey(NULL, id++, fsModifiers, vKeyCode))
	{
		// increment only if successful
		this->numKeyBinds = id;
		std::cout << "Hotkey Registered!" << std::endl;
		this->IdToHotkey.insert(std::pair<SHORT, WORD>(this->numKeyBinds, vKeyCode));
	}


	return success;
}

// purpose: Bind action to most recent hot key.
//			To be called after bindKey;
// output: return -1 if failure to insert.
int KeyBinder::bindActionToKey(KeyNFlag kf)
{
	int success = -1;
	size_t currentSize = this->IdToActionMap.size();

	SHORT id = this->numKeyBinds;
	this->IdToActionMap.insert(std::pair<SHORT, KeyNFlag>(id, kf));

	if (currentSize < this->IdToActionMap.size()) {
		success = 1;
	}
		
	return success;
}

std::map<SHORT, WORD> KeyBinder::giveKeyBinds()
{
	return this->IdToHotkey;
}

std::map<SHORT, KeyNFlag> KeyBinder::giveActionmap()
{
	return this->IdToActionMap;
}

int KeyBinder::giveNumKeyBinds()
{
	return this->numKeyBinds;
}
