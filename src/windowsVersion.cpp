#include <iostream>
#include <string>

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

using cstring = const char*;

void showWindowsVersion();

int main() {
	using std::cout;
	using std::endl;
	showWindowsVersion();

	std::cout << " * Enter RETURN to exit." << std::endl;
	std::cin.get();
	return 0;
}

void showWindowsVersion() 
{
	std::cout << "Operating system version" << std::endl;
	std::cout << "------------------------" << std::endl;
	// OSVERSIONINFOEX* ex = new OSVERSIONINFOEX();
	OSVERSIONINFO osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);
	std::cout << "Major version   = " << osvi.dwMajorVersion
		      << "; Minor version = " << osvi.dwMinorVersion
			  << "; szCSDVersion  = " << osvi.szCSDVersion
			  << std::endl;
}

