#ifdef _WINDOWS

#include <windows.h>
#include "SpiffsStub.h"

FILE* single_file = nullptr;


bool SpiffsStub::begin(bool mount /* = true */)
{
	return true;
}


bool SpiffsStub::format()
{
	return true;
}


FILE* SpiffsStub::open(char* fileName, char* mode)
{
	char fullFileName[255] = {0};
	strcat_s(fullFileName, SPIFFS_DIR);
	strcat_s(fullFileName, "//");
	strcat_s(fullFileName, fileName);
	fopen_s(&single_file, fullFileName, mode);
	return single_file;
}

#endif // _WINDOWS
