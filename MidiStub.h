#pragma once

#include "ClassNames.h"
#include HEADER_FILE(SERIAL_CLASS)


#define MIDI_CREATE_INSTANCE(serialPort, serialType, name);


class Midi
{
public:
	Midi();
	~Midi();

	void begin();
};



extern Midi midiA;
extern Midi midiB;
extern Midi midiC;
extern Midi midiD;