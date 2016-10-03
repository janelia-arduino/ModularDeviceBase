// ----------------------------------------------------------------------------
// ModularDevice.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "ModularDevice.h"


using namespace modular_device;

ModularDevice::ModularDevice()
{
}

void ModularDevice::setup()
{
  // Pin Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);
  modular_server_.setFormFactor(constants::form_factor);

  // Add Device Info
  modular_server_.addFirmwareInfo(constants::firmware_info);
  modular_server_.addHardwareInfo(constants::hardware_info);

#if defined(__MK20DX128__) || defined(__MK20DX256__)
  modular_server_.addHardwareInfo(constants::hardware_info_2);
#endif

  // Add Server Streams
  modular_server_.addServerStream(Serial);

  // Add Storage

  // Fields

  // Parameters

  // Methods

  // Setup Streams
  Serial.begin(constants::baudrate);

}

void ModularDevice::startServer()
{
  // Start Modular Device Server
  modular_server_.startServer();
}

void ModularDevice::update()
{
  modular_server_.handleServerRequests();
}

// Callbacks must be non-blocking (avoid 'delay')
//
// modular_server_.getParameterValue must be cast to either:
// const char *
// long
// double
// bool
// ArduinoJson::JsonArray &
// ArduinoJson::JsonObject &
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.getFieldValue type must match the field default type
// modular_server_.setFieldValue type must match the field default type
// modular_server_.getFieldElementValue type must match the field array element default type
// modular_server_.setFieldElementValue type must match the field array element default type
