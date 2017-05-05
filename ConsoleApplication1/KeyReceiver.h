#pragma once
#include <Windows.h>
class KeyReceiver
{
private:
	bool flagCtrl; // if ctrl key was held down
	bool flagAlt; // if alt key was held down 
	WORD scanCode; // keydown scancode !!! To be changed to INPUT type, maybe. We'll see.
public:
	KeyReceiver();
	~KeyReceiver();
	INPUT getKeyEvent();
	DWORD getScanCode();
};

