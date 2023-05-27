#include <iostream>
#include <exception>
#include "WAVFile.h"
#include "WAVExtender.h"

int main() {
	try {
		WAVFile file("D:/Study/OP/examples/Lab4/example.wav");
		WAVExtender extender(file, 2);
		extender.extend("D:/Study/OP/examples/Lab4/output.wav");
	}
	catch (std::exception& exception) {
		std::cout << exception.what();
	}
	return 0;
}