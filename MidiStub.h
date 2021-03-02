#pragma once

#include <queue>

#include "ClassNames.h"
#include HEADER_FILE(SERIAL_CLASS)

#include "SynthLedStripsTypes.h"


#define MIDI_CREATE_INSTANCE(serialPort, serialType, name);

enum MidiType 
{
    InvalidType           = 0x00,    
    NoteOff               = 0x80,    
    NoteOn                = 0x90,    
    AfterTouchPoly        = 0xA0,    
    ControlChange         = 0xB0,    
    ProgramChange         = 0xC0,    
    AfterTouchChannel     = 0xD0,    
    PitchBend             = 0xE0,    
    SystemExclusive       = 0xF0,    
    TimeCodeQuarterFrame  = 0xF1,    
    SongPosition          = 0xF2,    
    SongSelect            = 0xF3,    
    Undefined_F4          = 0xF4,
    Undefined_F5          = 0xF5,
    TuneRequest           = 0xF6,    
    SystemExclusiveEnd    = 0xF7,    
    Clock                 = 0xF8,    
    Tick                  = 0xF9,
    Start                 = 0xFA,    
    Continue              = 0xFB,    
    Stop                  = 0xFC,    
    Undefined_FD          = 0xFD,
    ActiveSensing         = 0xFE,    
    SystemReset           = 0xFF,    
};

typedef uint8_t DataByte;


class Midi
{
public:
	Midi();
	~Midi();

	void begin();

    bool read();
    MidiType getType();
    DataByte getData1();
    DataByte getData2();

    void AddToQueue(MidiType type, DataByte dataByte1);
    void AddToQueue(MidiType type, DataByte dataByte1, DataByte dataByte2);

    static uint8_t GetNrOfDataBytes(MidiType midiType);

private:
    void Read1DataByte();
    void Read2DataBytes();

    std::queue<uint8_t> _queue;

    MidiType _midiType;
    uint8_t _midiChannel;
    DataByte _data1;
    DataByte _data2;
};


extern Midi midiA;
extern Midi midiB;
extern Midi midiC;
extern Midi midiD;