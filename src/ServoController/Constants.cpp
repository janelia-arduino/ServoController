// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace servo_controller
{
namespace constants
{
CONSTANT_STRING(device_name,"servo_controller");

CONSTANT_STRING(firmware_name,"ServoController");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
{
  .name_ptr=&firmware_name,
  .version_major=2,
  .version_minor=0,
  .version_patch=0,
};

CONSTANT_STRING(hardware_name,"servo_controller");

const long milliseconds_per_second = 1000;

const long velocity_period_ms = 10;

// Pins

// Units
CONSTANT_STRING(us_units,"us");
CONSTANT_STRING(degree_per_us_units,"degree/us");
CONSTANT_STRING(degree_units,"degree");
CONSTANT_STRING(unit_pulse_duration_per_s_units,"unit_pulse_duration/s");

// Properties
CONSTANT_STRING(channel_count_property_name,"channelCount");
const long channel_count_min = 1;

CONSTANT_STRING(center_pulse_duration_property_name,"centerPulseDuration");
const long center_pulse_duration_element_default = 1500;

CONSTANT_STRING(travel_per_unit_pulse_duration_property_name,"travelPerUnitPulseDuration");
const double travel_per_unit_pulse_duration_min = 0.04;
const double travel_per_unit_pulse_duration_max = 0.2;
const double travel_per_unit_pulse_duration_element_default = 0.085;

CONSTANT_STRING(direction_inverted_property_name,"directionInverted");
const bool direction_inverted_element_default = false;

CONSTANT_STRING(velocity_limit_property_name,"velocityLimit");
const long velocity_limit_min = 1;
const long velocity_limit_max = 50000;
const long velocity_limit_element_default = 5000;

// Parameters
CONSTANT_STRING(channel_parameter_name,"channel");
const long channel_min = 0;

CONSTANT_STRING(pulse_duration_parameter_name,"pulse_duration");
const long pulse_duration_min = 50;
const long pulse_duration_max = 5000;

CONSTANT_STRING(angle_parameter_name,"angle");
const double angle_min = -180.0;
const double angle_max = 180.0;

// Functions
CONSTANT_STRING(set_channel_pulse_duration_function_name,"setChannelPulseDuration");
CONSTANT_STRING(set_all_channels_pulse_duration_function_name,"setAllChannelsPulseDuration");
CONSTANT_STRING(rotate_to_function_name,"rotateTo");
CONSTANT_STRING(rotate_all_to_function_name,"rotateAllTo");
CONSTANT_STRING(rotate_by_function_name,"rotateBy");
CONSTANT_STRING(rotate_all_by_function_name,"rotateAllBy");

// Callbacks
CONSTANT_STRING(enable_all_callback_name,"enableAll");
CONSTANT_STRING(disable_all_callback_name,"disableAll");

// Errors
}
}
