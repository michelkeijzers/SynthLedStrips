#pragma once

#include "LedColor.h"
#include "SynthLedStripsTypes.h"

class MidiKeyboard;
class LedStrip;

class Pattern
{
public:
	Pattern();

	virtual void Initialize(MidiKeyboard* midiKeyboard, LedStrip* ledStrip);

	virtual void Start() = 0;

	virtual void Process() = 0;

protected:
	MidiKeyboard* _midiKeyboard;

	LedStrip* _ledStrip;

	uint32_t _timeLastProcessed;
};
