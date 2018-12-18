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
  .version_major=1,
  .version_minor=0,
  .version_patch=0,
};

CONSTANT_STRING(hardware_name,"servo_controller");

// Pins

// Units
CONSTANT_STRING(us_units,"us");

// Properties
CONSTANT_STRING(channel_count_property_name,"channelCount");
const long channel_count_min = 1;

// Parameters
CONSTANT_STRING(channel_parameter_name,"channel");
const long channel_min = 0;

CONSTANT_STRING(pulse_duration_parameter_name,"pulse_duration");
const long pulse_duration_min = 50;
const long pulse_duration_max = 5000;

// Functions
CONSTANT_STRING(set_channel_pulse_duration_function_name,"setChannelPulseDuration");
CONSTANT_STRING(set_all_channels_pulse_duration_function_name,"setAllChannelsPulseDuration");

// Callbacks
CONSTANT_STRING(enable_all_callback_name,"enableAll");
CONSTANT_STRING(disable_all_callback_name,"disableAll");

// Errors
}
}
