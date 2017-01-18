// File:		hexd.cpp
// Author:		Samuel McFalls
// Date:		01/27/17
// Description:	Project 0: Hexdump
//				Prints out a hex dump of a given input file.
//				Usage: hexdump <filename>

#include <iostream>
#include <string>
#include <cstdint>
#include <fstream>
#include <cstdlib>

int main(int argc, char* argv[]) {

	// If an incorrect number of arguments is given, we can immediately terminate.
	if (argc != 2) {
		std::cout << "Usage: hexdump <filename>\n";
		return EXIT_FAILURE;
	}

	const std::string FILENAME = argv[1];

	std::ifstream inStream;

	inStream.open(FILENAME, std::ios::binary);

	if (!inStream.is_open()) {
		std::cout << "Could not open \"" << FILENAME << "\". It does not exist or contains errors.\n";
		return EXIT_FAILURE;
	}

	// Binary value read from the file
	uint8_t value;

	// Buffer to store the hex value of a byte
	// I'm not sure why we need 3 elements in the buffer
	char valueBuffer[3];

	// Counter for the number of bytes read. Used to format output
	size_t byteCount = 0;

	// Buffer to store the count value in hex
	char countBuffer[8];

	while (inStream.read(reinterpret_cast<std::fstream::char_type*>(&value), sizeof value)) {

		if (byteCount % 16 == 0) {
			std::sprintf(countBuffer, "%07X", byteCount);
			if (byteCount == 0) {
				std::cout << countBuffer;
			}
			else {
				std::cout << "\n" << countBuffer;
			}
		}

		if (byteCount % 2 == 0) {
			std::cout << " ";
		}

		std::sprintf(valueBuffer, "%02X", value);
		std::cout << valueBuffer;

		byteCount++;

	}

	return EXIT_SUCCESS;
}