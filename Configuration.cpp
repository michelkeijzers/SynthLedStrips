#include <cstdint>
#include <iostream>

#include "Configuration.h"
#include "LedStrips.h"
#include "Patterns.h"
#include "PatternMidiNoteOnOff.h"
#include "PatternKnightRider.h"
#include "PatternOff.h"
#include "PatternSplits.h"
#include "LedColor.h"
#include "MidiKeyboards.h"
#include "LedStrips.h"


const uint16_t PATTERN_OFFSET_TABLE_START = 0;
const uint16_t SPLITS_OFFSET_TABLE_START = 256;
const uint16_t DATA_START = 512; // First 512 bytes for 2 bytes offset for 128 patterns, 2 bytes offset for 128 splits

const uint8_t OFF__PARAMETER_LENGTH                         = 0;

const uint8_t KNIGHT_RIDER__BACKGROUND_COLOR				= 0;
const uint8_t KNIGHT_RIDER__BACKGROUND_COLOR_TIME			= KNIGHT_RIDER__BACKGROUND_COLOR				+ 1;
const uint8_t KNIGHT_RIDER__FOREGROUND_COLOR				= KNIGHT_RIDER__BACKGROUND_COLOR_TIME			+ 4;
const uint8_t KNIGHT_RIDER__FOREGROUND_COLOR_TIME			= KNIGHT_RIDER__FOREGROUND_COLOR				+ 1;
const uint8_t KNIGHT_RIDER__DIRECTION						= KNIGHT_RIDER__FOREGROUND_COLOR_TIME			+ 4;
const uint8_t KNIGHT_RIDER__PARAMETER_LENGTH				= KNIGHT_RIDER__DIRECTION						+ 1;

const uint8_t MIDI_NOTE_ON_OFF__BACKGROUND_COLOR			= 0;
const uint8_t MIDI_NOTE_ON_OFF__BACKGROUND_COLOR_TIME		= MIDI_NOTE_ON_OFF__BACKGROUND_COLOR			+ 1;
const uint8_t MIDI_NOTE_ON_OFF__FOREGROUND_COLOR			= MIDI_NOTE_ON_OFF__BACKGROUND_COLOR_TIME		+ 4;
const uint8_t MIDI_NOTE_ON_OFF__FOREGROUND_COLOR_TIME		= MIDI_NOTE_ON_OFF__FOREGROUND_COLOR			+ 1;
const uint8_t MIDI_NOTE_ON_OFF__FADE_TIME_NOTE_ON			= MIDI_NOTE_ON_OFF__FOREGROUND_COLOR_TIME		+ 4;
const uint8_t MIDI_NOTE_ON_OFF__FADE_TIME_NOTE_OFF			= MIDI_NOTE_ON_OFF__FADE_TIME_NOTE_ON			+ 4;
const uint8_t MIDI_NOTE_ON_OFF__MOVE_RIGHT_TIME				= MIDI_NOTE_ON_OFF__FADE_TIME_NOTE_OFF			+ 4;
const uint8_t MIDI_NOTE_ON_OFF__MOVE_TIME_LEFT				= MIDI_NOTE_ON_OFF__MOVE_RIGHT_TIME				+ 4;
const uint8_t MIDI_NOTE_ON_OFF__NOTE_ON_VELOCITY_INTENSITY	= MIDI_NOTE_ON_OFF__MOVE_TIME_LEFT				+ 4;
const uint8_t MIDI_NOTE_ON_OFF__PARAMETER_LENGTH			= MIDI_NOTE_ON_OFF__NOTE_ON_VELOCITY_INTENSITY	+ 1;


Configuration::Configuration()
	: _file(nullptr)
{
}


void Configuration::OpenFile()
{
	SPIFFS.begin(true);
	_file = SPIFFS.open("output-config.cfg", "r");
}


void Configuration::SetPatterns(MidiKeyboards* midiKeyboards, LedStrips* ledStrips, Patterns& patterns, uint8_t configurationIndex)
{
	uint16_t fileOffset = configurationIndex * 2;
	fileOffset = ReadNext2Bytes(&fileOffset);
    EPatternType patternType = (EPatternType) (ReadNextByte(&fileOffset));
	if (configurationIndex < 128)
	{
		SetPattern(&midiKeyboards->GetMidiKeyboard(0), &ledStrips->GetLedStrip(0), patterns, 0, &fileOffset, patternType);
	}
	else
	{
		SetPattern(&midiKeyboards->GetMidiKeyboard(0), &ledStrips->GetLedStrip(1), patterns, 1, &fileOffset, patternType);
	}

	patternType = (EPatternType) (ReadNextByte(&fileOffset));
	if (configurationIndex < 128)
	{
		SetPattern(&midiKeyboards->GetMidiKeyboard(1), &ledStrips->GetLedStrip(2), patterns, 2, &fileOffset, patternType);
	}
	else
	{
		SetPattern(&midiKeyboards->GetMidiKeyboard(1), &ledStrips->GetLedStrip(3), patterns, 3, &fileOffset, patternType);
	}

	ledStrips->On();
}


