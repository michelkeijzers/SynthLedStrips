// StringUtils.h
// String/char array utilities

#pragma once

#include <cstdint>

class StringUtils
{
public:
	static int8_t GetIndexOfLastLetter(const char* text, uint8_t length);

	static char* TrimWhitespace(char* str);

	static void ToUpper(char* str);
	static void ToLower(char* str);

	static uint8_t GetWordLength(const char* stringToAnalyze, uint8_t startIndex);

	static void CopyString(char* destination, const char* source, size_t sourceLength);

private:
	StringUtils();
};
