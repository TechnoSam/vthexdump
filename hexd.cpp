// File:		hexd.cpp
// Author:		Samuel McFalls
// Date:		01/27/17
// Description:	Project 0: Hexdump
//				Prints out a hex dump of a given input file.
//				Usage: hexdump <filename>

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <cstdlib>

/**
	Prints a line of the hexdump in the following format:
	(A - address characters, X - hex characters, C - ascii characters)
	AAAAAAA: XX XX XX ... CCCCCC...
	@param address The starting address of the given vector of bytes
	@param bytesPerLine The number of expected bytes per line; used to fill incomplete final lines
	@param values The vector containing the bytes to print. Will print all bytes in the vector, irrespective of size.
*/
void printLine(const size_t address, const int bytesPerLine, std::vector<uint8_t>& values);

int main(int argc, char* argv[]) {

	// Constants
	const int BYTES_PER_LINE = 16;

	// If an incorrect number of arguments is given, we can immediately terminate.
	if (argc != 2) {
		std::cout << "Usage: hexdump <filename>\n";
		return EXIT_FAILURE;
	}

	const std::string FILENAME = argv[1];

	std::ifstream inStream;

	inStream.open(FILENAME, std::ios::binary);

	// If we could not open the file, we can terminate.
	if (!inStream.is_open()) {
		std::cout << "Could not open \"" << FILENAME << "\". It does not exist or contains errors.\n";
		return EXIT_FAILURE;
	}

	// Binary value read from the file
	uint8_t value;

	// Vector to store the past BYTES_PER_LINE bytes read so they can be printed at the end of a line
	std::vector<uint8_t> line;

	// Counter for the number of bytes read. Used to format output
	size_t byteCount = 0;

	while (inStream.read(reinterpret_cast<std::fstream::char_type*>(&value), sizeof value)) {

		byteCount++;

		line.push_back(value);

		if (byteCount % BYTES_PER_LINE == 0 && byteCount != 0) {

			printLine(byteCount - BYTES_PER_LINE, BYTES_PER_LINE, line);
			line.clear();

		}

	}

	// If there are any that do not fit in a perfect line of BYTES_PER_LINE, they still need to be printed
	if (byteCount != 0 && byteCount % 16 != 0) {
		printLine(byteCount - (byteCount % BYTES_PER_LINE), BYTES_PER_LINE, line);
	}

	return EXIT_SUCCESS;
}

void printLine(const size_t address, const int bytesPerLine, std::vector<uint8_t>& values) {

	// Print the address
	std::cout << std::hex << std::setw(7) << std::setfill('0') << address << ":";

	// Print the hex values
	for (unsigned int i = 0; i < values.size(); i++) {
		// Every 2 bytes, print a space
		if (i % 2 == 0) {
			std::cout << " ";
		}
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)values.at(i);
	}

	// Space fill if there are not bytesPerLine values available
	// The logic is the same as above, but we print spaces instead of actual values
	if (values.size() != bytesPerLine) {
		for (unsigned int i = values.size(); i < bytesPerLine; i++) {
			if (i % 2 == 0) {
				std::cout << " ";
			}
			std::cout << "  ";
		}
	}

	// Print the ascii with a newline
	std::cout << " ";
	for (unsigned int i = 0; i < values.size(); i++) {
		if (values.at(i) > 31 && values.at(i) < 127) {
			std::cout << (char)values.at(i);
		}
		else {
			std::cout << ".";
		}
	}
	std::cout << "\n";

}