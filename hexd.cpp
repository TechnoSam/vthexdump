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
		std::cout << "Could not open \"" << FILENAME << "\". It does not exist or contains errors.";
		return EXIT_FAILURE;
	}

	// I'm not sure why we need 3 elements in the buffer
	char buffer[3];
	uint8_t value;

	while (inStream.read(reinterpret_cast<std::fstream::char_type*>(&value), sizeof value)) {

		if (value > 31 && value < 127) {
			std::sprintf(buffer, "%02X", value);
			std::cout << buffer << "\n";
		}
		else {
			std::cout << ".\n";
		}

	}

	return EXIT_SUCCESS;
}