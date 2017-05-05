#include "stdafx.h"
#include "KeyReceiver.h"
#include <iostream>

KeyReceiver::KeyReceiver()
{
	this->flagCtrl = false;
	this->flagAlt = false;
	this->scanCode = 0;
}


KeyReceiver::~KeyReceiver()
{
}

// purpose: return INPUT that holds VK code.
INPUT KeyReceiver::getKeyEvent()
{
	INPUT inp = { 0 };
	return inp;
}

// purpose: return a scan code on a button's pressdown.
DWORD KeyReceiver::getScanCode()
{
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	//INPUT_RECORD inRecord = { 0 };
	INPUT_RECORD *inpRecord = new INPUT_RECORD[10];
	DWORD eventsReadVal;
	LPDWORD eventsRead = &eventsReadVal;
	ReadConsoleInput(handle, inpRecord, 1, eventsRead);
	return 0;
}