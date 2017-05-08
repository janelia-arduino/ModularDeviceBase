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

  // Add Client Streams
  for (size_t i=0; i<constants::SERIAL_STREAM_COUNT; ++i)
  {
    client_streams_[i].setStream(*(constants::serial_stream_ptrs[i]));
    client_streams_[i].setId(constants::client_stream_ids[i]);
    client_streams_[i].setName(*(constants::client_stream_name_ptrs[i]));
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
  modular_server::Parameter & address_parameter = modular_server_.createParameter(constants::address_parameter_name);
  address_parameter.setRange(constants::address_min,constants::address_max);
  address_parameter.setArrayLengthRange(constants::address_array_length_min,constants::address_array_length_max);

  modular_server::Parameter & request_parameter = modular_server_.createParameter(constants::request_parameter_name);
  request_parameter.setArrayLengthRange(constants::request_array_length_min,constants::request_array_length_max);

  // Functions
  modular_server::Function & forward_to_address_function = modular_server_.createFunction(constants::forward_to_address_function_name);
  forward_to_address_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ModularDeviceBase::forwardToAddressHandler));
  forward_to_address_function.addParameter(address_parameter);
  forward_to_address_function.addParameter(request_parameter);
  forward_to_address_function.setReturnTypeObject();

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

int ModularDeviceBase::findClientStreamIndex(const size_t stream_id)
{
  int stream_index = -1;
  for (size_t i=0; i<constants::CLIENT_STREAM_COUNT; ++i)
  {
    if (stream_id == client_streams_[i])
    {
      stream_index = i;
      break;
    }
  }
  return stream_index;
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
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void ModularDeviceBase::forwardToAddressHandler()
{
  ArduinoJson::JsonArray * address_array_ptr;
  modular_server_.parameter(constants::address_parameter_name).getValue(address_array_ptr);

  ArduinoJson::JsonArray * request_array_ptr;
  modular_server_.parameter(constants::request_parameter_name).getValue(request_array_ptr);

  forwardToAddress(*address_array_ptr,*request_array_ptr);

}
