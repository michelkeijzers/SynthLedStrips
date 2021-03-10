#pragma once

#include "MidiKeyboard.h"
#include "LedStrip.h"

#define NR_OF_MIDI_KEYBOARDS 2

#define NR_OF_LEDS         144
#define NR_OF_LED_STRIPS     4


class SynthLedStrips
{
public:
	SynthLedStrips();
	~SynthLedStrips();

	static void Setup();
	static void Loop();

	static void ProcessMidi();
	static void ProcessMidiEvents(midi::MidiType midiType, midi::DataByte dataByte1, midi::DataByte dataBatye2);
	static void ProcessMidiKeyboards();
	static void ProcessLedStrips();
	static void ClearNewFlags();

private:
	static const uint8_t DATA_PINS[];

	static MidiKeyboard _midiKeyboards[NR_OF_MIDI_KEYBOARDS];

	static LedStrip _ledStrips[NR_OF_LED_STRIPS];

	static FastLedCRGB _leds[NR_OF_LED_STRIPS][NR_OF_LEDS];

	static uint32_t _counter;
};
