#pragma once
#include "WAVFile.h"
#include <string>

class WAVExtender {
	WAVFile file;
	int n;
public:
	WAVExtender(const WAVFile&, int);
	void extend(std::string);
	~WAVExtender();
};