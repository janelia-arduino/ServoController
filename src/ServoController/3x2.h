// ----------------------------------------------------------------------------
// 3x2.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef SERVO_CONTROLLER_3X2_CONSTANTS_H
#define SERVO_CONTROLLER_3X2_CONSTANTS_H
#include "Constants.h"


#if defined(__MK20DX256__)

namespace servo_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PIN_COUNT_MAX=1};

enum {PCA9685_COUNT=1};
enum {CHANNEL_COUNT_MAX=PCA9685_COUNT*PCA9685::CHANNELS_PER_DEVICE};

enum{EVENT_COUNT_MAX=32};

extern const uint8_t pca9685_addresses[PCA9685_COUNT];

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long center_pulse_duration_default[CHANNEL_COUNT_MAX];

extern const double travel_per_unit_pulse_duration_default[CHANNEL_COUNT_MAX];

extern const bool direction_inverted_default[CHANNEL_COUNT_MAX];

extern const long velocity_limit_default[CHANNEL_COUNT_MAX];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
