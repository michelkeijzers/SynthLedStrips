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
#include "SynthLedStripsTypes.h"
#include "MidiKeyboards.h"
#include "Patterns.h"
#include "MidiKeyboards.h"

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(MIDI_CLASS)
#include HEADER_FILE(SERIAL_CLASS)
#include HEADER_FILE(FAST_LED_CLASS)
#include "Patterns.h"
#include "PatternOff.h"
#include "PatternKnightRider.h"
#include "PatternMidiNoteOnOff.h"


#define USE_SERIAL

/* static */ LedStrips SynthLedStrips::_ledStrips;
/* static */ Patterns SynthLedStrips::_patterns;
/* static */ MidiKeyboards SynthLedStrips::_midiKeyboards;

/* static */ uint32_t SynthLedStrips::_counter = 0;

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
	pattern_0->SetBackgroundColor(LedColor::EColor::Galaxy);
	pattern_0->SetBackgroundColorSpeed(Speed::ESpeed::_10s);
	pattern_0->SetForegroundColor(LedColor::EColor::White);
	pattern_0->SetForegroundColorSpeed(Speed::ESpeed::_4s);
	pattern_0->SetFadeTimeNoteOn(Time::ETime::_10s);
	pattern_0->SetFadeTimeNoteOff(Time::ETime::_20s);
	pattern_0->SetNoteOnVelocityIntensity(255);
	_patterns.SetPattern(0, pattern_0, &_midiKeyboards.GetMidiKeyboard(0), &_ledStrips.GetLedStrip(0));

	PatternOff* pattern_1 = new (_patterns.GetPatternData(1)) PatternOff();
	_patterns.SetPattern(1, pattern_1, &_midiKeyboards.GetMidiKeyboard(0), &_ledStrips.GetLedStrip(1));

	PatternKnightRider* pattern_2 = new (_patterns.GetPatternData(2)) PatternKnightRider();
	pattern_2->SetBackgroundColor(LedColor::EColor::Black);
	pattern_2->SetBackgroundColorSpeed(Speed::ESpeed::_10s);
	pattern_2->SetForegroundColor(LedColor::EColor::Red);
	pattern_2->SetForegroundColorSpeed(Speed::ESpeed::_4s);
	pattern_2->SetDirection(true);
	pattern_2->SetLedSpeed(Speed::ESpeed::_1s);
	pattern_2->SetLedWidth(10);
	_patterns.SetPattern(2, pattern_2, &_midiKeyboards.GetMidiKeyboard(1), &_ledStrips.GetLedStrip(2));

	PatternKnightRider* pattern_3 = new (_patterns.GetPatternData(3)) PatternKnightRider();
	pattern_3->SetBackgroundColor(LedColor::EColor::Black);
	pattern_3->SetBackgroundColorSpeed(Speed::ESpeed::_10s);
	pattern_3->SetForegroundColor(LedColor::EColor::Red);
	pattern_3->SetForegroundColorSpeed(Speed::ESpeed::_4s);
	pattern_3->SetDirection(true);
	pattern_3->SetLedSpeed(Speed::ESpeed::_1s);
	pattern_3->SetLedWidth(10);
	_patterns.SetPattern(3, pattern_3, &_midiKeyboards.GetMidiKeyboard(1), &_ledStrips.GetLedStrip(3));
}


/* static */ void SynthLedStrips::Loop()
{
	ProcessMidi();
	_midiKeyboards.Process(_counter);
	_patterns.Process(_counter);
	_ledStrips.Process(_counter);
	_midiKeyboards.ClearNewFlags();
	FastLED.show();
	_counter++;
	delay(10);
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
	MidiKeyboard& midiKeyboard = _midiKeyboards.GetMidiKeyboard(midiChannel);

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
