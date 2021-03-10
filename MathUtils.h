// Mathtils.h

#pragma once

// https://www.daycounter.com/Calculators/Sine-Generator-Calculator.phtml

class MathUtils
{
public:
	static int Abs(int a);

	static int Min(int a, int b);

	static int Min(int a, int b, int c);
	
	static int Max(int a, int b);

	static int Max(int a, int b, int c);

	static int Sin(int angle); // angle 0-255, return 0-255

private:
	MathUtils();

	~MathUtils();

	static const int SINE_TABLE_ELEMENTS = 256;

	static const int _sineTable[SINE_TABLE_ELEMENTS];
};
