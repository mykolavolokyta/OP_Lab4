#include "WAVFile.h"
#include "WAVExtender.h"
#include <iostream>
#include <fstream>

WAVExtender::WAVExtender(const WAVFile& file, int n) : file(file), n(n) {}

void WAVExtender::extend(std::string result) {
	std::string::size_type pos = result.find_last_of(".");
	if (pos == std::string::npos) throw std::exception("[ERROR] Result file should be *.wav");
	std::string extension = result.substr(pos + 1);
	if (extension != "wav") throw std::exception("[ERROR] Result file should be *.wav");
	
	std::ofstream out(result, std::ios::binary);
	if (!out) throw std::exception(("[ERROR] Can`t open file with name \"" + result + "\".").c_str());

	int8_t* new_data = new int8_t[file.subchunk2.subchunk2Size * n];
	for (int i = 0; i < file.subchunk2.subchunk2Size; i += file.subchunk1.blockAlign) {
		for (int j = 0; j < n * file.subchunk1.blockAlign; j += file.subchunk1.blockAlign) {
			memcpy_s(new_data + i * n + j, file.subchunk1.blockAlign, file.data + i, file.subchunk1.blockAlign);
		}
	}
	RIFFHEADER _riffheader{
		file.riffheader.chunkId,
		36 + file.subchunk2.subchunk2Size * n,
		file.riffheader.format };

	SUBCHUNK1 _subchunk1{
		file.subchunk1.subchunk1Id,
		file.subchunk1.subchunk1Size,
		file.subchunk1.audioFormat,
		file.subchunk1.numChannels,
		file.subchunk1.sampleRate / n,
		file.subchunk1.byteRate,
		file.subchunk1.blockAlign * n,
		file.subchunk1.bitsPerSample * n
	};

	SUBCHUNK2 _subchunk2{
		file.subchunk2.subchunk2Id,
		file.subchunk2.subchunk2Size * n
	};
	out.write((char*)&_riffheader, sizeof(RIFFHEADER));
	out.write((char*)&_subchunk1, sizeof(SUBCHUNK1));
	out.write((char*)&_subchunk2, sizeof(SUBCHUNK2));
	out.write((char*)new_data, file.subchunk2.subchunk2Size * n);
	out.close();
	delete[] new_data;
}


WAVExtender::~WAVExtender() {}