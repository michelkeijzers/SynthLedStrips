#ifdef _WINDOWS

#pragma once

#include <cstdint>

#include "LedStrip.h"

const uint8_t MAX_NR_OF_LED_STRIPS = 16;

const uint8_t MAX_NR_OF_LEDS = 255;

enum ESPIChipsets {	WS2811, WS2812, WS2813 };
enum EOrder { RGB };

struct FastLedCRGB
{
	uint8_t red; 
	uint8_t green; 
	uint8_t blue; 
};

class CLEDController
{
};


class CFastLED {
private:
	static struct FastLedCRGB *_data[MAX_NR_OF_LED_STRIPS];
	static int _pinNumbers[MAX_NR_OF_LED_STRIPS];
	static int _nrOfUsedLeds[MAX_NR_OF_LED_STRIPS];
	//static int _nLedsOrOffset[MAX_NR_OF_LED_STRIPS];

	static int _nrOfLedStrips;

	static bool _showEnabled;

public:
	CFastLED();

	static struct FastLedCRGB* GetData(int ledStrip);
	static int GetPinNumber(int ledStrip);
	static int GetNrOfUsedLeds(int ledStrip);
	static int GetNrOfLedStrips();

	static bool IsShowEnabled();

	static CLEDController& addLeds(CLEDController* pLed, struct FastLedCRGB* data, int nLedsOrOffset, int nLedsIfOffset = 0);

	template<ESPIChipsets CHIPSET, uint8_t DATA_PIN, EOrder RGB_ORDER> CLEDController& addLeds(
		struct FastLedCRGB* data, int nLedsOrOffset)
	{
		_pinNumbers[_nrOfLedStrips] = DATA_PIN;
		addLeds(nullptr, data, nLedsOrOffset);

		return *new CLEDController();
	}
	
	void setBrightness(uint8_t scale) { }

	uint8_t getBrightness() {  }

	inline void setMaxPowerInVoltsAndMilliamps(uint8_t volts, uint32_t milliamps) { setMaxPowerInMilliWatts(volts * milliamps); }

	inline void setMaxPowerInMilliWatts(uint32_t milliwatts) {  }

	void show(uint8_t scale);

	void show();

	void clear(bool writeData = false);

	void clearData();

	void showColor(const struct CRGB & color, uint8_t scale);

	void showColor(const struct CRGB & color) {  }

	void delay(unsigned long ms);

	void setTemperature(const struct CRGB & temp);

	void setCorrection(const struct CRGB & correction);

	void setDither(uint8_t ditherMode = 0);

	void setMaxRefreshRate(uint16_t refresh, bool constrain=false);

	void countFPS(int nFrames=25);

	uint16_t getFPS() { return 0; }

	int count();

	CLEDController & operator[](int x);

	//int size() { return (*this)[0].size(); }

	//CRGB *leds() { return (*this)[0].leds(); }
};

extern CFastLED FastLED;

#endif // WINDOWS_H