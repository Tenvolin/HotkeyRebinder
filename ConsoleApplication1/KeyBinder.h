#pragma once
#include <Windows.h>
#include <map>
#include "KeyReceiver.h"

class KeyBinder
{
private:
	// keyBindIds:vKeyCodes
	std::map<SHORT, WORD> IdToVkeyMap;
	std::map<SHORT, KeyNFlag> IdToKnfMap;
	SHORT numKeyBinds;
public:
	KeyBinder();
	~KeyBinder();
	// purpose: Create keybind, return -1 otherwise. Keybinds stored as
	//			data member.
	int bindKey(bool flagAlt, bool flagCtrl, WORD vKeyCode);
	std::map<SHORT, WORD> giveKeyBinds();
};

