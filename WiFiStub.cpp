#ifdef _WINDOWS

#include "WiFiStub.h"
#include <string.h>
#include "StringUtils.h"

/* extern */ WiFiStub WiFi;


WiFiStub::WiFiStub()
  : _ssid(nullptr),
	_password(nullptr),
	_key(nullptr),
	_localIp(nullptr)
{
	StringUtils::CopyString(_localIp, "<Local IP", strlen("<Local IP"));
}


void WiFiStub::mode(EMode mode)
{
}


WiFiStub::EStatus WiFiStub::begin(const char* ssid /* = "" */, const char* password /* = "" */, const char* key /* = "" */)
{
	StringUtils::CopyString(_ssid, ssid, strlen(ssid));
	StringUtils::CopyString(_password, password, strlen(password));
	StringUtils::CopyString(_key, key, strlen(key));
	return WL_CONNECTED;
}


char* WiFiStub::localIP()
{
	return _localIp;
}

#endif // _WINDOWS