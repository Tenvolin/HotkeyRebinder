#pragma once
#include <Windows.h>

struct KeyNFlag {
	bool flagAlt;
	bool flagCtrl;
	WORD vKeyCode;
};

// purpose: Receive input key from a console input buffer and store virtual-key
//			code and modifier-key flags in this class.
// notes:	Valid modifier-keys: ctrl, alt.
class KeyReceiver
{
private:
	bool flagCtrl; // if ctrl key was held down
	bool flagAlt; // if alt key was held down 
	WORD vKeyCode; // keydown scancode !!! To be changed to INPUT type, maybe. We'll see.
public:
	void reset(); // purpose: Reset all member variables.
	KeyReceiver();
	~KeyReceiver();
	void getKeyEvent();
	KeyNFlag getKeyNFlag();
};

