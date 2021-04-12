#include <cstdint>
#include <iostream>

#include "Configuration.h"
#include "LedStrips.h"
#include "Patterns.h"

enum EPatternType: uint8_t
{
	EOff,
	EKnightRider,
	EMidiNoteOnOff
};

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
{
}


void Configuration::OpenFile()
{
	SPIFFS.begin(true);
	_file = SPIFFS.open("config.bin", "r");
}


void Configuration::SetPatterns(Patterns* patterns, uint8_t configurationIndex)
{
	// First pattern
	if (fseek(_file, 2 * configurationIndex, SEEK_SET) != 0)
	{
		throw 20;
	}

	uint16_t patternOffset;
	if (fread(&patternOffset, 2, 1, _file) != 2)
	{
		throw 21;
	}

	if (fseek_file, _patternOffset)



}


void Configuration::SetSplits(LedStrips* ledStrips, uint8_t configurationIndex)
{
	/*TODO*/
}
