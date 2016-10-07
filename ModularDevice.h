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

  modular_server::Field fields_[modular_device::constants::FIELD_COUNT_MAX];
  modular_server::Parameter parameters_[modular_device::constants::PARAMETER_COUNT_MAX];
  modular_server::Method methods_[modular_device::constants::METHOD_COUNT_MAX];

private:

  // Callbacks

};

#endif
