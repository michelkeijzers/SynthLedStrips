#include "Pattern.h"

#include <stdlib.h>

#include "MidiKeyboard.h"
#include "LedStrip.h"


Pattern::Pattern()
:
	_ledStrip(NULL),
	_midiKeyboard(NULL)
{
}


Pattern::~Pattern()
{
}


void Pattern::Initialize(MidiKeyboard* midiKeyboard, LedStrip* ledStrip)
{
	_midiKeyboard = midiKeyboard;
	_ledStrip = ledStrip;
}
