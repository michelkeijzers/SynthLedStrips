#pragma once

#include "SynthLedStripsTypes.h"

#include "ClassNames.h"
#include HEADER_FILE(FAST_LED_CLASS)
#include HEADER_FILE(MIDI_CLASS)

#include "LedColor.h"
#include "MidiKeyboard.h"
#include "Pattern.h"

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
	
	uint8_t GetNrOfLeds();

	void SetPattern(Pattern* pattern);

	void Process(uint32_t counter);

	struct FastLedCRGB* GetLed(uint8_t ledIndex);

public:
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

	Pattern* _pattern;
};

