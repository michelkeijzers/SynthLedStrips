#ifdef _WINDOWS

#pragma once

#include <stdio.h>

class SpiffsStub
{
public:
	bool begin(bool mount = true);

	bool format();

	FILE* open(char* path, char* option);

private:
	const char* SPIFFS_DIR = "E:\\ESP32_SPIFFS";
	SpiffsStub() {}
};

#endif // _WINDOWS
