#include <iostream>
#include <exception>
#include "WAVFile.h"

int main() {
	try {
		WAVFile file("D:/Study/OP/examples/Lab4/example.wav");
	}
	catch (std::exception& exception) {
		std::cout << exception.what();
	}
	return 0;
}