// StringUtils.h
// String/char array utilities

#pragma once

#include "SynthLedStripsTypes.h"

class StringUtils
{
public:
	static int8_t GetIndexOfLastLetter(const char* text, uint8_t length);

	static char* TrimWhitespace(char* str);

	static void ToUpper(char* str);
	static void ToLower(char* str);

	static uint8_t GetWordLength(const char* stringToAnalyze, uint8_t startIndex);


private:
	StringUtils();

	~StringUtils();
};

