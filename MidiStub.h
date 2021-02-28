#pragma once

#include "ClassNames.h"
#include HEADER_FILE(SERIAL_CLASS)

#include "SynthLedStripsTypes.h"


#define MIDI_CREATE_INSTANCE(serialPort, serialType, name);


typedef uint8_t DataByte;


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