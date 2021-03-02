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
#endif

#include "SynthLedStrips.h"
#include "SynthLedStripsTypes.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(MIDI_CLASS)
#include HEADER_FILE(SERIAL_CLASS)
#include HEADER_FILE(FAST_LED_CLASS)

#include "LedStrip.h"

#include HEADER_FILE(MIDI_CLASS)

// LED STRIPS
const uint8_t NR_OF_LEDS       = 144;
const uint8_t NR_OF_LED_STRIPS =   4;

const uint8_t DATA_PINS[] = { 2, 3, 4, 5 };

FastLedCRGB _leds[NR_OF_LED_STRIPS][NR_OF_LEDS];

LedStrip _ledStrips[NR_OF_LED_STRIPS];


void ProcessMidi();


// Application
#include "SerialPrint.h"

#include "MidiKeyboard.h"

// DEBUGGING
#define USE_SERIAL

// MIDI
#ifndef USE_SERIAL
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiA);
#endif

MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, midiB);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, midiC);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, midiD);

#define NR_OF_KEYBOARDS 2

MidiKeyboard* _keyboards[NR_OF_KEYBOARDS];


uint32_t _counter;

// Application

SynthLedStrips::SynthLedStrips()
{
}


SynthLedStrips::~SynthLedStrips()
{
}


/* static */ void SynthLedStrips::Setup()
{
	// Generic GPIO.
	pinMode(LED_BUILTIN, OUTPUT);

	// Serial/MIDI.
#ifdef USE_SERIAL
	Serial.begin(115200);
	Serial.println("LED Strip Synth 0.1");
#else
	midiA.begin();
#endif

	midiB.begin();
	midiC.begin();
	midiD.begin();


	_keyboards[0] = new MidiKeyboard(1, 61);
	_keyboards[1] = new MidiKeyboard(2, 88);

	// LED STRIPS
	FastLED.addLeds<WS2813, 3, RGB>(_leds[0], NR_OF_LEDS);
	_ledStrips[0].Set(DATA_PINS[0], NR_OF_LEDS, _leds[0], LedStrip::EPattern::MidiNoteOnOff);
	FastLED.addLeds<WS2813, 4, RGB>(_leds[1], NR_OF_LEDS);
	_ledStrips[1].Set(DATA_PINS[1], NR_OF_LEDS, _leds[1], LedStrip::EPattern::KnightRiderSpread, 255, 0, 0, 10, 1);
	FastLED.addLeds<WS2813, 5, RGB>(_leds[2], NR_OF_LEDS);
	_ledStrips[2].Set(DATA_PINS[2], NR_OF_LEDS, _leds[2], LedStrip::EPattern::KnightRider, 255, 0, 0, 10);
	FastLED.addLeds<WS2813, 6, RGB>(_leds[3], NR_OF_LEDS);
	_ledStrips[3].Set(DATA_PINS[3], NR_OF_LEDS, _leds[3], LedStrip::EPattern::KnightRiderSpread, 255, 255, 255, 20, 10);

	FastLED.setBrightness(84);

	_counter = 0;
}


/* static */ void SynthLedStrips::Loop()
{
	if (midiB.read())
	{
		ProcessMidi();
	}
	

	for (int ledStrip = 0; ledStrip < NR_OF_LED_STRIPS; ledStrip++)
	{
		_ledStrips[ledStrip].Process(_counter);
	}
	
	FastLED.show();

	_counter++;
	delay(1);
}


void ProcessMidi()
{
	midi::MidiType midiType = midiB.getType();
	uint8_t midiChannel = midiType & 0x0F;
	MidiKeyboard* keyboard = _keyboards[midiChannel];
	midi::DataByte dataByte1 = midiB.getData1();
	midi::DataByte dataByte2 = midiB.getData2();

	for (int ledStrip = 0; ledStrip < NR_OF_LED_STRIPS; ledStrip++)
	{
		switch (midiType)
		{
		case midi::MidiType::NoteOn:
			keyboard->ProcessMidiNoteOn(midiType & 0x0F, dataByte1, dataByte2);
			break;

		case midi::MidiType::NoteOff:
			keyboard->ProcessMidiNoteOff(midiType & 0x0F, dataByte1, dataByte2);
			break;

		default:
			exit(0);
		}
	}
}


/*
1.5 seconds for 120 (60 inc, 60 dec) loops with sleep 10

1500 ms / 120 loops = 12.5 ms
sleep is 10 ms
overhead: 2.5 ms

1300 ms / 120 = 10.83 ms
sleep is 10 ms
overhead: 0.83 ms

*/
