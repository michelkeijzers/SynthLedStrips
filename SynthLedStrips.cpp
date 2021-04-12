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
	//midiD.begin();

	_midiKeyboards.Initialize();
	_patterns.Initialize();
	_ledStrips.Initialize();

	SetPatterns();
}


/* static */ void SynthLedStrips::SetPatterns()
{
//#pragma warning( disable: 6386 )
//#pragma warning(pop)
	PatternMidiNoteOnOff* pattern_0 = new (_patterns.GetPatternData(0)) PatternMidiNoteOnOff();
	pattern_0->SetBackgroundColor(LedColor::EColor::Black); // Galaxy
	pattern_0->SetBackgroundColorTime(1000);
	pattern_0->SetForegroundColor(LedColor::EColor::White);
	pattern_0->SetForegroundColorTime(4000);
	pattern_0->SetFadeTimeNoteOn(10000);
	pattern_0->SetFadeTimeNoteOff(20000);
	pattern_0->SetMoveRightTime(30000);
	pattern_0->SetMoveLeftTime(500);
	pattern_0->SetNoteOnVelocityIntensity(255);
	_patterns.SetPattern(0, pattern_0, &_midiKeyboards.GetMidiKeyboard(0), &_ledStrips.GetLedStrip(0));
	pattern_0->Start();

	PatternOff* pattern_1 = new (_patterns.GetPatternData(1)) PatternOff();
	_patterns.SetPattern(1, pattern_1, &_midiKeyboards.GetMidiKeyboard(0), &_ledStrips.GetLedStrip(1));
	pattern_1->Start();

	PatternOff* pattern_2 = new (_patterns.GetPatternData(2)) PatternOff();
	/*
	pattern_2->SetBackgroundColor(LedColor::EColor::Black);
	pattern_2->SetBackgroundColorTime(10000);
	pattern_2->SetForegroundColor(LedColor::EColor::Red);
	pattern_2->SetForegroundColorTime(4000);
	pattern_2->SetDirection(true);
	pattern_2->SetLedTime(50000);
	pattern_2->SetLedWidth(10);
	*/
	_patterns.SetPattern(2, pattern_2, &_midiKeyboards.GetMidiKeyboard(1), &_ledStrips.GetLedStrip(2));
	pattern_2->Start();

	PatternKnightRider* pattern_3 = new (_patterns.GetPatternData(3)) PatternKnightRider();
	pattern_3->SetBackgroundColor(LedColor::EColor::Rainbow);
	pattern_3->SetBackgroundColorTime(10000);
	pattern_3->SetForegroundColor(LedColor::EColor::Red);
	pattern_3->SetForegroundColorTime(4000);
	pattern_3->SetDirection(true);
	pattern_3->SetLedTime(1000);
	pattern_3->SetLedWidth(10);
	_patterns.SetPattern(3, pattern_3, &_midiKeyboards.GetMidiKeyboard(1), &_ledStrips.GetLedStrip(3));
	pattern_3->Start();
}


/* static */ void SynthLedStrips::Loop()
{
	SerialUtils::PrintUint("Millis", millis());
	ProcessMidi();
	_midiKeyboards.Process();

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
		_midiProcessor.Process(&_configuration, &_midiKeyboards, &_ledStrips, &_patterns,
			midiB.getType(), midiB.getChannel(), midiB.getData1(), midiB.getData2());
	}

	while (midiC.read())
	{
		_midiProcessor.Process(&_configuration, &_midiKeyboards, &_ledStrips, &_patterns,
			midiC.getType(), midiC.getChannel(), midiC.getData1(), midiC.getData2());
	}
}
