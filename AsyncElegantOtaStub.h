#ifdef _WINDOWS

#pragma once

class AsyncWebServer;
class AsyncWebServerRequest;

class AsyncElegantOTAClass
{
public:
	AsyncElegantOTAClass();

	void begin(AsyncWebServer* server);

	void loop();
};

extern AsyncElegantOTAClass AsyncElegantOTA;

#endif // _WINDOWS
