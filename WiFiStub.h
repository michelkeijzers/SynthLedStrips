#ifdef _WINDOWS

#pragma once

enum EMode { WIFI_STA };

class WiFiStub
{
public:
	enum EStatus { WL_CONNECTED, WL_IDLE_STATUS };

	WiFiStub();

	void mode(EMode mode);
	EStatus begin(const char* ssid = "", const char* password = "", const char* key = "");
	char* localIP();

private:
	char* _ssid;

	char* _password;

	// Used for WEP
	char* _key;
	char* _localIp;
};


extern WiFiStub WiFi;

#endif _WINDOWS