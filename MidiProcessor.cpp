#include "AssertUtils.h"
#include "Configuration.h"
#include "MidiProcessor.h"
#include "MidiKeyboards.h"
#include "SynthLedStrips.h"


MidiProcessor::MidiProcessor()
{
}


void MidiProcessor::Process(Configuration* configuration, MidiKeyboards* midiKeyboards, LedStrips* ledStrips, Patterns* patterns,
	midi::MidiType midiType, midi::DataByte dataByte1, midi::DataByte dataByte2)
{
	uint8_t midiChannel = (((uint8_t)midiType & 0x0F) == 0) ? 0 : 1;

	switch (midiType)
	{
	case midi::MidiType::ControlChange:
		ProcessControlChange(configuration, midiKeyboards, ledStrips, patterns, midiChannel, dataByte1, dataByte2);
		break;

	case midi::MidiType::NoteOn:
		midiKeyboards->GetMidiKeyboard(midiChannel).ProcessMidiNoteOn(dataByte1, dataByte2);
		break;

	case midi::MidiType::NoteOff:
		midiKeyboards->GetMidiKeyboard(midiChannel).ProcessMidiNoteOff(dataByte1, dataByte2);
		break;

	default:
		AssertUtils::MyAssert(false);
	}
}


void MidiProcessor::ProcessControlChange(Configuration* configuration, MidiKeyboards* midiKeyboards, LedStrips* ledStrips, Patterns* patterns,
	uint8_t midiChannel, midi::DataByte dataByte1, midi::DataByte dataByte2)
{
	switch (midiChannel)
	{
	case 0: // MIDI Channel 1
		if (dataByte1 == (uint8_t)midi::MidiType::ControlChange)
		{
			ledStrips->Off();
		}
		break;

	case 15: // MIDI Channel 16
	{
		if (dataByte1 == (uint8_t) midi::MidiControlChangeNumber::BankSelect) // MSB
		{
			configuration->SetPatterns(patterns, dataByte2);
		}
		else if (dataByte1 == (uint8_t) midi::MidiControlChangeNumber::BankSelect + 32) // LSB
		{
			configuration->SetSplits(ledStrips, dataByte2);
		}
		break;
	}

	default:
		// Ignore others
		break;
	}
}