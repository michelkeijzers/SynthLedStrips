// ClassNames.h

#pragma once

// Used to include variable class names
#define stringify(x) #x
#define HEADER_FILE(a) stringify(a.h)

// Class names
#ifdef _WINDOWS

#define ARDUINO_CLASS				ArduinoStub
#define DMX_SIMPLE_CLASS		    DmxSimpleStub
#define FAST_LED_CLASS				FastLedStub
#define SPI_RAM_CLASS				SpiRAMStub
#define SERIAL_CLASS				SerialStub
#define MIDI_CLASS					MidiStub
#define SPI_CLASS					SpiStub
#define SPI_MEMORY_CLASS			SpiMemoryStub
#define SPIFFS_CLASS				SpiffsStub
#define SD_CLASS					SdStub
#define IR_REMOTE_CLASS				IrRemoteStub
#define LIQUID_CRYSTAL_CLASS		LiquidCrystalStub
#define RF24_CLASS					Rf24Stub
#define WIFI_CLASS					WiFiStub
#define ASYNC_TCP_CLASS				AsyncTcpStub
#define ESP_ASYNC_WEB_SERVER_CLASS	ESPAsyncWebServerStub
#define ASYNC_ELEGANT_OTA_CLASS		AsyncElegantOtaStub

#else // NON _WINDOWS

#define strcpy_s(d,d_sz,s)			strcpy(d,s);
#define ABS							abs
#define MIN(a,b)					(((a)<(b))?(a):(b))
#define MAX(a,b)					(((a)>(b))?(a):(b))
#define FastLedCRGB					CRGB

#define ARDUINO_CLASS				Arduino
#define DMX_SIMPLE_CLASS			DmxSimple
#define FAST_LED_CLASS				FastLED
#define SPI_RAM_CLASS				SpiRAM
#define SERIAL_CLASS				Arduino
#define MIDI_CLASS					MIDI
#define SPI_CLASS					SPI
#define SPI_MEMORY_CLASS			SPIMemory
#define SPIFFS_CLASS				SPIFFS
#define SD_CLASS					SD
#define IR_REMOTE_CLASS				IRremote
#define LIQUID_CRYSTAL_CLASS		LiquidCrystal
#define RF24_CLASS					RF24
#define WIFI_CLASS					WiFi
#define ASYNC_TCP_CLASS				AsyncTCP
#define ESP_ASYNC_WEB_SERVER_CLASS	ESPAsyncWebServer
#define ASYNC_ELEGANT_OTA_CLASS		AsyncElegantOTA

#endif // _WINDOWS
