#pragma once

#include <stdlib.h>

constexpr auto COLOR_GALAXY_SLOW_STAR_LENGTH = 11;
constexpr auto COLOR_GALAXY_FAST_STAR_LENGTH = 6;

class LedColor
{
public:
	enum class EColor: uint8_t
	{
		BLACK,
		NAVY,
		DARKBLUE,
		MEDIUMBLUE,
		BLUE,
		DARKGREEN,
		GREEN,
		TEAL,
		DARKCYAN,
		DEEPSKYBLUE,
		DARKTURQUOISE,
		MEDIUMSPRINGGREEN,
		LIME,
		SPRINGGREEN,
		AQUA,
		CYAN,
		MIDNIGHTBLUE,
		DODGERBLUE,
		LIGHTSEAGREEN,
		FORESTGREEN,
		SEAGREEN,
		DARKSLATEGREY,
		LIMEGREEN,
		MEDIUMSEAGREEN,
		TURQUOISE,
		ROYALBLUE,
		STEELBLUE,
		DARKSLATEBLUE,
		MEDIUMTURQUOISE,
		INDIGO,
		DARKOLIVEGREEN,
		CADETBLUE,
		CORNFLOWERBLUE,
		REBECCAPURPLE,
		MEDIUMAQUAMARINE,
		DIMGREY,
		SLATEBLUE,
		OLIVEDRAB,
		SLATEGREY,
		LIGHTSLATEGREY,
		MEDIUMSLATEBLUE,
		LAWNGREEN,
		CHARTREUSE,
		AQUAMARINE,
		MAROON,
		PURPLE,
		OLIVE,
		GREY,
		SKYBLUE,
		LIGHTSKYBLUE,
		BLUEVIOLET,
		DARKRED,
		DARKMAGENTA,
		SADDLEBROWN,
		DARKSEAGREEN,
		LIGHTGREEN,
		MEDIUMPURPLE,
		DARKVIOLET,
		PALEGREEN,
		DARKORCHID,
		YELLOWGREEN,
		SIENNA,
		BROWN,
		DARKGREY,
		LIGHTBLUE,
		GREENYELLOW,
		PALETURQUOISE,
		LIGHTSTEELBLUE,
		POWDERBLUE,
		FIREBRICK,
		DARKGOLDENROD,
		MEDIUMORCHID,
		ROSYBROWN,
		DARKKHAKI,
		SILVER,
		MEDIUMVIOLETRED,
		INDIANRED,
		PERU,
		CHOCOLATE,
		TAN,
		LIGHTGREY,
		THISTLE,
		ORCHID,
		GOLDENROD,
		PALEVIOLETRED,
		CRIMSON,
		GAINSBORO,
		PLUM,
		BURLYWOOD,
		LIGHTCYAN,
		LAVENDER,
		DARKSALMON,
		VIOLET,
		PALEGOLDENROD,
		LIGHTCORAL,
		KHAKI,
		ALICEBLUE,
		HONEYDEW,
		AZURE,
		SANDYBROWN,
		WHEAT,
		BEIGE,
		WHITESMOKE,
		MINTCREAM,
		GHOSTWHITE,
		SALMON,
		ANTIQUEWHITE,
		LINEN,
		LIGHTGOLDENRODYELLOW,
		OLDLACE,
		RED,
		FUCHSIA,
		MAGENTA,
		DEEPPINK,
		ORANGERED,
		TOMATO,
		HOTPINK,
		CORAL,
		DARKORANGE,
		LIGHTSALMON,
		ORANGE,
		LIGHTPINK,
		PINK,
		GOLD,
		PEACHPUFF,
		NAVAJOWHITE,
		MOCCASIN,
		BISQUE,
		MISTYROSE,
		BLANCHEDALMOND,
		PAPAYAWHIP,
		LAVENDERBLUSH,
		SEASHELL,
		CORNSILK,
		LEMONCHIFFON,
		FLORALWHITE,
		SNOW,
		YELLOW,
		LIGHTYELLOW,
		IVORY,
		WHITE,

		RANDOM = 240, RAINBOW, FIRE, GALAXY
	};

	static bool IsOff					(uint8_t* red, uint8_t* green, uint8_t* blue);
	static void SetRgb					(uint8_t* red, uint8_t* green, uint8_t* blue, LedColor::EColor color, uint32_t step);

	static void SetRandom				(uint8_t* red, uint8_t* green, uint8_t* blue);
	static void SetRainbow				(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t step);
	
	static void SetFire					(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t step);
	
	static void SetGalaxy				(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t step);
	static void CreateNewGalaxyStar		(uint8_t* red, uint8_t* green, uint8_t* blue);

	static void SetRgb					(uint8_t* red, uint8_t* green, uint8_t* blue, uint32_t rgb);

	static void SetRgb					(uint8_t* red, uint8_t* green, uint8_t* blue, uint8_t redValue, uint8_t greenValue, uint8_t blueValue);

	static uint8_t SetBrightness		(uint8_t* red, uint8_t* green, uint8_t* blue, uint8_t percentage_0, uint8_t percentage_1);

private:
	static const uint8_t GALAXY_SLOW_SPEED_START_STEP;
	static const uint8_t GALAXY_FAST_SPEED_START_STEP;
	static const uint8_t GALAXY_STEPS[256];
};
