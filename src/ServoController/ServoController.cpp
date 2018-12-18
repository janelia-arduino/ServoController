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

  // Parameters
  modular_server::Parameter & channel_parameter = modular_server_.createParameter(constants::channel_parameter_name);
  channel_parameter.setTypeLong();

  modular_server::Parameter & pulse_duration_parameter = modular_server_.createParameter(constants::pulse_duration_parameter_name);
  pulse_duration_parameter.setRange(constants::pulse_duration_min,constants::pulse_duration_max);
  pulse_duration_parameter.setUnits(constants::us_units);

  // Functions
  modular_server::Function & set_channel_pulse_duration_function = modular_server_.createFunction(constants::set_channel_pulse_duration_function_name);
  set_channel_pulse_duration_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ServoController::setChannelPulseDurationHandler));
  set_channel_pulse_duration_function.addParameter(channel_parameter);
  set_channel_pulse_duration_function.addParameter(pulse_duration_parameter);

  modular_server::Function & set_all_channels_pulse_duration_function = modular_server_.createFunction(constants::set_all_channels_pulse_duration_function_name);
  set_all_channels_pulse_duration_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ServoController::setAllChannelsPulseDurationHandler));
  set_all_channels_pulse_duration_function.addParameter(pulse_duration_parameter);

  // Callbacks
  modular_server::Callback & enable_all_callback = modular_server_.createCallback(constants::enable_all_callback_name);
  enable_all_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&ServoController::enableAllHandler));

  modular_server::Callback & disable_all_callback = modular_server_.createCallback(constants::disable_all_callback_name);
  disable_all_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&ServoController::disableAllHandler));

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
  size_t pulse_duration)
{
  PCA9685::setChannelServoPulseDuration(channel,pulse_duration);
}

void ServoController::setAllChannelsPulseDuration(size_t pulse_duration)
{
  PCA9685::setAllChannelsServoPulseDuration(pulse_duration);
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
