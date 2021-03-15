#pragma once

#include "LedStrip.h"

class MidiKeyboard;
class LedStrip;


class KeysToLeds
{
	KeysToLeds(MidiKeyboard& midiKeyboard, LedStrip& ledStrip);

	~KeysToLeds();

	void Process();

private:

	bool AreNewPressedKeysAssigned();

	MidiKeyboard& _midiKeyboard;

	LedStrip& _ledStrip;
};
