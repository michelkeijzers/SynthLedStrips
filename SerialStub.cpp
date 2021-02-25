#ifdef _WINDOWS


#include "SerialStub.h"
#include "Windows.h"
#include "stdio.h"


SerialClass Serial;


SerialPort SoftwareSerial;
SerialPort HardwareSerial;


void SerialClass::begin(int baudrate)
{
	static_cast<int>(baudrate);
}


void SerialClass::println(const char* str)
{
	size_t sizet;
	mbstowcs_s(&sizet, _string, str, strlen(str) + 1);
	swprintf_s(_message, L"%s\n", _string);
	OutputDebugString(_message);
}


void SerialClass::println(int value, int mode)
{
	(void)mode;

	swprintf_s(_message, L"%d\n", value);
	OutputDebugString(_message);
}



void SerialClass::println(int value)
{
	println(value, DEC);
}


void SerialClass::print(const char* str)
{
	size_t sizet;
	mbstowcs_s(&sizet, _string, str, strlen(str) + 1);
	swprintf_s(_message, L"%s", _string);
	OutputDebugString(_message);
}


void SerialClass::print(int value, int mode)
{
	(void)mode;

	swprintf_s(_message, L"%d", value);
	OutputDebugString(_message);
}


void SerialClass::print(int value)
{
	print(value, DEC);
}


void SerialClass::flush()
{
}


#endif // _WINDOWS