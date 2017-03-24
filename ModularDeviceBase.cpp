// ----------------------------------------------------------------------------
// ModularDeviceBase.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "ModularDeviceBase.h"


using namespace modular_device_base;

ModularDeviceBase::ModularDeviceBase()
{
}

void ModularDeviceBase::setup()
{
  // Server Setup
  modular_server_.setup();

  // Pin Setup

  // Add Server Streams
  modular_server_.addServerStream(Serial);
  for (size_t i=0; i<constants::SERIAL_STREAM_COUNT; ++i)
  {
    modular_server_.addServerStream(*(constants::serial_stream_ptrs[i]));
  }

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);
  modular_server_.setFormFactor(constants::form_factor);

  // Add Hardware
  modular_server_.addHardware(constants::processor_hardware_info,
                              processor_interrupts_);

#if !defined(__AVR_ATmega2560__)
  modular_server_.addHardware(constants::hardware_info,
                              interrupts_);
#endif

  // Interrupts
#if !defined(__AVR_ATmega2560__)
  modular_server::Interrupt & bnc_a_interrupt = modular_server_.createInterrupt(constants::bnc_a_interrupt_name,
                                                                                constants::bnc_a_pin);

  modular_server::Interrupt & bnc_b_interrupt = modular_server_.createInterrupt(constants::bnc_b_interrupt_name,
                                                                                constants::bnc_b_pin);
#endif

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);

  // Properties

  // Parameters

  // Functions

  // Callbacks

  // Begin Streams
  Serial.begin(constants::baudrate);
  for (size_t i=0; i<constants::SERIAL_STREAM_COUNT; ++i)
  {
    constants::serial_stream_ptrs[i]->begin(constants::baudrate);
  }

}

void ModularDeviceBase::startServer()
{
  // Start Modular Device Server
  modular_server_.startServer();
}

void ModularDeviceBase::update()
{
  modular_server_.handleServerRequests();
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
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(value) value type must match the property array element default type
