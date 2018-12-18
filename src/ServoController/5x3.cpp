// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "5x3.h"


#if defined(__MK64FX512__)

namespace servo_controller
{
namespace constants
{
const modular_server::HardwareInfo hardware_info =
{
  .name_ptr=&hardware_name,
  .part_number=1130,
  .version_major=1,
  .version_minor=0,
};

TwoWire * wire_ptr = &Wire;
const size_t output_enable_pin = 2;

const uint8_t pca9685_addresses[PCA9685_COUNT] =
{
  0x40,
  0x41
};

// Pins

// Units

// Properties
const long channel_count_default = CHANNEL_COUNT_MAX;

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
