﻿#pragma once
#include <string>

typedef struct {
    int32_t chunkId;   // Завжди містить значення 0x52494646 (літери "RIFF")
    int32_t chunkSize; // 36 + розмір другого підрозділу в байтах
    // Іншими словами 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
    // Це розмір всього файла мінус 8 байтів які займають поля chunkId та chunkSize
    int32_t format;    // Для wav-файла це завжди 0x57415645 (літери "WAVE")
} RIFFHEADER;

typedef struct {
    int32_t subchunk1Id;   // Завжди 0x666d7420 – літери "fmt "
    int32_t subchunk1Size; // Завжди 16 для аудіо PCM. Це розмір частини підрозділу, що слідує після цього числа
    int16_t audioFormat;   // PCM = 1
    int16_t numChannels;   // Mono = 1, Stereo = 2
    int32_t sampleRate;    // Наприклад 44100
    int32_t byteRate;      // == SampleRate * NumChannels * BitsPerSample/8
    int16_t blockAlign;    // == NumChannels * BitsPerSample/8
    int16_t bitsPerSample; // 8 bits = 8, 16 bits = 16, etc.
} SUBCHUNK1;

typedef struct {
    int32_t subchunk2Id;   // 0x64617461 – літери "data"
    int32_t subchunk2Size; // == NumSamples * NumChannels * BitsPerSample/8, кількість байтів аудіоданих
} SUBCHUNK2;

class WAVFile {
    std::string filename;
    RIFFHEADER riffheader;
    SUBCHUNK1 subchunk1;
    SUBCHUNK2 subchunk2;
    int8_t* data;         // семпли
public:
    WAVFile(std::string);
    WAVFile(const WAVFile&);
    ~WAVFile();
    friend class WAVExtender;
};
