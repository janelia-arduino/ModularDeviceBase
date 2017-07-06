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
  pinMode(constants::led_green_pin,OUTPUT);
  setLedOn(constants::led_green);
  pinMode(constants::led_yellow_pin,OUTPUT);
  setLedOff(constants::led_yellow);

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

  modular_server::Interrupt & btn_a_interrupt = modular_server_.createInterrupt(constants::btn_a_interrupt_name,
                                                                                constants::btn_a_pin);

#endif

#if defined(__MK64FX512__)
  modular_server::Interrupt & btn_b_interrupt = modular_server_.createInterrupt(constants::btn_b_interrupt_name,
                                                                                constants::btn_b_pin);


#endif

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);

  // Properties
  modular_server::Property & leds_enabled_property = modular_server_.createProperty(constants::leds_enabled_property_name,constants::leds_enabled_default);
  leds_enabled_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&ModularDeviceBase::ledsEnabledHandler));

  // Parameters
  modular_server::Parameter & address_parameter = modular_server_.createParameter(constants::address_parameter_name);
  address_parameter.setRange(constants::address_min,constants::address_max);
  address_parameter.setArrayLengthRange(constants::address_array_length_min,constants::address_array_length_max);
  address_parameter.setTypeLong();

  modular_server::Parameter & request_parameter = modular_server_.createParameter(constants::request_parameter_name);
  request_parameter.setArrayLengthRange(constants::request_array_length_min,constants::request_array_length_max);
  request_parameter.setTypeAny();

  modular_server::Parameter & led_parameter = modular_server_.createParameter(constants::led_parameter_name);
  led_parameter.setTypeString();
  led_parameter.setSubset(constants::led_ptr_subset);

  // Functions
  modular_server::Function & forward_to_address_function = modular_server_.createFunction(constants::forward_to_address_function_name);
  forward_to_address_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ModularDeviceBase::forwardToAddressHandler));
  forward_to_address_function.addParameter(address_parameter);
  forward_to_address_function.addParameter(request_parameter);
  forward_to_address_function.setResultTypeObject();

  modular_server::Function & get_client_info_function = modular_server_.createFunction(constants::get_client_info_function_name);
  get_client_info_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ModularDeviceBase::getClientInfoHandler));
  get_client_info_function.setResultTypeObject();

  modular_server::Function & set_led_on_function = modular_server_.createFunction(constants::set_led_on_function_name);
  set_led_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ModularDeviceBase::setLedOnHandler));
  set_led_on_function.addParameter(led_parameter);

  modular_server::Function & set_led_off_function = modular_server_.createFunction(constants::set_led_off_function_name);
  set_led_off_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ModularDeviceBase::setLedOffHandler));
  set_led_off_function.addParameter(led_parameter);

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

JsonStream * ModularDeviceBase::findClientJsonStream(const size_t stream_id)
{
  JsonStream * json_stream_ptr = NULL;
  int stream_index = findClientStreamIndex(stream_id);
  if (stream_index >= 0)
  {
    json_stream_ptr = &(client_streams_[stream_index].getJsonStream());
  }
  return json_stream_ptr;
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

int ModularDeviceBase::findClientStreamIndex(Stream & Stream)
{
  int stream_index = -1;
  for (size_t i=0; i<constants::CLIENT_STREAM_COUNT; ++i)
  {
    if (&Stream == &(client_streams_[i].getStream()))
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

void ModularDeviceBase::ledsEnabledHandler()
{
  bool leds_enabled;
  modular_server_.property(constants::leds_enabled_property_name).getValue(leds_enabled);

  if (!leds_enabled)
  {
    bool led_green_on = led_green_on_;
    setLedOff(constants::led_green);
    led_green_on_ = led_green_on;
    bool led_yellow_on = led_yellow_on_;
    setLedOff(constants::led_yellow);
    led_yellow_on_ = led_yellow_on;
  }
  else
  {
    if (led_green_on_)
    {
      setLedOn(constants::led_green);
    }
    if (led_yellow_on_)
    {
      setLedOn(constants::led_yellow);
    }
  }
}

void ModularDeviceBase::forwardToAddressHandler()
{
  ArduinoJson::JsonArray * address_array_ptr;
  modular_server_.parameter(constants::address_parameter_name).getValue(address_array_ptr);

  ArduinoJson::JsonArray * request_array_ptr;
  modular_server_.parameter(constants::request_parameter_name).getValue(request_array_ptr);

  forwardToAddress(*address_array_ptr,*request_array_ptr);

}

void ModularDeviceBase::getClientInfoHandler()
{
  modular_server_.response().writeResultKey();

  modular_server_.response().beginArray();

  for (size_t client_index=0; client_index<clients_.size(); ++client_index)
  {
    ModularClient & client = clients_[client_index];

    modular_server_.response().beginObject();

    int client_stream_index = findClientStreamIndex(client.getStream());
    if (client_stream_index >= 0)
    {
      const ConstantString & stream_name = client_streams_[client_stream_index].getName();
      modular_server_.response().write(constants::stream_string,stream_name);
    }

    modular_server_.response().write(constants::address_parameter_name,client.getAddress());

    modular_server_.response().endObject();
  }

  modular_server_.response().endArray();
}

void ModularDeviceBase::setLedOnHandler()
{
  const char * led;
  modular_server_.parameter(constants::led_parameter_name).getValue(led);

  setLedOn(led);
}

void ModularDeviceBase::setLedOffHandler()
{
  const char * led;
  modular_server_.parameter(constants::led_parameter_name).getValue(led);

  setLedOff(led);
}

