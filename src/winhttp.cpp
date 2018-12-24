// Brief:   Http request and file download using Win APIs winnit and Urlmon.
// Author:   Caio Rodrigues
// Requires: urlon.dll and wininet.lib
//---------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

#include <windows.h>
#include <urlmon.h>   
#include <wininet.h>  
#include <tchar.h> 

// Only for MSVC
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "wininet.lib")

auto launchedFromConsole() -> bool;
auto ExitPrompt() -> void;

// Simple C++ wrapper for the function: URLDownloadToFileA
HRESULT downloadFile(std::string url, std::string file);

void testHTTPRequest();

int main() {
	// ==================  File Download  ========================= //
	//
	std::cout << " ========== HTTP Download with URLMON ====" << std::endl;
	HRESULT hr;

	hr = downloadFile("http://httpbin.org/image/jpeg", "image.jpeg");
	std::cout << " Downloading http://httpbin.org/image/jpeg waiting .." << std::endl;
	if (SUCCEEDED(hr))
		std::cout << "Download successful OK." << '\n';
	else
		std::cout << "Download failed." << '\n';

	std::cout << " Simulate Download failure. Waiting ..." << std::endl;
	hr = downloadFile("httpxpabin.org/image/jpeg-error", "image2.jpeg");
	if (SUCCEEDED(hr))
		std::cout << "Download sucessful OK." << '\n';
	else
		std::cout << "Download failed." << '\n';

	//=============== HTTP Protocol ===================================//
	//
	std::cout << " ========== HTTP Request test ====" << std::endl;
	testHTTPRequest();

	ExitPrompt();

	return 0;
} //================== End of main() =============================//

/** Returns true if program was launched by invoking it from command line console 
  * Returns false if program was launched by clicking on it.
  * Aka: prompt = shell = terminal = console. 
  *===============================================================================*/
auto launchedFromConsole() -> bool 
{
	DWORD procIDs[2];
	DWORD maxCount = 2;
	DWORD result = GetConsoleProcessList((LPDWORD)procIDs, maxCount);
	return result != 1;
}

/** Ask question 'Type RETURN to exit' if program was launched by clicking on it.
  * Note: It is only useful for console programs. If the underlying application 
  * was launched from cmd.exe or any other terminal (aka console), do nothing.
  ******************************************************************************* */
auto ExitPrompt() -> void 
{
	DWORD procIDs[2];
	DWORD maxCount = 2;
	DWORD result = GetConsoleProcessList((LPDWORD)procIDs, maxCount);
	if (result != 1) return;
	std::cout << "\n *** Type RETURN to exit ***" << std::endl;
	std::cin.get();
}

HRESULT downloadFile(std::string url, std::string file) {
	HRESULT hr = URLDownloadToFileA(
		// (pCaller)    Pointer to IUknown instance (not needed)
		NULL
		// (szURL)      URL to the file that will be downloaded
		, url.c_str()
		// (szFileName) File name that the downloaded file will be saved.
		, file.c_str()
		// (dwReserved) Reserverd - always 0
		, 0
		// (lpfnCB)     Status callback
		, NULL
	);
	return hr;
}

void testHTTPRequest() {
	// Reference: http://www.cplusplus.com/forum/beginner/75062/
	HINTERNET hConnect = InternetOpen("Fake browser", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (!hConnect) {
		std::cerr << "Error: Connection Failure.";
		return;
	}

	HINTERNET hAddr = InternetOpenUrl(
		hConnect
		, "http://www.httpbin.org/get"
		, NULL
		, 0
		, INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_KEEP_CONNECTION
		, 0
	);

	if (!hAddr)
	{
		DWORD errorCode = GetLastError();
		std::cerr << "Failed to open URL" << '\n' << "Error Code = " << errorCode;
		InternetCloseHandle(hConnect);
		return;
	}

	// Buffer size - 4kb or 4096 bytes 
	auto bytesReceived = std::string(4096, 0x00);
	DWORD NumOfBytesReceived = 0;
	while (InternetReadFile(hAddr, &bytesReceived[0], 4096, &NumOfBytesReceived) && NumOfBytesReceived)
	{
		std::cout << bytesReceived.substr(0, NumOfBytesReceived - 1);
	}

	InternetCloseHandle(hAddr);
	InternetCloseHandle(hConnect);

} // --- EoF testHTTPRequest() --- // 
