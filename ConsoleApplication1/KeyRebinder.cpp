#include <iostream>
#include <Windows.h>

int main() {
	int yes = 0;
	if (RegisterHotKey(NULL, 1, 0, VK_UP))
	{
		std::cout << "hotkey for VK_UP registered!" << std::endl;
	}

	MSG msg = { 0 };

	/*while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (msg.wParam == 1)
		{
			std::cout << "WM_HOTKEY received\n" << std::endl;
		}
	}*/
	while (1)
	{

	}

	//while (1) {
	//	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	//	{
	//		// the 'Up' arrow key is currently being held down
	//		std::cout << "Hello, World: " << yes << std::endl;
	//		yes++;
	//		Sleep(150);
	//	}

	//}

}