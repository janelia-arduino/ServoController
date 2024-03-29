// ----------------------------------------------------------------------------
// 3x2.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#include "3x2.h"


#if defined(__MK20DX256__)

namespace servo_controller
{
namespace constants
{
const modular_server::HardwareInfo hardware_info =
{
  .name_ptr=&hardware_name,
  .part_number=1131,
  .version_major=1,
  .version_minor=0,
};

TwoWire * wire_ptr = &Wire;
const size_t output_enable_pin = 2;

const uint8_t pca9685_addresses[PCA9685_COUNT] =
{
  0x40
};

// Pins

// Units

// Properties
const long channel_count_default = CHANNEL_COUNT_MAX;

const long center_pulse_duration_default[CHANNEL_COUNT_MAX] =
{
  center_pulse_duration_element_default,
  center_pulse_duration_element_default,
  center_pulse_duration_element_default,
  center_pulse_duration_element_default,
  center_pulse_duration_element_default,
  center_pulse_duration_element_default,
  center_pulse_duration_element_default,
  center_pulse_duration_element_default,
  center_pulse_duration_element_default,
  center_pulse_duration_element_default,
  center_pulse_duration_element_default,
  center_pulse_duration_element_default,
  center_pulse_duration_element_default,
  center_pulse_duration_element_default,
  center_pulse_duration_element_default,
  center_pulse_duration_element_default,
};

const double travel_per_unit_pulse_duration_default[CHANNEL_COUNT_MAX] =
{
  travel_per_unit_pulse_duration_element_default,
  travel_per_unit_pulse_duration_element_default,
  travel_per_unit_pulse_duration_element_default,
  travel_per_unit_pulse_duration_element_default,
  travel_per_unit_pulse_duration_element_default,
  travel_per_unit_pulse_duration_element_default,
  travel_per_unit_pulse_duration_element_default,
  travel_per_unit_pulse_duration_element_default,
  travel_per_unit_pulse_duration_element_default,
  travel_per_unit_pulse_duration_element_default,
  travel_per_unit_pulse_duration_element_default,
  travel_per_unit_pulse_duration_element_default,
  travel_per_unit_pulse_duration_element_default,
  travel_per_unit_pulse_duration_element_default,
  travel_per_unit_pulse_duration_element_default,
  travel_per_unit_pulse_duration_element_default,
};

const bool direction_inverted_default[CHANNEL_COUNT_MAX] =
{
  direction_inverted_element_default,
  direction_inverted_element_default,
  direction_inverted_element_default,
  direction_inverted_element_default,
  direction_inverted_element_default,
  direction_inverted_element_default,
  direction_inverted_element_default,
  direction_inverted_element_default,
  direction_inverted_element_default,
  direction_inverted_element_default,
  direction_inverted_element_default,
  direction_inverted_element_default,
  direction_inverted_element_default,
  direction_inverted_element_default,
  direction_inverted_element_default,
  direction_inverted_element_default,
};

const long velocity_limit_default[CHANNEL_COUNT_MAX] =
{
  velocity_limit_element_default,
  velocity_limit_element_default,
  velocity_limit_element_default,
  velocity_limit_element_default,
  velocity_limit_element_default,
  velocity_limit_element_default,
  velocity_limit_element_default,
  velocity_limit_element_default,
  velocity_limit_element_default,
  velocity_limit_element_default,
  velocity_limit_element_default,
  velocity_limit_element_default,
  velocity_limit_element_default,
  velocity_limit_element_default,
  velocity_limit_element_default,
  velocity_limit_element_default,
};

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
