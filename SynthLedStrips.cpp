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

#include "MathUtils.h"
#include "SynthLedStrips.h"
#include "SerialPrint.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(MIDI_CLASS)
#include HEADER_FILE(SERIAL_CLASS)
#include HEADER_FILE(FAST_LED_CLASS)

#include "SynthLedStripsTypes.h"
#include "Speed.h"
#include "Time.h"
#include "LedColor.h"
#include "PatternOff.h"
#include "PatternKnightRider.h"
#include "PatternMidiNoteOnOff.h"

/*
void* operator new(size_t size, void* ptr)
{
	return ptr;
}
*/

#define USE_SERIAL


/* static */ LedStrip SynthLedStrips::_ledStrips[NR_OF_LED_STRIPS];
/* static */ MidiKeyboard SynthLedStrips::_midiKeyboards[NR_OF_MIDI_KEYBOARDS];
/* static */ FastLedCRGB SynthLedStrips:: _leds[NR_OF_LED_STRIPS][NR_OF_LEDS];
/* static */ uint32_t SynthLedStrips::_counter = 0;
/* static */ const uint8_t SynthLedStrips::DATA_PINS[] = { 2, 3, 4, 5 };

#ifndef USE_SERIAL
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiA);
#endif

MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, midiB);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, midiC);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, midiD);


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

	// Serial/MIDI.
	Serial.begin(115200);
	Serial.println("LED Strip Synth 0.1");

	midiB.begin();
	midiC.begin();
	midiD.begin();

	_midiKeyboards[0].SetNrOfKeys(61);
	_midiKeyboards[1].SetNrOfKeys(88);

	// LED STRIPS
	int maxSize = MathUtils::Max(sizeof(PatternOff), sizeof(PatternKnightRider));
	byte* patternData = new byte[maxSize * 4];

	FastLED.addLeds<WS2813, 3, RGB>(_leds[0], NR_OF_LEDS);
	_ledStrips[0].Initialize(DATA_PINS[0], NR_OF_LEDS, _leds[0]);
#pragma warning( disable: 6386 )
	PatternMidiNoteOnOff* pattern_0 = new (patternData) PatternMidiNoteOnOff(_ledStrips[0], _midiKeyboards[0]);
#pragma warning(pop)
	pattern_0->SetBackgroundColor(LedColor::EColor::Black);
	pattern_0->SetForegroundColor(LedColor::EColor::White);
	pattern_0->SetFadeTimeNoteOn(Time::ETime::_10s);
	pattern_0->SetFadeTimeNoteOff(Time::ETime::_20s);
	pattern_0->SetNoteOnVelocityIntensity(255);
	_ledStrips[0].SetPattern(pattern_0);

	FastLED.addLeds<WS2813, 4, RGB>(_leds[1], NR_OF_LEDS);
	_ledStrips[1].Initialize(DATA_PINS[1], NR_OF_LEDS, _leds[1]);
	PatternOff* pattern_1 = new (patternData + maxSize) PatternOff(_ledStrips[1]);
	_ledStrips[1].SetPattern(pattern_1);
	//_ledStrips[1].SetPattern(LedStrip::EPattern::KnightRider, 255, 0, 0, 10, 1);

	FastLED.addLeds<WS2813, 5, RGB>(_leds[2], NR_OF_LEDS);
	_ledStrips[2].Initialize(DATA_PINS[2], NR_OF_LEDS, _leds[2]);
	//_ledStrips[2].SetPattern(LedStrip::EPattern::KnightRider, 255, 0, 0, 10, 5);
	PatternOff* pattern_2 = new (patternData + 2 * maxSize) PatternOff(_ledStrips[2]);
	_ledStrips[2].SetPattern(pattern_2);

	FastLED.addLeds<WS2813, 6, RGB>(_leds[3], NR_OF_LEDS);
	_ledStrips[3].Initialize(DATA_PINS[3], NR_OF_LEDS, _leds[3]);
	PatternKnightRider* pattern_3 = new (patternData + 3 * maxSize) PatternKnightRider(_ledStrips[3]);
	pattern_3->SetBackgroundColor(LedColor::EColor::Black);
	pattern_3->SetForegroundColor(LedColor::EColor::White);
	pattern_3->SetDirection(true);
	pattern_3->SetLedSpeed(Speed::ESpeed::_1s);
	pattern_3->SetLedWidth(10);
	_ledStrips[3].SetPattern(pattern_3);
	//_ledStrips[3].SetPattern(LedStrip::EPattern::KnightRider, 255, 255, 255, 20, 10);
}


/* static */ void SynthLedStrips::Loop()
{
	ProcessMidi();
	ProcessMidiKeyboards();
	ProcessLedStrips();
	ClearNewFlags();
	FastLED.show();
	_counter++;
	delay(1);
}


/* static */ void SynthLedStrips::ProcessMidi()
{
	if (midiB.read())
	{
		midi::MidiType midiType = midiB.getType();
		midi::DataByte dataByte1 = midiB.getData1();
		midi::DataByte dataByte2 = midiB.getData2();

		ProcessMidiEvents(midiType, dataByte1, dataByte2);
	}

	if (midiC.read())
	{
		midi::MidiType midiType = midiC.getType();
		midi::DataByte dataByte1 = midiC.getData1();
		midi::DataByte dataByte2 = midiC.getData2();

		ProcessMidiEvents(midiType, dataByte1, dataByte2);
	}

	if (midiD.read())
	{
		midi::MidiType midiType = midiD.getType();
		midi::DataByte dataByte1 = midiD.getData1();
		midi::DataByte dataByte2 = midiD.getData2();

		ProcessMidiEvents(midiType, dataByte1, dataByte2);
	}
}


/* static */ void SynthLedStrips::ProcessMidiEvents(midi::MidiType midiType, midi::DataByte dataByte1, midi::DataByte dataByte2)
{
	uint8_t midiChannel = (((uint8_t) midiType & 0x0F) == 0) ? 0 : 1;
	MidiKeyboard& midiKeyboard = _midiKeyboards[midiChannel];

	switch (midiType)
	{
	case midi::MidiType::NoteOn:
		midiKeyboard.ProcessMidiNoteOn(dataByte1, dataByte2);
		break;

	case midi::MidiType::NoteOff:
		midiKeyboard.ProcessMidiNoteOff(dataByte1, dataByte2);
		break;

	default:
		exit(0);
	}
}


/* static void */

/* static */ void SynthLedStrips::ProcessMidiKeyboards()
{
	for (uint8_t midiKeyboard = 0; midiKeyboard < NR_OF_MIDI_KEYBOARDS; midiKeyboard++)
	{
		_midiKeyboards[midiKeyboard].Process(_counter);
	}
}


/* static */ void SynthLedStrips::ProcessLedStrips()
{
	for (int ledStrip = 0; ledStrip < NR_OF_LED_STRIPS; ledStrip++)
	{
		_ledStrips[ledStrip].Process(_counter);
	}
}


/* static */ void SynthLedStrips::ClearNewFlags()
{
	for (uint8_t midiKeyboard = 0; midiKeyboard < NR_OF_MIDI_KEYBOARDS; midiKeyboard++)
	{
		_midiKeyboards[midiKeyboard].ClearNewFlags();
	}
}