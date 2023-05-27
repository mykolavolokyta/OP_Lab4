#pragma once
#include "WAVFile.h"
#include <iostream>
#include <string>
#include <fstream>
#include <exception>

WAVFile::WAVFile(std::string _filename) : filename(_filename) {
	std::string::size_type pos = filename.find_last_of(".");
	if (pos == std::string::npos) throw std::exception("[ERROR] File should be *.wav");
	std::string extension = filename.substr(pos + 1);
	if (extension != "wav") throw std::exception("[ERROR] File should be *.wav");
	std::ifstream in(_filename, std::ios::binary | std::ios::ate);
	if (!in) throw std::exception(("[ERROR] Can`t open file with name \"" + filename + "\".").c_str());

	std::ifstream::pos_type file_size = in.tellg();
	in.close();

	in.open(_filename, std::ios::binary);
	in.read((char*)&riffheader, sizeof(RIFFHEADER));
	in.read((char*)&subchunk1, sizeof(SUBCHUNK1));
	in.read((char*)&subchunk2, sizeof(SUBCHUNK2));
		
	if (riffheader.chunkId != 0x46464952) throw std::exception("[ERROR] Bad format!");
	if (riffheader.chunkSize != int(file_size) - 8) throw std::exception("[ERROR] Bad format!");
	if (riffheader.format != 0x45564157) throw std::exception("[ERROR] Bad format!");

	if (subchunk1.subchunk1Id != 0x20746d66) throw std::exception("[ERROR] Bad format!");
	if (subchunk1.subchunk1Size != 16) throw std::exception("[ERROR] Bad format!");
	if (subchunk1.byteRate != subchunk1.sampleRate * subchunk1.numChannels * subchunk1.bitsPerSample / 8) throw std::exception("[ERROR] Bad format!");
	if (subchunk1.blockAlign != subchunk1.numChannels * subchunk1.bitsPerSample / 8) throw std::exception("[ERROR] Bad format!");

	if (subchunk2.subchunk2Id != 0x61746164) throw std::exception("[ERROR] Bad format!");

	data = new int8_t[subchunk2.subchunk2Size];
	in.read((char*)data, sizeof(data));
	in.close();
}

WAVFile::~WAVFile() {
	delete[] data;
}

