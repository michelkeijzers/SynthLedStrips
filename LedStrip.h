#pragma once

#include "SynthLedStripsTypes.h"

#include "ClassNames.h"
#include HEADER_FILE(FAST_LED_CLASS)
#include HEADER_FILE(MIDI_CLASS)

#include "MidiKeyboard.h"


class LedStrip
{
public:

	enum class EPattern 
	{
		Off = 0, 
		SolidColor = 1, 
		FadeStrobe = 2, 
		Rainbow = 3, 
		KnightRider = 50, 
		MidiNoteOnOff 
	};
	
	LedStrip();

    ~LedStrip();

    void Set(MidiKeyboard*& keyboard, uint8_t dataPin, uint8_t nrOfLeds, struct FastLedCRGB* data, EPattern pattern,
		uint8_t parameter_0 = 0, uint8_t parameter_1 = 0, uint8_t parameter_2 = 0, uint8_t parameter_3 = 0, uint8_t parameter_4 = 0, 
		uint8_t parameter_5 = 0, uint8_t parameter_6 = 0, uint8_t parameter_7 = 0, uint8_t parameter_8 = 0, uint8_t parameter_9 = 0);

	void Process(uint32_t counter);

private:

	void ProcessStart(uint32_t counter);
	void ProcessLeds(uint32_t counter);

	MidiKeyboard* _midiKeyboard;

	uint8_t _dataPin;

	uint8_t _nrOfLeds;

	struct FastLedCRGB* _data;

	EPattern _pattern;


	// LED Strips

	uint8_t _value_0 = 0;
	uint8_t _value_1 = 1;

	uint8_t _parameter_0 = 0;
	uint8_t _parameter_1 = 0;
	uint8_t _parameter_2 = 0;
	uint8_t _parameter_3 = 0;
	uint8_t _parameter_4 = 0;
	uint8_t _parameter_5 = 0;
	uint8_t _parameter_6 = 0;
	uint8_t _parameter_7 = 0;
	uint8_t _parameter_8 = 0;
	uint8_t _parameter_9 = 0;
};

