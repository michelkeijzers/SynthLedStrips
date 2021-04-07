// StringUtils.cpp
// String/char array utilities

#include <ctype.h>
#include <string.h>

#include "CharUtils.h"
#include "StringUtils.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)

StringUtils::StringUtils()
{
}


/**
 * -1 if not found, else index, only checks a-z, no capitals
 */
/* static */ int8_t StringUtils::GetIndexOfLastLetter(const char* text, uint8_t length)
{
	for (int8_t index = length - 1; index >= 0; index--)
	{
		char character = CharUtils::ToLower(text[index]);
		if (character >= 'a' && character <= 'z')
		{
			return index;
		}
	}

	return -1;
}


/* static */ char* StringUtils::TrimWhitespace(char* str)
{
	char* end;

	// Trim leading space
	while (isspace(static_cast<unsigned char>(* str)))
	{
		str++;
	}

	if (*str == 0)  // All spaces?
	{
		return str;
	}

	// Trim trailing space
	end = str + strlen(str) - 1;
	while (end > str && isspace(static_cast<unsigned char>(* end)))
	{
		end--;
	}

	// Write new null terminator character
	end[1] = '\0';

	return str;
}


/* static */ void StringUtils::ToUpper(char* str) 
{
	while (*str) 
	{
		*str = CharUtils::ToUpper(char(str[0U]));
		str++;
	}
}


/* static */ void StringUtils::ToLower(char* str)
{
	while (*str)
	{
		*str = CharUtils::ToLower(char(str[0U]));
		str++;
	}
}


/*
 * Returns the number of non whitespace characters starting from startIndex
 *
 * NOT CHECKED
 */

/* static */ uint8_t StringUtils::GetWordLength(const char* stringToAnalyze, uint8_t startIndex)
{
	uint8_t count = 0;
	size_t length = strlen(stringToAnalyze);

	while (startIndex < length)
	{
		if (isspace(stringToAnalyze[startIndex]))
		{
			break;
		}

		count++;
	}

	return count;
}


/* static */ void StringUtils::CopyString(char* destination, const char* source, size_t sourceLength)
{
	if (destination != nullptr)
	{
		delete[] destination;
	}
	
	destination = new char[sourceLength + 1];
	strcpy_s(destination, sourceLength + 1, source);
}
