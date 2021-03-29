#pragma once

#define assert(expression) \
  if (!(expression)) \
  { \
	  Serial.println(F(__FILE__)); \
	  Serial.println(__LINE__, DEC); \
	  Serial.flush(); \
  	abort(); \
  }

//#define assert(expr) AssertUtils::Assert((expr), (__FILE__), (__LINE__));

class AssertUtils
{
public:
	static void MyAssert(bool expression);

	static void MyAssert(bool expression, const char* fileName, int line);
};
