#include "PatternSplits.h"
#include "LedStrip.h"
#include "LedColor.h"


uint8_t NOTE_INDEX2LED[] = 
{
	4, 5, 6
};


PatternSplits::PatternSplits()
:
	_colors{},
	_notes{},
	_nrOfNotesSet(0)
{
}


void PatternSplits::SetColorAndNote(uint8_t index, LedColor::EColor color, uint8_t note)
{
	_colors[index] = (uint8_t) color;
	_notes[index] = note;
	_nrOfNotesSet++;
}


/* override */ void PatternSplits::Start()
{
	_ledStrip->SetAllLeds(LedColor::EColor::Black, 0);

	uint8_t currentLed = 0;
	for (uint8_t noteIndex = 0; noteIndex < _nrOfNotesSet; noteIndex++)
	{
		currentLed = Fill(currentLed, _notes[noteIndex], _colors[noteIndex]);
	}

	Fill(currentLed, 127, _colors[_nrOfNotesSet]);
}


uint8_t PatternSplits::Fill(uint8_t currentLed, uint8_t noteIndex, uint8_t color)
{
	for (uint8_t ledIndex = currentLed; ledIndex < NOTE_INDEX2LED[noteIndex - 1]; ledIndex++)
	{
		_ledStrip->SetLed(_ledStrip->GetLed(ledIndex), color);
	}

	return currentLed;
}


/* override */ void PatternSplits::Process()
{
	// No action needed (unless to implement special colors like galaxy, fire, random
}
