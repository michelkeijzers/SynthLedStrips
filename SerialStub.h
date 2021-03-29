#pragma once

// Decimal
constexpr auto DEC = 1;
constexpr auto HEX = 2;

class SerialClass
{
public:
	void begin(int baudrate);

	void println(const char* str);
	void println(int value);
	void println(int value, int mode);

	void print(const char* str);
	void print(int value);
	void print(int value, int mode);

	static void flush();

private:
	wchar_t _message[256];
	wchar_t _string[256];
};


class SerialPort
{
public:
	SerialPort() {};
	~SerialPort() {};
};

extern SerialClass Serial;
extern SerialClass Serial1;
extern SerialClass Serial2;
//extern SerialClass Serial3;

extern SerialPort SoftwareSerial;
extern SerialPort HardwareSerial;
