#include "Pattern.h"
#include <stdlib.h>
#include "MidiKeyboard.h"
#include "LedStrip.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)

Pattern::Pattern()
:
	_ledStrip(NULL),
	_midiKeyboard(NULL),
	_timeLastProcessed(millis())
{
}


Pattern::~Pattern()
{
}


/* virtual */ void Pattern::Initialize(MidiKeyboard* midiKeyboard, LedStrip* ledStrip)
{
	_midiKeyboard = midiKeyboard;
	_ledStrip = ledStrip;
}
