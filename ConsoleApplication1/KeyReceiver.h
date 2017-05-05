#pragma once
#include <Windows.h>
class KeyReceiver
{
private:
	bool flagCtrl; // if ctrl key was held down
	bool flagAlt; // if alt key was held down 
	WORD vKeyCode; // keydown scancode !!! To be changed to INPUT type, maybe. We'll see.
	void reset();
public:
	KeyReceiver();
	~KeyReceiver();
	void getKeyEvent();
};

