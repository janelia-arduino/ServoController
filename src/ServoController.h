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

#include <EventController.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>

#include "ServoController/Constants.h"


class ServoController : public ModularDeviceBase, public PCA9685
{
public:
  ServoController();
  virtual void setup();

  virtual size_t getChannelCount();

  void enableAll();
  void disableAll();

  void setChannelPulseDuration(size_t channel,
    uint16_t pulse_duration);
  void setAllChannelsPulseDuration(uint16_t pulse_duration);

  void rotateTo(size_t channel,
    double angle);
  void rotateAllTo(double angle);
  void rotateBy(size_t channel,
    double angle);
  void rotateAllBy(double angle);

protected:
  void addEvent(size_t channel,
    long delay,
    const Functor1<int> & event_functor);
  void setAtTargetPositionFunctor(size_t channel,
    const Functor1<int> & at_target_position_functor);

  // Handlers
  virtual void setChannelCountHandler();

private:
  modular_server::Pin pins_[servo_controller::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[servo_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[servo_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[servo_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[servo_controller::constants::CALLBACK_COUNT_MAX];

  EventController<servo_controller::constants::EVENT_COUNT_MAX> event_controller_;
  EventId event_ids_[servo_controller::constants::CHANNEL_COUNT_MAX];

  servo_controller::constants::ChannelInfo  channel_info_array_[servo_controller::constants::CHANNEL_COUNT_MAX];
  Functor1<int> dummy_functor_;

  long angleToPulseDuration(size_t channel,
    double angle);
  void setupVelocityEvents();

  // Handlers
  void enableAllHandler(modular_server::Pin * pin_ptr);
  void disableAllHandler(modular_server::Pin * pin_ptr);
  void setChannelPulseDurationHandler();
  void setAllChannelsPulseDurationHandler();
  void rotateToHandler();
  void rotateAllToHandler();
  void rotateByHandler();
  void rotateAllByHandler();
  void setVelocityLimitElementHandler(size_t channel);
  void velocityHandler(int channel);

};

#endif
