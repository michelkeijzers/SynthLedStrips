#pragma once

#include "SynthLedStripsTypes.h"

#include "ClassNames.h"
#include HEADER_FILE(FAST_LED_CLASS)
#include HEADER_FILE(MIDI_CLASS)

#include "LedColor.h"
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

    void Initialize(MidiKeyboard* midiKeyboard, uint8_t dataPin, uint8_t nrOfLeds, struct FastLedCRGB* data);
	
	void SetPattern(EPattern pattern,
		uint8_t parameter_0 = 0, uint8_t parameter_1 = 0, uint8_t parameter_2 = 0, uint8_t parameter_3 = 0, uint8_t parameter_4 = 0, 
		uint8_t parameter_5 = 0, uint8_t parameter_6 = 0, uint8_t parameter_7 = 0, uint8_t parameter_8 = 0, uint8_t parameter_9 = 0);

	void Process(uint32_t counter);

private:
	void StartPattern();

	void ProcessKnightRider(uint32_t counter);
	void ProcessMidiNoteOnOff(uint32_t counter);

	void SetAllLeds(LedColor::EColor color, uint8_t step);
	void SetAllLeds(uint32_t color);
	void SetAllLeds(uint8_t red, uint8_t green, uint8_t blue);

	void SetLed(struct FastLedCRGB* led, LedColor::EColor color, uint8_t step);
	void SetLed(struct FastLedCRGB* led, uint32_t color);
	void SetLed(struct FastLedCRGB* led, uint8_t red, uint8_t green, uint8_t blue);

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

