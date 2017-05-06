#pragma once
#include <Windows.h>
#include <map>
class KeyBinder
{
private:
	// keyBindIds with mapped vKeyCodes
	std::map<SHORT, WORD> keyBindIds;
	SHORT numKeyBinds;
public:
	KeyBinder();
	~KeyBinder();
	// purpose: Create keybind, return -1 otherwise. Keybinds stored as
	//			data member.
	int bindKey(bool flagAlt, bool flagCtrl, WORD vKeyCode);
	std::map<SHORT, WORD> giveKeyBinds();
};

