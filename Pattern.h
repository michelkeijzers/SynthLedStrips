#pragma once

#include "LedColor.h"
#include "SynthLedStripsTypes.h"


class MidiKeyboard;
class LedStrip;


class Pattern
{
public:
	Pattern();

	~Pattern();

	void Initialize(MidiKeyboard* midiKeyboard, LedStrip* ledStrip);

	virtual void Start() = 0;

	virtual void Process(uint32_t counter) = 0;

protected:
	MidiKeyboard* _midiKeyboard;

	LedStrip* _ledStrip;
};
