// File:		hexd.cpp
// Author:		Samuel McFalls
// Date:		01/27/17
// Description:	Project 0: Hexdump
//				Prints out a hex dump of a given input file.
//				Usage: hexdump <filename>

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

int main(int argc, char* argv[]) {

	// If an incorrect number of arguments is given, we can immediately terminate.
	if (argc != 2) {
		return EXIT_FAILURE;
	}

	const std::string FILENAME = argv[1];

	std::ifstream inFile;

	inFile.open(FILENAME);

	if (!inFile.is_open()) {
		std::cout << "Could not open \"" << FILENAME << "\". It does not exist or contains errors.";
		return EXIT_FAILURE;
	}

	std::string buffer;

	while (!inFile.eof()) {

		std::getline(inFile, buffer, '\n');

		// If the line contains nothing (not even a newline) then we must be at the end of the file
		if (buffer == "") { break; }

		std::cout << buffer << "\n";

	}

	return EXIT_SUCCESS;
}