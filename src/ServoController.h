// ----------------------------------------------------------------------------
// ServoController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <PCA9685.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>

#include "ServoController/Constants.h"


class ServoController : public ModularDeviceBase, public PCA9685
{
public:
  ServoController();
  virtual void setup();

private:
  modular_server::Pin pins_[servo_controller::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[servo_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[servo_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[servo_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[servo_controller::constants::CALLBACK_COUNT_MAX];

  // Handlers

};

#endif
