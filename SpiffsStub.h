#ifdef _WINDOWS

#pragma once

#include <stdio.h>

class SpiffsStub
{
public:
	bool begin(bool mount = true);

	bool format();

	FILE* open(const char* path, const char* option);

	void close(FILE* file);

private:
	const char* SPIFFS_DIR = "E:\\ESP32_SPIFFS";
};

extern SpiffsStub SPIFFS;

#endif // _WINDOWS
