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
#include <Functor.h>
#include <PCA9685.h>


namespace servo_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=5};
enum{PARAMETER_COUNT_MAX=3};
enum{FUNCTION_COUNT_MAX=6};
enum{CALLBACK_COUNT_MAX=2};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

extern TwoWire * wire_ptr;
extern const size_t output_enable_pin;

extern const long milliseconds_per_second;

extern const long velocity_delay;
extern const long velocity_period;
extern const long velocity_offset;

struct ChannelInfo
{
  uint16_t velocity_limit;
  uint16_t pulse_duration;
  uint16_t pulse_duration_target;
  EventId velocity_event_id;
  Functor1<int> at_target_position_functor;
};

// Pins

// Units
extern ConstantString us_units;
extern ConstantString degree_per_us_units;
extern ConstantString degree_units;
extern ConstantString unit_pulse_duration_per_velocity_period_units;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString channel_count_property_name;
extern const long channel_count_min;
extern const long channel_count_default;

extern ConstantString center_pulse_duration_property_name;
extern const long center_pulse_duration_element_default;

extern ConstantString travel_per_unit_pulse_duration_property_name;
extern const double travel_per_unit_pulse_duration_min;
extern const double travel_per_unit_pulse_duration_max;
extern const double travel_per_unit_pulse_duration_element_default;

extern ConstantString direction_inverted_property_name;
extern const bool direction_inverted_element_default;

extern ConstantString velocity_limit_property_name;
extern const long velocity_limit_min;
extern const long velocity_limit_max;
extern const long velocity_limit_element_default;

// Parameters
extern ConstantString channel_parameter_name;
extern const long channel_min;

extern ConstantString pulse_duration_parameter_name;
extern const long pulse_duration_min;
extern const long pulse_duration_max;

extern ConstantString angle_parameter_name;
extern const double angle_min;
extern const double angle_max;

// Functions
extern ConstantString set_channel_pulse_duration_function_name;
extern ConstantString set_all_channels_pulse_duration_function_name;
extern ConstantString rotate_to_function_name;
extern ConstantString rotate_all_to_function_name;
extern ConstantString rotate_by_function_name;
extern ConstantString rotate_all_by_function_name;

// Callbacks
extern ConstantString enable_all_callback_name;
extern ConstantString disable_all_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
