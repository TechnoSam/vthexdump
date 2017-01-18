// File:		hexd.cpp
// Author:		Samuel McFalls
// Date:		01/27/17
// Description:	Project 0: Hexdump
//				Prints out a hex dump of a given input file.
//				Usage: hexdump <filename>

#include <iostream>
#include <iomanip>
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

	// Counter for the number of bytes read. Used to format output
	size_t byteCount = 0;

	while (inStream.read(reinterpret_cast<std::fstream::char_type*>(&value), sizeof value)) {

		if (byteCount % 16 == 0) {
			if (byteCount == 0) {
				std::cout << std::hex << std::setw(7) << std::setfill('0') << byteCount;
			}
			else {
				std::cout << "\n" << std::hex << std::setw(7) << std::setfill('0') << byteCount;
			}
		}

		if (byteCount % 2 == 0) {
			std::cout << " ";
		}

		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)value;

		byteCount++;

	}

	return EXIT_SUCCESS;
}