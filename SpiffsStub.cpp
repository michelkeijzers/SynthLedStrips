#ifdef _WINDOWS

#include <windows.h>
#include "SpiffsStub.h"

SpiffsStub SPIFFS;

bool SpiffsStub::begin(bool mount /* = true */)
{
	return true;
}


bool SpiffsStub::format()
{
	return true;
}


FILE* SpiffsStub::open(const char* fileName, const char* mode)
{
	char fullFileName[255] = {0};
	strcat_s(fullFileName, SPIFFS_DIR);
	strcat_s(fullFileName, "//");
	strcat_s(fullFileName, fileName);
	FILE* file = new FILE();
	fopen_s(&file, fullFileName, mode);
	return file;
}


void SpiffsStub::close(FILE* file)
{
}

#endif // _WINDOWS
