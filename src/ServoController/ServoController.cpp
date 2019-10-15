// ----------------------------------------------------------------------------
// ServoController.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "../ServoController.h"


using namespace servo_controller;

ServoController::ServoController()
{
}

void ServoController::setup()
{
  // Parent Setup
  ModularDeviceBase::setup();
  PCA9685::setWire(*constants::wire_ptr);
  for (uint8_t pca9685_index=0; pca9685_index<constants::PCA9685_COUNT; ++pca9685_index)
  {
    PCA9685::addDevice(constants::pca9685_addresses[pca9685_index]);
  }
  PCA9685::resetAllDevices();
  PCA9685::setToServoFrequency();
  PCA9685::setupOutputEnablePin(constants::output_enable_pin);
  enableAll();

  // Reset Watchdog
  resetWatchdog();

  // Variable Setup

  // Event Controller Setup
  event_controller_.setup();

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware
  modular_server_.addHardware(constants::hardware_info,
    pins_);

  // Pins

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & channel_count_property = modular_server_.createProperty(constants::channel_count_property_name,constants::channel_count_default);
  channel_count_property.setRange(constants::channel_count_min,constants::CHANNEL_COUNT_MAX);
  channel_count_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&ServoController::setChannelCountHandler));

  modular_server::Property & center_pulse_duration_property = modular_server_.createProperty(constants::center_pulse_duration_property_name,constants::center_pulse_duration_default);
  center_pulse_duration_property.setUnits(constants::us_units);
  center_pulse_duration_property.setRange(constants::pulse_duration_min,constants::pulse_duration_max);

  modular_server::Property & travel_per_unit_pulse_duration_property = modular_server_.createProperty(constants::travel_per_unit_pulse_duration_property_name,constants::travel_per_unit_pulse_duration_default);
  travel_per_unit_pulse_duration_property.setUnits(constants::degree_per_us_units);
  travel_per_unit_pulse_duration_property.setRange(constants::travel_per_unit_pulse_duration_min,constants::travel_per_unit_pulse_duration_max);

  modular_server_.createProperty(constants::direction_inverted_property_name,constants::direction_inverted_default);

  modular_server::Property & velocity_limit_property = modular_server_.createProperty(constants::velocity_limit_property_name,constants::velocity_limit_default);
  velocity_limit_property.setUnits(constants::unit_pulse_duration_per_s_units);
  velocity_limit_property.setRange(constants::velocity_limit_min,constants::velocity_limit_max);

  // Parameters
  modular_server::Parameter & channel_parameter = modular_server_.createParameter(constants::channel_parameter_name);
  channel_parameter.setTypeLong();

  modular_server::Parameter & pulse_duration_parameter = modular_server_.createParameter(constants::pulse_duration_parameter_name);
  pulse_duration_parameter.setRange(constants::pulse_duration_min,constants::pulse_duration_max);
  pulse_duration_parameter.setUnits(constants::us_units);

  modular_server::Parameter & angle_parameter = modular_server_.createParameter(constants::angle_parameter_name);
  angle_parameter.setRange(constants::angle_min,constants::angle_max);
  angle_parameter.setUnits(constants::degree_units);

  setChannelCountHandler();

  // Functions
  modular_server::Function & set_channel_pulse_duration_function = modular_server_.createFunction(constants::set_channel_pulse_duration_function_name);
  set_channel_pulse_duration_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ServoController::setChannelPulseDurationHandler));
  set_channel_pulse_duration_function.addParameter(channel_parameter);
  set_channel_pulse_duration_function.addParameter(pulse_duration_parameter);

  modular_server::Function & set_all_channels_pulse_duration_function = modular_server_.createFunction(constants::set_all_channels_pulse_duration_function_name);
  set_all_channels_pulse_duration_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ServoController::setAllChannelsPulseDurationHandler));
  set_all_channels_pulse_duration_function.addParameter(pulse_duration_parameter);

  modular_server::Function & rotate_to_function = modular_server_.createFunction(constants::rotate_to_function_name);
  rotate_to_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ServoController::rotateToHandler));
  rotate_to_function.addParameter(channel_parameter);
  rotate_to_function.addParameter(angle_parameter);

  modular_server::Function & rotate_all_to_function = modular_server_.createFunction(constants::rotate_all_to_function_name);
  rotate_all_to_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ServoController::rotateAllToHandler));
  rotate_all_to_function.addParameter(angle_parameter);

  modular_server::Function & rotate_by_function = modular_server_.createFunction(constants::rotate_by_function_name);
  rotate_by_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ServoController::rotateByHandler));
  rotate_by_function.addParameter(channel_parameter);
  rotate_by_function.addParameter(angle_parameter);

  modular_server::Function & rotate_all_by_function = modular_server_.createFunction(constants::rotate_all_by_function_name);
  rotate_all_by_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ServoController::rotateAllByHandler));
  rotate_all_by_function.addParameter(angle_parameter);

  // Callbacks
  modular_server::Callback & enable_all_callback = modular_server_.createCallback(constants::enable_all_callback_name);
  enable_all_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&ServoController::enableAllHandler));

  modular_server::Callback & disable_all_callback = modular_server_.createCallback(constants::disable_all_callback_name);
  disable_all_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&ServoController::disableAllHandler));

  setupVelocityEvents();
}

size_t ServoController::getChannelCount()
{
  long channel_count;
  modular_server_.property(constants::channel_count_property_name).getValue(channel_count);

  return channel_count;
}

