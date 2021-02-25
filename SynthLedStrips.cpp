// LedStripSynthShow.ino
//
//           
//             M E G A                 Cmd
//            Flash SRAM   SRAMnew     Data
// Maximum:  
// Current:  
//       %:      9    71         8
//
// Stack:
//
// Class          ::Method					   Parameters     Local Variables
// Total  

// Interrupt

#ifdef _WINDOWS
#include <windows.h>
#endif

#include "SynthLedStrips.h"
#include "SynthLedStripsTypes.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
//#include HEADER_FILE(DMX_SIMPLE_CLASS)
#include HEADER_FILE(SERIAL_CLASS)
#include HEADER_FILE(FAST_LED_CLASS)

// MIDI
#include HEADER_FILE(MIDI_CLASS)

// LED STRIPS
const uint8_t NR_OF_LEDS       = 60;
const uint8_t NR_OF_LED_STRIPS =  3;

const uint8_t DATA_PIN_1 = 3;
const uint8_t DATA_PIN_2 = 4;
const uint8_t DATA_PIN_3 = 5;

FastLedCRGB _leds[NR_OF_LED_STRIPS][NR_OF_LEDS];

// Application
#include "SerialPrint.h"

// DEBUGGING
#define USE_SERIAL

// MIDI
#ifndef USE_SERIAL
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiA);
#endif

MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, midiB);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, midiC);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, midiD);

// LED Strips

int _currentLed = 0;
enum class EDirection { Up, Down };
EDirection _direction = EDirection::Up;

enum class EPattern { Off, KnightRider, KnightRiderSpread, Strobo };
EPattern _pattern = EPattern::KnightRiderSpread;


int _parameter1 = 0;
int _parameter2 = 0;
int _parameter3 = 0;

// Application

SynthLedStrips::SynthLedStrips()
{
}


SynthLedStrips::~SynthLedStrips()
{
}


/* static */ void SynthLedStrips::Setup()
{
	// Generic GPIO.
	pinMode(LED_BUILTIN, OUTPUT);

	// Serial/MIDI.
#ifdef USE_SERIAL
	Serial.begin(115200);
	Serial.println("LED Strip Synth 0.1");
#else
	midiA.begin();
#endif

	midiB.begin();
	midiC.begin();
	midiD.begin();

	// LEDs
	// LED STRIPS
	FastLED.addLeds<WS2813, DATA_PIN_1, RGB>(_leds[0], NR_OF_LEDS);
	FastLED.addLeds<WS2813, DATA_PIN_2, RGB>(_leds[1], NR_OF_LEDS);
	FastLED.addLeds<WS2813, DATA_PIN_3, RGB>(_leds[2], NR_OF_LEDS);
	FastLED.setBrightness(84);

	// Program

	switch (_pattern)
	{
	case EPattern::Off:
		break;

	case EPattern::KnightRider:
		_parameter1 = 10; // Speed
		break;

	case EPattern::KnightRiderSpread:
		_parameter1 = 10; // Speed
		_parameter2 = 15; // Spread
		break;

	case EPattern::Strobo:
		_parameter1 = 500; // Speed
		
		break;

	default:
		exit(0);

		

	}
}


/* static */ void SynthLedStrips::Loop()
{
	//TODO IF MIDI COMMAND RECEIVED

	// LEDs
	if (_direction == EDirection::Up)
	{
		_currentLed++;
		if (_currentLed == NR_OF_LEDS - 1)
		{
			_direction = EDirection::Down;
		}
	}
	else
	{
		_currentLed--;
		if (_currentLed == 0)
		{
			_direction = EDirection::Up;
		}
	}


	for (int led = 0; led < NR_OF_LEDS; led++)
	{
		FastLedCRGB *rgb = &(_leds[0][led]);
		switch (_pattern)
		{
		case EPattern::Off:
			rgb->red = 0;
			rgb->green = 0;
			rgb->blue = 0;
			break;

		case EPattern::KnightRider:
			rgb->red = _currentLed == led ? 255 : 0;
			rgb->blue = 0;
			rgb->green = 0;
			break;

		case EPattern::KnightRiderSpread:
			
			rgb->red = max(0, _parameter2 - abs(led - _currentLed)) * (255 / _parameter2);
			rgb->blue = 0;
			rgb->green = 0;
			break;

		default:
			exit(0);
		}
		
		//int width = 15;
		//rgb->red = max(0, width - abs(led - _currentLed)) * (255/width);
		//rgb->green = _currentLed * 3 + led % 20 * 2; // 0; ((NR_OF_LEDS - led - 1) == _currentLed) ? 255 : 0;
		//rgb->blue = 0; //(led + _currentLed) % (_currentLed / 10 + 1) == 0 ? 255 : 0;
	}
	
	delay(1);
	FastLED.show();
}


/*
1.5 seconds for 120 (60 inc, 60 dec) loops with sleep 10

1500 ms / 120 loops = 12.5 ms
sleep is 10 ms
overhead: 2.5 ms

1300 ms / 120 = 10.83 ms
sleep is 10 ms
overhead: 0.83 ms

*/
