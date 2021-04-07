#pragma once

#include <stdlib.h>

#include "MidiKeyboard.h"

constexpr auto NR_OF_MIDI_KEYBOARDS = 2;
constexpr auto NR_OF_KEYBOARD_1_KEYS = 61;
constexpr auto NR_OF_KEYBOARD_2_KEYS = 88;

class MidiKeyboards
{
public:
	MidiKeyboards();

	void Initialize();

	MidiKeyboard& GetMidiKeyboard(uint8_t index);

	void Process();

	void ClearNewFlags();

private:
	static MidiKeyboard _midiKeyboards[NR_OF_MIDI_KEYBOARDS];
};
