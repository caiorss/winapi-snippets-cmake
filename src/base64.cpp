// Author: Caio Rodrigues
// Brief:  Test base64 encoding/decoding with Windows API.
//---------------------------------------------------------
#include <iostream>
#include <string>
#include <iomanip>

#include <windows.h>
#include <wincrypt.h>


namespace Base64 {
	auto encode(const std::string& text)    -> std::string;
	auto decode(const std::string& textB64) -> std::string;
}

int main(){
	std::cout << std::boolalpha;
	std::cout << "Test 1 - Base 64 REPL" << std::endl;

	std::string line;
	std::string encoded;

	while (true) {
		std::cout << " => Enter some text: ";
		std::getline(std::cin, line);
		if (line == "") continue;
		if (line == "exit") 
			break;
		encoded = Base64::encode(line);
		std::cout << "Encoded text = " << encoded << "\n";
		std::cout << "Decoded text = " << Base64::decode(encoded)
			      << "\n--------------------------------\n";
				  
	}
	//std::cout << " Enter RETURN to exit" << std::endl;
	//std::cin.get();
	return 0;
}

namespace Base64 {
	/** Encode String to Base64 - test it here: https://www.base64decode.org/ */
	auto encode(const std::string& text) -> std::string
	{
		DWORD size;
		// Get size needed to store the base 64 output.
		::CryptBinaryToStringA((BYTE*)text.data(), text.size(), 0x01, nullptr, &size);
		std::string output(size - 1, 0x00);
		::CryptBinaryToStringA((BYTE*)text.data(), text.size(), 0x01, &output[0], &size);
		// Remove characters '\r\n' CR-LF from the end of string
		return output.substr(0, output.size() - 2);
	}

	/* Decode text from Brase64 */
	auto decode(const std::string& textB64) -> std::string {
		DWORD size;
		::CryptStringToBinaryA(textB64.data(), textB64.size(),
			CRYPT_STRING_BASE64, nullptr, &size, nullptr, nullptr);
		std::string output(size, 0x00);
		::CryptStringToBinaryA(textB64.data(), textB64.size(),
			CRYPT_STRING_BASE64, (BYTE*)&output[0], &size, nullptr, nullptr);
		return output;
	}

}
