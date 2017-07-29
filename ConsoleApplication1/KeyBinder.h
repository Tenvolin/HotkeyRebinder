/**
KeyRebinder, KeyBinder.h
purpose: declarations for KeyBinder class.

@author Alex Chung
*/
#pragma once
#include <Windows.h>
#include <map>
#include "KeyReceiver.h"

class KeyBinder
{
private:
	std::map<SHORT, WORD> IdToHotkey;	// keyBindIds:vKeyCodes
	std::map<SHORT, KeyNFlag> IdToActionMap; // keyBindIds:KeyNFlag
	SHORT numKeyBinds;
public:
	KeyBinder();
	~KeyBinder();

	// purpose: Create keybind, return -1 otherwise. Keybinds stored as
	//			data member.
	int bindKey(bool flagAlt, bool flagCtrl, WORD vKeyCode);
	int bindActionToKey(KeyNFlag kf);
	std::map<SHORT, WORD> giveKeyBinds();
	std::map<SHORT, KeyNFlag> giveActionMap();
	int giveNumKeyBinds();
};

