#ifdef _WINDOWS

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

    enum class MidiType : uint8_t
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
        SystemExclusiveStart  = SystemExclusive,   
        TimeCodeQuarterFrame  = 0xF1,    
        SongPosition          = 0xF2,    
        SongSelect            = 0xF3,    
        Undefined_F4          = 0xF4,
        Undefined_F5          = 0xF5,
        TuneRequest           = 0xF6,    
        SystemExclusiveEnd    = 0xF7,    
        Clock                 = 0xF8,    
        Undefined_F9          = 0xF9,
        Tick                  = Undefined_F9, 
        Start                 = 0xFA,    
        Continue              = 0xFB,    
        Stop                  = 0xFC,    
        Undefined_FD          = 0xFD,
        ActiveSensing         = 0xFE,    
        SystemReset           = 0xFF,      
    };

    enum class MidiControlChangeNumber : uint8_t
    {
        // High resolution Continuous Controllers MSB (+32 for LSB) ----------------
        BankSelect                  = 0,
        ModulationWheel             = 1,
        BreathController            = 2,
        // CC3 undefined
        FootController              = 4,
        PortamentoTime              = 5,
        DataEntryMSB                = 6,
        ChannelVolume               = 7,
        Balance                     = 8,
        // CC9 undefined
        Pan                         = 10,
        ExpressionController        = 11,
        EffectControl1              = 12,
        EffectControl2              = 13,
        // CC14 undefined
        // CC15 undefined
        GeneralPurposeController1   = 16,
        GeneralPurposeController2   = 17,
        GeneralPurposeController3   = 18,
        GeneralPurposeController4   = 19,

        DataEntryLSB                = 38,

        // Switches ----------------------------------------------------------------
        Sustain                     = 64,
        Portamento                  = 65,
        Sostenuto                   = 66,
        SoftPedal                   = 67,
        Legato                      = 68,
        Hold                        = 69,

        // Low resolution continuous controllers -----------------------------------
        SoundController1            = 70,   
        SoundController2            = 71,   
        SoundController3            = 72,   
        SoundController4            = 73,   
        SoundController5            = 74,   
        SoundController6            = 75,   
        SoundController7            = 76,   
        SoundController8            = 77,   
        SoundController9            = 78,   
        SoundController10           = 79,   
        GeneralPurposeController5   = 80,
        GeneralPurposeController6   = 81,
        GeneralPurposeController7   = 82,
        GeneralPurposeController8   = 83,
        PortamentoControl           = 84,
        // CC85 to CC90 undefined
        Effects1                    = 91,   
        Effects2                    = 92,   
        Effects3                    = 93,   
        Effects4                    = 94,   
        Effects5                    = 95,   
        DataIncrement               = 96,
        DataDecrement               = 97,
        NRPNLSB                     = 98,   
        NRPNMSB                     = 99,   
        RPNLSB                      = 100,  
        RPNMSB                      = 101,  

        // Channel Mode messages ---------------------------------------------------
        AllSoundOff                 = 120,
        ResetAllControllers         = 121,
        LocalControl                = 122,
        AllNotesOff                 = 123,
        OmniModeOff                 = 124,
        OmniModeOn                  = 125,
        MonoModeOn                  = 126,
        PolyModeOn                  = 127
    };

    struct RPN
    {
        enum RegisteredParameterNumbers: uint16_t
        {
            PitchBendSensitivity    = 0x0000,
            ChannelFineTuning       = 0x0001,
            ChannelCoarseTuning     = 0x0002,
            SelectTuningProgram     = 0x0003,
            SelectTuningBank        = 0x0004,
            ModulationDepthRange    = 0x0005,
            NullFunction            = (0x7f << 7) + 0x7f,
        };
    };
};


class MidiInterface
{
public:
    MidiInterface();

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


extern MidiInterface midiB;
extern MidiInterface midiC;

#endif // WINDOWS
