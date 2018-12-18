// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef SERVO_CONTROLLER_CONSTANTS_H
#define SERVO_CONTROLLER_CONSTANTS_H
#include <ConstantVariable.h>
#include <ModularDeviceBase.h>
#include <Wire.h>


namespace servo_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=2};
enum{FUNCTION_COUNT_MAX=2};
enum{CALLBACK_COUNT_MAX=2};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

extern TwoWire * wire_ptr;
extern const size_t output_enable_pin;

// Pins

// Units
extern ConstantString us_units;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString channel_count_property_name;
extern const long channel_count_min;
extern const long channel_count_default;

// Parameters
extern ConstantString channel_parameter_name;
extern const long channel_min;

extern ConstantString pulse_duration_parameter_name;
extern const long pulse_duration_min;
extern const long pulse_duration_max;

// Functions
extern ConstantString set_channel_pulse_duration_function_name;
extern ConstantString set_all_channels_pulse_duration_function_name;

// Callbacks
extern ConstantString enable_all_callback_name;
extern ConstantString disable_all_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
