#ifdef _WINDOWS

#pragma once

#include <cstdint>
#include <functional>



class AsyncCallbackWebHandler;
class WebRequestMethodComposite
{

};

extern WebRequestMethodComposite HTTP_GET;

class AsyncWebServerRequest;

typedef std::function<void(AsyncWebServerRequest *request)> ArRequestHandlerFunction;

class AsyncCallbackWebHandler
{
};


class AsyncWebServer
{
public:
	AsyncWebServer(uint8_t portNumber);

	AsyncCallbackWebHandler& on(const char* uri, WebRequestMethodComposite method, ArRequestHandlerFunction onRequest);

	void begin();
};


class AsyncWebServerRequest
{
public:
	AsyncWebServerRequest();

	void send(uint16_t length, const char* textType, const char* text);
};

#endif // _WINDOWS