void Configuration::SetPattern(
	MidiKeyboard* midiKeyboard, LedStrip* ledStrip, Patterns& patterns, uint8_t patternIndex, uint16_t* fileOffset, EPatternType patternType)
{
	Pattern* pattern = nullptr;

	switch (patternType)
	{
	case EPatternType::Off:
	{
		pattern = new (patterns.GetPatternData(patternIndex)) PatternMidiNoteOnOff();
		pattern->Initialize(midiKeyboard, ledStrip);
		break;
	}

	case EPatternType::KnightRider:
		pattern = new (patterns.GetPatternData(patternIndex)) PatternKnightRider();
		pattern->Initialize(midiKeyboard, ledStrip);
		ReadKnightRiderProperties((PatternKnightRider*) pattern, fileOffset);
		break;

	case EPatternType::MidiNoteOnOff:
		pattern = new (patterns.GetPatternData(patternIndex)) PatternMidiNoteOnOff();
		pattern->Initialize(midiKeyboard, ledStrip);
		ReadMidiNoteOnOffProperties((PatternMidiNoteOnOff*) pattern, fileOffset);
		break;

	case EPatternType::Splits:
		pattern = new (patterns.GetPatternData(patternIndex)) PatternSplits();
		pattern->Initialize(midiKeyboard, ledStrip);
		ReadSplitsProperties((PatternSplits*) pattern, fileOffset);
		break;

	default:
		throw 24;
	}

	patterns.SetPattern(patternIndex, pattern, midiKeyboard, ledStrip);
	pattern->Start();
}


void Configuration::ReadKnightRiderProperties(PatternKnightRider* pattern, uint16_t* fileOffset)
{
	pattern->SetBackgroundColor((LedColor::EColor) ReadNextByte(fileOffset));
	pattern->SetBackgroundColorTime(ReadNext2Bytes(fileOffset));
	pattern->SetForegroundColor((LedColor::EColor) ReadNextByte(fileOffset));
	pattern->SetForegroundColorTime(ReadNext2Bytes(fileOffset));
	pattern->SetLedTime(ReadNext2Bytes(fileOffset));
	pattern->SetLedTime(ReadNext2Bytes(fileOffset)); // TODO: left/right time
	pattern->SetLedWidth(ReadNextByte(fileOffset));

}


void Configuration::ReadMidiNoteOnOffProperties(PatternMidiNoteOnOff* pattern, uint16_t* fileOffset)
{
	pattern->SetBackgroundColor((LedColor::EColor) ReadNextByte(fileOffset));
	pattern->SetBackgroundColorTime(ReadNext2Bytes(fileOffset));
	pattern->SetForegroundColor((LedColor::EColor) ReadNextByte(fileOffset));
	pattern->SetForegroundColorTime(ReadNext2Bytes(fileOffset));
	pattern->SetMoveLeftTime(ReadNext2Bytes(fileOffset));
	pattern->SetMoveRightTime(ReadNext2Bytes(fileOffset));
	pattern->SetFadeTimeNoteOn(ReadNext2Bytes(fileOffset));
	pattern->SetFadeTimeNoteOff(ReadNext2Bytes(fileOffset));
	pattern->SetNoteOnVelocityIntensity(ReadNextByte(fileOffset));
}


void Configuration::ReadSplitsProperties(PatternSplits* pattern, uint16_t* fileOffset)
{
	uint8_t note = 0;

	do
	{
		uint8_t color = ReadNextByte(fileOffset);
		note = ReadNextByte(fileOffset);
		pattern->AddColorAndNote((LedColor::EColor) color, note);
	} while (note != 255);
}


uint8_t Configuration::ReadNextByte(uint16_t* fileOffset)
{
	if (fseek(_file, *fileOffset, SEEK_SET) != 0)
	{
		throw 28;
	}

	uint8_t data;
	if (fread(&data, 1, 1, _file) != 1)
	{
		throw 29;
	}
	
	(*fileOffset)++;
	return data;
}


uint16_t Configuration::ReadNext2Bytes(uint16_t* fileOffset)
{
	if (fseek(_file, *fileOffset, SEEK_SET) != 0)
	{
		throw 28;
	}

	uint16_t data;
	if (fread(&data, 1, 2, _file) != 2)
	{
		throw 29;
	}

	*fileOffset = *fileOffset + 2;
	return (data >> 8) + (data << 8);
}

