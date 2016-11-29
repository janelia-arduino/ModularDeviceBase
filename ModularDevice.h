// ----------------------------------------------------------------------------
// ModularDevice.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MODULAR_DEVICE_H
#define MODULAR_DEVICE_H
#include "Flash.h"
#include <EEPROM.h>
#include "Streaming.h"
#include "ArduinoJson.h"
#include "JsonSanitizer.h"
#include "JsonStream.h"
#include "Array.h"
#include "Vector.h"
#include "MemoryFree.h"
#include "ConstantVariable.h"
#include "SavedVariable.h"
#include "Functor.h"
#include "IndexedContainer.h"
#include "FunctorCallbacks.h"

#include "ModularServer.h"

#include "utility/Constants.h"


class ModularDevice
{
public:
  ModularDevice();
  virtual void setup();
  virtual void update();
  virtual void startServer();

  modular_server::ModularServer modular_server_;

  modular_server::Interrupt interrupts_[modular_device::constants::INTERRUPT_COUNT_MAX];

#if defined(__MK20DX128__) || defined(__MK20DX256__)
  modular_server::Interrupt teensy_interrupts_[modular_device::constants::TEENSY_INTERRUPT_COUNT_MAX];
#endif

  modular_server::Property properties_[modular_device::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[modular_device::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[modular_device::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[modular_device::constants::CALLBACK_COUNT_MAX];

private:

  // Handlers

};

#endif
