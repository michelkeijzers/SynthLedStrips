#include "AssertUtils.h"
#include "Configuration.h"
#include "MidiProcessor.h"
#include "MidiKeyboards.h"
#include "SynthLedStrips.h"


MidiProcessor::MidiProcessor()
{
}


void MidiProcessor::Process(Configuration* configuration, MidiKeyboards* midiKeyboards, LedStrips* ledStrips, Patterns& patterns,
	midi::MidiType midiType, uint8_t midiChannel, midi::DataByte dataByte1, midi::DataByte dataByte2)
{
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


void MidiProcessor::ProcessControlChange(Configuration* configuration, MidiKeyboards* midiKeyboards, LedStrips* ledStrips, Patterns& patterns,
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

	case 16: // MIDI Channel 16
	{
		if (dataByte1 == (uint8_t) midi::MidiControlChangeNumber::BankSelect) // MSB
		{
			configuration->SetPatterns(&(midiKeyboards->GetMidiKeyboard(0)), &(ledStrips->GetLedStrip(0)), &(ledStrips->GetLedStrip(1)), 
				patterns, dataByte2);
		}
		else if (dataByte1 == (uint8_t) midi::MidiControlChangeNumber::BankSelect + 32) // LSB
		{
			configuration->SetPatterns(&(midiKeyboards->GetMidiKeyboard(1)), &(ledStrips->GetLedStrip(2)), &(ledStrips->GetLedStrip(3)),
				patterns, dataByte2 + 128);
		}
		break;
	}

	default:
		// Ignore others
		break;
	}
}