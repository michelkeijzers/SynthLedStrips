#pragma once

#include <queue>

#include "ClassNames.h"
#include HEADER_FILE(SERIAL_CLASS)

#include "SynthLedStripsTypes.h"


#define MIDI_CREATE_INSTANCE(serialPort, serialType, name);


class midi
{
public:
    typedef uint8_t DataByte;

    enum class MidiType 
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
};


class Midi
{
public:
	Midi();
	~Midi();

	void begin();

    bool read();
    midi::MidiType getType();
    midi::DataByte getData1();
    midi::DataByte getData2();

    void AddToQueue(midi::MidiType type, midi::DataByte dataByte1);
    void AddToQueue(midi::MidiType type, midi::DataByte dataByte1, midi::DataByte dataByte2);

    static uint8_t GetNrOfDataBytes(midi::MidiType midiType);

private:
    void Read1DataByte();
    void Read2DataBytes();

    std::queue<uint8_t> _queue;

    midi::MidiType _midiType;
    uint8_t _midiChannel;
    midi::DataByte _data1;
    midi::DataByte _data2;
};


extern Midi midiA;
extern Midi midiB;
extern Midi midiC;
extern Midi midiD;
