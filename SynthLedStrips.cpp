// LedStripSynthShow.ino
//
//           
//             M E G A                 Cmd
//            Flash SRAM   SRAMnew     Data
// Maximum:  
// Current:  
//       %:      9    71         8
//
// Stack:
//
// Class          ::Method					   Parameters     Local Variables
// Total  

// Interrupt

#ifdef _WINDOWS
#include <windows.h>
#include "MemoryUtils.h"
#endif
#include <new>
#include "SerialUtils.h"
#include "MathUtils.h"
#include "SynthLedStrips.h"
#include "MidiKeyboards.h"
#include "Configuration.h"
#include "Patterns.h"
#include "MidiKeyboards.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(MIDI_CLASS)
#include HEADER_FILE(SERIAL_CLASS)
#include HEADER_FILE(FAST_LED_CLASS)
#include HEADER_FILE(WIFI_CLASS)
#include HEADER_FILE(ASYNC_TCP_CLASS)
#include HEADER_FILE(ESP_ASYNC_WEB_SERVER_CLASS)
#include HEADER_FILE(ASYNC_ELEGANT_OTA_CLASS)
#include "Patterns.h"
#include "PatternOff.h"
#include "PatternKnightRider.h"
#include "PatternMidiNoteOnOff.h"
#include "AssertUtils.h"
#include "MidiProcessor.h"

#define USE_SERIAL

/* static */ Configuration SynthLedStrips::_configuration;
/* static */ LedStrips SynthLedStrips::_ledStrips;
/* static */ Patterns SynthLedStrips::_patterns;
/* static */ MidiKeyboards SynthLedStrips::_midiKeyboards;
/* static */ MidiProcessor SynthLedStrips::_midiProcessor;


char _ssid[] = "yourNetwork";      // your network SSID (name)
char _password[] = "secretPassword";   // your network password

AsyncWebServer server(80);


#ifndef USE_SERIAL
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiA);
#endif

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiB);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, midiC);
//MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, midiD);


SynthLedStrips::SynthLedStrips()
{
}


SynthLedStrips::~SynthLedStrips()
{
}


/* static */ void SynthLedStrips::Setup()
{
	randomSeed(analogRead(0));

	// Generic GPIO.
	pinMode(LED_BUILTIN, OUTPUT);

	// WIFI / OTA, see https://randomnerdtutorials.com/esp32-ota-over-the-air-arduino/ or for PlatformIO.
	WiFi.mode(WIFI_STA);
	WiFi.begin(_ssid, _password);

	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(200, "text/plain", "Hi! I am ESP32.");
		});

	AsyncElegantOTA.begin(&server);
	
	server.begin();
	AsyncElegantOTA.loop();

	// Configuration
	_configuration.OpenFile();

	// Serial/MIDI.
	Serial.begin(115200);
	Serial.println("LED Strip Synth 0.1");

	midiB.begin();
	midiC.begin();

	_midiKeyboards.Initialize();
	_patterns.Initialize();
	_ledStrips.Initialize();
}


/* static */ void SynthLedStrips::Loop()
{
	//SerialUtils::PrintUint("Millis", millis());
	ProcessMidi();
	_midiKeyboards.Process();
	_midiKeyboards.DebugPrint();

	if (_ledStrips.IsOn())
	{
		_patterns.Process();
		_ledStrips.Process();
	}

	_midiKeyboards.ClearNewFlags();

	if (_ledStrips.IsOn())
	{
		FastLED.show();
	}

	delay(1); //TODO Check if needed
}


/* static */ MidiKeyboard& SynthLedStrips::GetMidiKeyboards(uint8_t index)
{
	AssertUtils::MyAssert(index <= NR_OF_MIDI_KEYBOARDS);
	return _midiKeyboards.GetMidiKeyboard(index);
}


/* static */ void SynthLedStrips::ProcessMidi()
{
	while (midiB.read())
	{
		_midiProcessor.Process(&_configuration, &_midiKeyboards, &_ledStrips, _patterns,
			midiB.getType(), midiB.getChannel(), midiB.getData1(), midiB.getData2());
	}

	while (midiC.read())
	{
		_midiProcessor.Process(&_configuration, &_midiKeyboards, &_ledStrips, _patterns,
			midiC.getType(), midiC.getChannel(), midiC.getData1(), midiC.getData2());
	}
}
