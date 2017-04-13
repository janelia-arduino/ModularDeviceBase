// ----------------------------------------------------------------------------
// ModularDeviceBase.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MODULAR_DEVICE_BASE_H
#define MODULAR_DEVICE_BASE_H
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
#include "ModularClient.h"

#include "ModularServer.h"

#include "utility/Constants.h"


class ModularDeviceBase
{
public:
  ModularDeviceBase();
  virtual void setup();
  virtual void update();
  virtual void startServer();

  void forward(ArduinoJson::JsonArray & address_array,
               ArduinoJson::JsonArray & request_array);

protected:

  modular_server::ModularServer modular_server_;

private:

  modular_server::Interrupt processor_interrupts_[modular_device_base::constants::PROCESSOR_INTERRUPT_COUNT_MAX];

  modular_server::Interrupt interrupts_[modular_device_base::constants::INTERRUPT_COUNT_MAX];

  modular_server::Property properties_[modular_device_base::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[modular_device_base::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[modular_device_base::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[modular_device_base::constants::CALLBACK_COUNT_MAX];

  // Handlers
  void forwardHandler();

};

#endif