void ServoController::enableAll()
{
  PCA9685::enableOutputs(constants::output_enable_pin);
}

void ServoController::disableAll()
{
  PCA9685::disableOutputs(constants::output_enable_pin);
}

void ServoController::setChannelPulseDuration(size_t channel,
  uint16_t pulse_duration)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  event_controller_.clear(event_ids_[channel]);
  // long pulse_duration_diff = pulse_duration - channel_info_array_[channel].pulse_duration;
  PCA9685::setChannelServoPulseDuration(channel,pulse_duration);
  noInterrupts();
  channel_info_array_[channel].pulse_duration = pulse_duration;
  interrupts();
}

void ServoController::setAllChannelsPulseDuration(uint16_t pulse_duration)
{
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    setChannelPulseDuration(channel,pulse_duration);
  }
}

void ServoController::rotateTo(size_t channel,
  double angle)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  long center_pulse_duration;
  modular_server::Property & center_pulse_duration_property = modular_server_.property(constants::center_pulse_duration_property_name);
  center_pulse_duration_property.getElementValue(channel,center_pulse_duration);

  uint16_t pulse_duration = angleToPulseDuration(channel,angle) + center_pulse_duration;
  setChannelPulseDuration(channel,pulse_duration);
}

void ServoController::rotateAllTo(double angle)
{
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    rotateTo(channel,angle);
  }
}

void ServoController::rotateBy(size_t channel,
  double angle)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  noInterrupts();
  uint16_t current_pulse_duration = channel_info_array_[channel].pulse_duration;
  interrupts();

  uint16_t pulse_duration = angleToPulseDuration(channel,angle) + current_pulse_duration;
  setChannelPulseDuration(channel,pulse_duration);
}

void ServoController::rotateAllBy(double angle)
{
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    rotateBy(channel,angle);
  }
}

void ServoController::addEvent(size_t channel,
  long delay,
  const Functor1<int> & event_functor)
{
  if ((channel >= getChannelCount()) || (event_controller_.eventsAvailable() < 1))
  {
    return;
  }
  EventId event_id = event_controller_.addEventUsingDelay(
    event_functor,
    delay,
    channel);
  event_controller_.enable(event_id);
  event_ids_[channel] = event_id;
}

long ServoController::angleToPulseDuration(size_t channel,
  double angle)
{
  double travel_per_unit_pulse_duration;
  modular_server::Property & travel_per_unit_pulse_duration_property = modular_server_.property(constants::travel_per_unit_pulse_duration_property_name);
  travel_per_unit_pulse_duration_property.getElementValue(channel,travel_per_unit_pulse_duration);

  bool direction_inverted;
  modular_server::Property & direction_inverted_property = modular_server_.property(constants::direction_inverted_property_name);
  direction_inverted_property.getElementValue(channel,direction_inverted);

  int polarity = -1;
  if (direction_inverted)
  {
    polarity = 1;
  }

  return polarity * round(angle / travel_per_unit_pulse_duration);
}

void ServoController::setupVelocityEvents()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT_MAX; ++channel)
  {
    channel_info_array_[channel].pulse_duration = constants::center_pulse_duration_element_default;
  }
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
// const ConstantString *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void ServoController::setChannelCountHandler()
{
  size_t channel_count = getChannelCount();

  modular_server::Property & center_pulse_duration_property = modular_server_.property(constants::center_pulse_duration_property_name);
  center_pulse_duration_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & travel_per_unit_pulse_duration_property = modular_server_.property(constants::travel_per_unit_pulse_duration_property_name);
  travel_per_unit_pulse_duration_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & direction_inverted_property = modular_server_.property(constants::direction_inverted_property_name);
  direction_inverted_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & velocity_limit_property = modular_server_.property(constants::velocity_limit_property_name);
  velocity_limit_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Parameter & channel_parameter = modular_server_.parameter(constants::channel_parameter_name);
  channel_parameter.setRange(constants::channel_min,(long)(channel_count-1));

}

void ServoController::enableAllHandler(modular_server::Pin * pin_ptr)
{
  enableAll();
}

void ServoController::disableAllHandler(modular_server::Pin * pin_ptr)
{
  disableAll();
}

void ServoController::setChannelPulseDurationHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
  long pulse_duration;
  modular_server_.parameter(constants::pulse_duration_parameter_name).getValue(pulse_duration);
  setChannelPulseDuration(channel,pulse_duration);
}

void ServoController::setAllChannelsPulseDurationHandler()
{
  long pulse_duration;
  modular_server_.parameter(constants::pulse_duration_parameter_name).getValue(pulse_duration);
  setAllChannelsPulseDuration(pulse_duration);
}

void ServoController::rotateToHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
  double angle;
  modular_server_.parameter(constants::angle_parameter_name).getValue(angle);
  rotateTo(channel,angle);
}

void ServoController::rotateAllToHandler()
{
  double angle;
  modular_server_.parameter(constants::angle_parameter_name).getValue(angle);
  rotateAllTo(angle);
}

void ServoController::rotateByHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
  double angle;
  modular_server_.parameter(constants::angle_parameter_name).getValue(angle);
  rotateBy(channel,angle);
}

void ServoController::rotateAllByHandler()
{
  double angle;
  modular_server_.parameter(constants::angle_parameter_name).getValue(angle);
  rotateAllBy(angle);
}

void ServoController::velocityHandler(int channel)
{
}
