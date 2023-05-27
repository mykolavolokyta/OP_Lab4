#include <iostream>
#include <exception>
#include "WAVFile.h"
#include "WAVExtender.h"
#include "functions.h"

int main(int argc, char** argv) {
	if (argc != 4 || !is_number(argv[3])) {
		std::cout << "[ERROR] Usage: \"Lab4.exe input.wav output.wav n\".";
	}
	try {
		WAVFile file(argv[1]);
		WAVExtender extender(file, atoi(argv[3]));
		extender.extend(argv[2]);
		WAVFile file1(argv[2]);
	}
	catch (std::exception& exception) {
		std::cout << exception.what();
	}
	return 0;
}