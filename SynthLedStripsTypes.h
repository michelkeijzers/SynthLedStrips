#pragma once

#include "SynthLedStripsTypes.h"

#include "ClassNames.h"

#ifndef _WINDOWS
#include HEADER_FILE(ARDUINO_CLASS)

#define FastLedCRGB CRGB

#endif

#include "stdint.h"

/*
typedef signed char        int8_t;
typedef short int          int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
*/

typedef uint32_t par_bits_t;
typedef uint8_t  par_group_t; // Used within command to store
typedef uint16_t dmx_channel_t;
typedef uint8_t  dmx_value_t;
typedef uint8_t  program_t;
typedef uint8_t  preset_t;
typedef int16_t step_t; // Can be negative (for rainbow program)
typedef uint8_t  step_duration_t;
typedef uint32_t step_time_t;
typedef int16_t parameter_t;
typedef uint8_t  intensity_t;
typedef uint8_t  fixture_number_t;
typedef uint8_t  led_bar_segment_number_t;
