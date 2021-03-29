#include "Pattern.h"
#include <stdlib.h>
#include "MidiKeyboard.h"
#include "LedStrip.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)

Pattern::Pattern()
:
	_ledStrip(nullptr),
	_midiKeyboard(nullptr),
	_timeLastProcessed(millis())
{
}


/* virtual */ void Pattern::Initialize(MidiKeyboard* midiKeyboard, LedStrip* ledStrip)
{
	_midiKeyboard = midiKeyboard;
	_ledStrip = ledStrip;
}
