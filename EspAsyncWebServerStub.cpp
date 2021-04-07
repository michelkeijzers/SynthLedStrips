#ifdef _WINDOWS

#include "EspAsyncWebServerStub.h"

WebRequestMethodComposite HTTP_GET;

AsyncWebServer::AsyncWebServer(uint8_t portNumber)
{
}


AsyncCallbackWebHandler& AsyncWebServer::on(const char* uri, WebRequestMethodComposite method, ArRequestHandlerFunction onRequest)
{
	AsyncCallbackWebHandler* handler = nullptr;
	return *handler;
}


void AsyncWebServer::begin()
{
} 


AsyncWebServerRequest::AsyncWebServerRequest()
{
}


void AsyncWebServerRequest::send(uint16_t length, const char* textType, const char* text)
{
}

#endif // WINDOWS
