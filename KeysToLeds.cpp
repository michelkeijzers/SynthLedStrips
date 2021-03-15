#include "KeysToLeds.h"

#include "MidiKeyboard.h"
#include "LedStrip.h"


KeysToLeds::KeysToLeds(MidiKeyboard& midiKeyboard, LedStrip& ledStrip)
	: _midiKeyboard(midiKeyboard),
	_ledStrip(ledStrip)
{
}


KeysToLeds::~KeysToLeds()
{
}


/// <summary>
/// Algorithm (see also Calculations in Google Sheets)
/// - If the new pressed keys are already assigned (to a led), return (no changes needed).
/// - 
/// 
/// </summary>
/// <param name="midiKeyboard"></param>
/// <param name="ledStrip"></param>
void KeysToLeds::Process()
{
	if (AreNewPressedKeysAssigned())
	{
		return;
	}
}


bool KeysToLeds::AreNewPressedKeysAssigned()
{
	for (uint8_t key = 0; key < _midiKeyboard.GetNrOfKeys(); key++)
	{
		if (_midiKeyboard.IsNew(key))
		{

		}
	}
	return true;
}