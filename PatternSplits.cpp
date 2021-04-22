#include "PatternSplits.h"
#include "LedStrip.h"
#include "LedColor.h"



// Left to right
//TODO
uint8_t NOTE_INDEX_OF_61_KBD_2_LED[] = 
{
	// Note number:  36   37   38   39   40   41   42   43   44   45   46   47
	// Key           C1  C#1   D1  D#1   E1   F1  F#1   G1  G#1   A1  A#1   B1
	                  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,
	// Note number:  48   49   50   51   52   53   54   55   56   57   58   59
	// Key           C2  C#2   D2  D#2   E2   F2  F#2   G2  G#2   A2  A#2   B2
					 15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,
	// Note number:  60   61   62   63   64   65   66   67   68   69   70   71
	// Key           C3  C#3   D3  D#3   E3   F3  F#3   G3  G#3   A3  A#3   B3
					 30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,
	// Note number:  72   73   74   75   76   77   78   79   80   81   82   83
	// Key           C4  C#4   D4  D#4   E4   F4  F#4   G4  G#4   A4  A#4   B4
					 45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,
	// Note number:  84   85   86   87   88   89   90   91   92   93   94   95
	// Key           C5  C#5   D5  D#5   E5   F5  F#5   G5  G#5   A5  A#5   B5
					 60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,
	// Note number:  36
	// Key           C6
					 75
};


uint8_t NOTE_INDEX_OF_88_KBD_2_LED[] = 
{
	// Note number:                                               21   22   23
	// Key                                                       A-1 A#-1  B-1
	                                                               0,   1,   2,
	// Note number:  24   25   26   27   28   29   30   31   32   33   34   35
	// Key           C0  C#0   D0  D#0   E0   F0  F#0   G0  G#0   A0  A#0   B0
					 15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,
	// Note number:  36   37   38   39   40   41   42   43   44   45   46   47
	// Key           C1  C#1   D1  D#1   E1   F1  F#1   G1  G#1   A1  A#1   B1
					 30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,
	// Note number:  48   49   50   51   52   53   54   55   56   57   58   59
	// Key           C2  C#2   D2  D#2   E2   F2  F#2   G2  G#2   A2  A#2   B2
					 45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,
	// Note number:  60   61   62   63   64   65   66   67   68   69   70   71
	// Key           C3  C#3   D3  D#3   E3   F3  F#3   G3  G#3   A3  A#3   B3
					 60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,
	// Note number:  72   73   74   75   76   77   78   79   80   81   82   83
	// Key           C4  C#4   D4  D#4   E4   F4  F#4   G4  G#4   A4  A#4   B4
					 75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,
	// Note number:  84   85   86   87   88   89   90   91   92   93   94   95
	// Key           C5  C#5   D5  D#5   E5   F5  F#5   G5  G#5   A5  A#5   B5
					 90,  91,  92,  93,  94,  95,  96,  97,  98,  99, 100, 101,
	// Note number:  96   97   98   99  100  101  102  103  104  105  106  107
	// Key           C6  C#6   D6  D#6   E6   F6  F#6   G6  G#6   A6  A#6   B6
					105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
	// Note number: 108
	// Key           C7
	                120
};
PatternSplits::PatternSplits()
:
	_colors{},
	_notes{},
	_nrOfNotesSet(0)
{
}


void PatternSplits::AddColorAndNote(LedColor::EColor color, uint8_t note)
{
	_colors[_nrOfNotesSet] = (uint8_t) color;
	_notes[_nrOfNotesSet] = note;
	_nrOfNotesSet++;
}


/* override */ void PatternSplits::Start()
{
	_ledStrip->SetAllLeds(LedColor::EColor::BLACK, 0);

	uint8_t currentLed = 0;
	for (uint8_t noteIndex = 0; noteIndex < _nrOfNotesSet; noteIndex++)
	{
		currentLed = Fill(currentLed, _notes[noteIndex], _colors[noteIndex]);
	}

	Fill(currentLed, 127, _colors[_nrOfNotesSet]);
}


uint8_t PatternSplits::Fill(uint8_t currentLed, uint8_t noteIndex, uint8_t color)
{
	uint8_t lastLed = 0;
	if (noteIndex < _midiKeyboard->GetKeyOffset())
	{
		lastLed = 0;
	}
	else if (noteIndex == 255)
	{
		lastLed = _ledStrip->GetNrOfLeds();
	}
	else
	{
		lastLed = (_midiKeyboard->GetNrOfKeys() == 61 ? NOTE_INDEX_OF_61_KBD_2_LED : NOTE_INDEX_OF_88_KBD_2_LED)
			[noteIndex - _midiKeyboard->GetKeyOffset()];
	}

	for (uint8_t ledIndex = currentLed; ledIndex < lastLed; ledIndex++)
	{
		_ledStrip->SetLed(_ledStrip->GetLed(ledIndex), (LedColor::EColor) color, 0); // TODO: last param 0: step
	}

	return lastLed;
}


/* override */ void PatternSplits::Process()
{
	// No action needed (unless to implement special colors like galaxy, fire, random
}
